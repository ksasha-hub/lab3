#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

class HashTable {
private:
    struct HashNode {
        int key;
        std::string value;
        HashNode* next;
        HashNode(int k, const std::string& v) : key(k), value(v), next(nullptr) {}
    };
    
    static const size_t DEFAULT_CAPACITY = 16;
    static const double LOAD_FACTOR_THRESHOLD;
    
    HashNode** table;
    size_t tableSize;
    size_t capacity;
    
    size_t hash(int key) const;
    void rehash();

public:
    HashTable();
    explicit HashTable(size_t initialCapacity);
    ~HashTable();
    HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& other);
    
    void insert(int key, const std::string& value);
    bool remove(int key);
    bool contains(int key) const;
    std::string get(int key) const;
    size_t size() const;
    bool empty() const;
    
    size_t getLongestChain() const;
    size_t getShortestChain() const;
    
    // Новые методы для тестирования
    double loadFactor() const;
    size_t getCapacity() const;
    std::vector<int> getAllKeys() const;
    bool checkIntegrity() const;
    
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