#include "Array.h"
#include <algorithm>
#include <sstream>

Array::Array() : data(nullptr), capacity(0), currentSize(0) {}

Array::Array(size_t size) : capacity(size), currentSize(size) {
    data = new std::string[capacity];
    for (size_t i = 0; i < currentSize; ++i) {
        data[i] = "";
    }
}

Array::Array(const Array& other) : capacity(other.capacity), currentSize(other.currentSize) {
    data = new std::string[capacity];
    for (size_t i = 0; i < currentSize; ++i) {
        data[i] = other.data[i];
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        currentSize = other.currentSize;
        data = new std::string[capacity];
        for (size_t i = 0; i < currentSize; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

Array::~Array() {
    delete[] data;
}

void Array::resize(size_t newCapacity) {
    std::string* newData = new std::string[newCapacity];
    size_t copySize = (currentSize < newCapacity) ? currentSize : newCapacity;
    for (size_t i = 0; i < copySize; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
    currentSize = copySize;
}

void Array::insert(const std::string& value) {
    if (currentSize >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[currentSize++] = value;
}

void Array::insertAt(size_t index, const std::string& value) {
    if (index > currentSize) {
        throw std::out_of_range("Index out of range");
    }
    
    if (currentSize >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    
    for (size_t i = currentSize; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    currentSize++;
}

void Array::remove(size_t index) {
    if (index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    
    for (size_t i = index; i < currentSize - 1; ++i) {
        data[i] = data[i + 1];
    }
    currentSize--;
}

std::string Array::get(size_t index) const {
    if (index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

void Array::set(size_t index, const std::string& value) {
    if (index >= currentSize) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

size_t Array::size() const {
    return currentSize;
}

bool Array::empty() const {
    return currentSize == 0;
}

void Array::clear() {
    currentSize = 0;
}

void Array::print() const {
    std::cout << "[";
    for (size_t i = 0; i < currentSize; ++i) {
        std::cout << "\"" << data[i] << "\"";
        if (i < currentSize - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void Array::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&currentSize), sizeof(currentSize));
    for (size_t i = 0; i < currentSize; ++i) {
        size_t strLen = data[i].length();
        os.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
        os.write(data[i].c_str(), strLen);
    }
}

void Array::deserialize(std::istream& is) {
    size_t arrSize;
    is.read(reinterpret_cast<char*>(&arrSize), sizeof(arrSize));
    
    if (arrSize > capacity) {
        delete[] data;
        capacity = arrSize;
        data = new std::string[capacity];
    }
    
    currentSize = arrSize;
    for (size_t i = 0; i < arrSize; ++i) {
        size_t strLen;
        is.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
        std::string value(strLen, ' ');
        is.read(&value[0], strLen);
        data[i] = value;
    }
}

// Текстовая сериализация
void Array::serializeText(std::ostream& os) const {
    os << currentSize << "\n";
    for (size_t i = 0; i < currentSize; ++i) {
        // Экранируем специальные символы
        std::string escaped = data[i];
        size_t pos = 0;
        while ((pos = escaped.find('\n', pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\\n");
            pos += 2;
        }
        pos = 0;
        while ((pos = escaped.find('\"', pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\\\"");
            pos += 2;
        }
        os << "\"" << escaped << "\"\n";
    }
}

// Текстовая десериализация
void Array::deserializeText(std::istream& is) {
    size_t newSize;
    is >> newSize;
    is.get(); // Пропускаем перевод строки
    
    clear();
    
    for (size_t i = 0; i < newSize; ++i) {
        std::string line;
        std::getline(is, line);
        
        // Убираем обрамляющие кавычки и разэкранируем
        if (line.size() >= 2 && line.front() == '\"' && line.back() == '\"') {
            line = line.substr(1, line.size() - 2);
            
            // Разэкранируем специальные символы
            size_t pos = 0;
            while ((pos = line.find("\\n", pos)) != std::string::npos) {
                line.replace(pos, 2, "\n");
                pos += 1;
            }
            pos = 0;
            while ((pos = line.find("\\\"", pos)) != std::string::npos) {
                line.replace(pos, 2, "\"");
                pos += 1;
            }
        }
        
        insert(line);
    }
}