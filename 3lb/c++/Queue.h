#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinkedList.h"
#include <string>
#include <iostream>
#include <stdexcept>

class Queue {
private:
    SinglyLinkedList list;

public:
    Queue();
    
    void enqueue(const std::string& value);
    std::string dequeue();
    std::string front() const;
    std::string back() const;
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