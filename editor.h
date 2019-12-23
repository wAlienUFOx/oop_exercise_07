#ifndef EDITOR_H
#define EDITOR_H

#include "document.h"
#include "command.h"
#include <iostream>
#include <stack>

class Editor {
public:
    Editor() : Doc(nullptr), History()
    {
    }

    void CreateDocument(const std::string& name) {
        Doc = std::make_shared<Document>(name);
	while(!History.empty())
            History.pop();
    }

    void InsertPrimitive(std::istream& is){
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new InsertCommand(is));
        command->SetDocument(Doc);
        command->Execute();
        History.push(command);
    }

    void RemovePrimitive(uint32_t id) {
        std::shared_ptr<Command> command = std::shared_ptr<Command>(new RemoveCommand(id));
        command->SetDocument(Doc);
        command->Execute();
        History.push(command);
    }

    void SaveDocument(const std::string& filename) {
        Doc->Save(filename);
    }

    void LoadDocument(const std::string& filename) {
        Doc = std::make_shared<Document>("NewDoc");
        Doc->Load(filename);
	while(!History.empty())
            History.pop();
    }

    void Undo() {
        if (History.empty()) {
            throw std::logic_error("History is empty");
        }
        std::shared_ptr<Command> last = History.top();
        last->UnExecute();
        History.pop();
    }

    void PrintDocument() {
        Doc->Print();
    }

    ~Editor() = default;
private:
    std::shared_ptr<Document> Doc;
    std::stack<std::shared_ptr<Command>> History;
};

#endif
