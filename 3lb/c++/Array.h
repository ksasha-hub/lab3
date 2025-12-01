#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include <string>

class Array {
private:
    std::string* data;
    size_t capacity;
    size_t currentSize;
    
    void resize(size_t newCapacity);

public:
    Array();
    explicit Array(size_t size);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();
    
    void insert(const std::string& value);
    void insertAt(size_t index, const std::string& value);
    void remove(size_t index);
    std::string get(size_t index) const;
    void set(size_t index, const std::string& value);
    size_t size() const;
    bool empty() const;
    
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