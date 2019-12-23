#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <fstream>
#include <cstdint>
#include <memory>
#include <string>
#include <algorithm>
#include "figure.h"
#include "factory.h"
#include <vector>

class Document {
public:
    Document(): Id(1), Name(""), Vec(0), Factory()
    {}

    explicit Document(std::string name):
            Id(1),
            Name(std::move(name)),
            Vec(0),
            Factory()
    {}

    ~Document() = default;

    void Save(const std::string& filename) const {
        std::ofstream os;
        os.open(filename, std::ios_base::binary | std::ios_base::out);
        if (!os.is_open()) {
            throw std::runtime_error("File is not opened");
        }
        uint32_t nameLen = Name.size();
        os.write((char*)&nameLen, sizeof(nameLen));
        os.write((char*)(Name.c_str()), nameLen);
        for (const auto& shape : Vec) {
            shape->Serialize(os);
        }
    }

    void Load(const std::string& filename) {
        std::ifstream is;
        is.open(filename, std::ios_base::binary | std::ios_base::in);
        if (!is.is_open()) {
            throw std::runtime_error("File is not opened");
        }
        uint32_t nameLen;
        is.read((char*)&nameLen, sizeof(nameLen));
        char* name = new char[nameLen + 1];
        name[nameLen] = 0;
        is.read(name, nameLen);
        Name = std::string(name);
        delete[] name;
        figures::FigureType type;
        while(is.read((char*)&type, sizeof(type))) {
            Vec.push_back(Factory.FigureCreate(type));
            Vec.back()->Deserialize(is);
        }
        Id = Vec.size();
    }

    void Print() {
        int it = 0;
        std::for_each(Vec.begin(), Vec.end(), [&it](std::shared_ptr<figures::Figure>& fig) {
            std::cout << it << ") ";
           fig->print(std::cout);
           it++;
        });
    }

    void Remove(uint32_t Id) {
        if (Id >= Vec.size())
            throw std::logic_error("Wrong index");
        Vec.erase(Vec.begin() + Id);
    }

    void Insert(std::istream& is) {
        Vec.push_back(Factory.FigureCreate(is));
    }

    void  Insert(uint32_t Id, std::shared_ptr<figures::Figure> figure) {
        Vec.insert(Vec.begin() + Id, figure);
    }

private:
    uint32_t Id;
    std::string Name;
    std::vector<std::shared_ptr<figures::Figure>> Vec;
    factory::Factory Factory;

    friend class InsertCommand;
    friend class RemoveCommand;

    void RemoveLastPrimitive() {
        if (Vec.empty())
            throw std::logic_error("Document is empty");
        Vec.pop_back();
    }

    std::shared_ptr<figures::Figure> GetFigure(uint32_t Id) {
        if (Id >= Vec.size())
            throw std::logic_error("Wrong index");
        auto it = Vec.begin() + Id;
        return *it;
    }
};

#endif