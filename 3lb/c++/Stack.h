#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"
#include <string>
#include <iostream>
#include <stdexcept>

class Stack {
private:
    SinglyLinkedList list;

public:
    Stack();
    
    void push(const std::string& value);
    std::string pop();
    std::string top() const;
    bool empty() const;
    size_t size() const;
    
    void clear();
    void print() const;
    
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
    
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
};

#endif