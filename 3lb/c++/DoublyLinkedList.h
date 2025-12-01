#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>

class DoublyLinkedList {
private:
    struct Node {
        std::string data;
        Node* next;
        Node* prev;
        explicit Node(const std::string& val) : data(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    size_t listSize;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    DoublyLinkedList(const DoublyLinkedList& other);
    DoublyLinkedList& operator=(const DoublyLinkedList& other);
    
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