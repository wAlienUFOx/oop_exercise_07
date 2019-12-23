#ifndef COMMAND_H
#define COMMAND_H

#include "document.h"
#include <stack>
#include <iostream>

class Command {
protected:
    std::shared_ptr<Document> Doc;
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;

    void SetDocument(std::shared_ptr<Document> doc) {
        Doc = doc;
    }
};

class InsertCommand : public Command {
public:
    explicit InsertCommand(std::istream& is):
            input(is)
    {}

    void Execute() override {
        Doc->Insert(input);
    }

    void UnExecute() override {
        Doc->RemoveLastPrimitive();
    }

private:
    std::istream& input;
};

class RemoveCommand : public Command {
public:
    explicit RemoveCommand(uint32_t id): Id(id)
    {}

    void Execute() override {
        Fig = Doc->GetFigure(Id);
        Doc->Remove(Id);
    }

    void UnExecute() override {
        Doc->Insert(Id, Fig);
    }

private:
    uint32_t Id;
    std::shared_ptr<figures::Figure> Fig;
};

#endif