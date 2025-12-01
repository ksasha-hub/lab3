#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"
#include "SerializationUtils.h"

class ConsoleInterface {
private:
    std::map<std::string, Array*> arrays;
    std::map<std::string, SinglyLinkedList*> singlyLists;
    std::map<std::string, DoublyLinkedList*> doublyLists;
    std::map<std::string, Queue*> queues;
    std::map<std::string, Stack*> stacks;
    std::map<std::string, HashTable*> hashTables;
    std::map<std::string, CompleteBinaryTree*> trees;

    // Вспомогательные методы
    std::vector<std::string> split(const std::string& str, char delimiter);
    int stringToInt(const std::string& str);
    void printHelp();
    std::string unescapeString(const std::string& str);
    std::string escapeString(const std::string& str);

public:
    ConsoleInterface();
    ~ConsoleInterface();
    
    void executeCommand(const std::vector<std::string>& args);
    void runFromCommandLine(int argc, char* argv[]);
    void interactiveMode();
};

#endif