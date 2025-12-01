#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class SinglyLinkedList {
private:
    struct Node {
        std::string data;
        Node* next;
        explicit Node(const std::string& val) : data(val), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t listSize;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList& other);
    SinglyLinkedList& operator=(const SinglyLinkedList& other);
    
    void push_front(const std::string& value);
    void push_back(const std::string& value);
    void pop_front();
    void pop_back();
    void insert(size_t index, const std::string& value);
    void remove(size_t index);
    std::string get(size_t index) const;
    size_t size() const;
    bool empty() const;
    
    // Новые методы для тестирования
    bool checkIntegrity() const;
    std::vector<std::string> toVector() const;
    bool contains(const std::string& value) const;
    
    void clear();
    void print() const;
    
    // Бинарная сериализация
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
    
    // Текстовая сериализация
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
};

#endif