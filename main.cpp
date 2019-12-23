#include <iostream>
#include "editor.h"

int main(){
    Editor editor;
    char cmd;
    std::cout << "Input command. Input 'h' for help;" << std::endl;
    while (std::cin >> cmd) {
        switch (cmd) {
            case 'h':
                std::cout << "h - help\n"
                          << "c - create\n"
                          << "l - load\n"
                          << "s - save\n"
                          << "a - add\n"
                          << "r - remove\n"
                          << "u - undo\n"
                          << "p - print\n"
                          << "q - quit\n";
                break;
            case 'c': {
                std::string name;
                std::cin >> name;
                editor.CreateDocument(name);
                std::cout << "Document " << name << " is created" << std::endl;
                break;
            }
            case 'l':{
                std::string filename;
                std::cin >> filename;
                try {
                    editor.LoadDocument(filename);
                    std::cout << "Document loaded" << std::endl;
                } catch (std::runtime_error& err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 's': {
                std::string filename;
                std::cin >> filename;

                try {
                    editor.SaveDocument(filename);
                    std::cout << "Document save" << std::endl;
                } catch (std::runtime_error &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 'a': {
                try {
                    editor.InsertPrimitive(std::cin);
                    std::cout << "Added" << std::endl;
                }catch (std::logic_error& err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 'r':{
                int id;
                std::cin >> id;
                try {
                    editor.RemovePrimitive(id);
                    std::cout << "Removed" << std::endl;
                } catch (std::logic_error& err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 'u':
                editor.Undo();
                break;
            case 'p':
                editor.PrintDocument();
                break;
            case 'q':
                return 0;
            default:
                std::cout << "Wrong. Input 'h' for help\n";
        }
    }
    return 0;
}