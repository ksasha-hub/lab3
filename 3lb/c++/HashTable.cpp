#include "HashTable.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

const double HashTable::LOAD_FACTOR_THRESHOLD = 0.75;

HashTable::HashTable() : table(new HashNode*[DEFAULT_CAPACITY]), tableSize(0), capacity(DEFAULT_CAPACITY) {
    for (size_t i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

HashTable::HashTable(size_t initialCapacity) : table(new HashNode*[initialCapacity]), tableSize(0), capacity(initialCapacity) {
    if (initialCapacity == 0) {
        throw std::invalid_argument("Capacity must be greater than 0");
    }
    
    for (size_t i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
    delete[] table;
}

HashTable::HashTable(const HashTable& other) : table(new HashNode*[other.capacity]), tableSize(0), capacity(other.capacity) {
    for (size_t i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
    
    for (size_t i = 0; i < other.capacity; ++i) {
        HashNode* current = other.table[i];
        while (current != nullptr) {
            insert(current->key, current->value);
            current = current->next;
        }
    }
}

HashTable& HashTable::operator=(const HashTable& other) {
    if (this != &other) {
        clear();
        delete[] table;
        
        capacity = other.capacity;
        tableSize = 0;
        table = new HashNode*[capacity];
        
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
        
        for (size_t i = 0; i < other.capacity; ++i) {
            HashNode* current = other.table[i];
            while (current != nullptr) {
                insert(current->key, current->value);
                current = current->next;
            }
        }
    }
    return *this;
}

size_t HashTable::hash(int key) const {
    return (static_cast<size_t>(key) * 2654435761U) % capacity;
}

void HashTable::rehash() {
    size_t newCapacity = capacity * 2;
    if (newCapacity == 0) newCapacity = DEFAULT_CAPACITY;
    
    HashNode** newTable = new HashNode*[newCapacity];
    
    for (size_t i = 0; i < newCapacity; ++i) {
        newTable[i] = nullptr;
    }
    
    size_t oldCapacity = capacity;
    capacity = newCapacity;
    
    for (size_t i = 0; i < oldCapacity; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            
            size_t newIndex = hash(current->key);
            
            current->next = newTable[newIndex];
            newTable[newIndex] = current;
            
            current = next;
        }
    }
    
    delete[] table;
    table = newTable;
}

void HashTable::insert(int key, const std::string& value) {
    if (static_cast<double>(tableSize) / capacity > LOAD_FACTOR_THRESHOLD) {
        rehash();
    }
    
    size_t index = hash(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        prev = current;
        current = current->next;
    }
    
    HashNode* newNode = new HashNode(key, value);
    if (prev == nullptr) {
        table[index] = newNode;
    } else {
        prev->next = newNode;
    }
    tableSize++;
}

bool HashTable::remove(int key) {
    size_t index = hash(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            tableSize--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

bool HashTable::contains(int key) const {
    size_t index = hash(key);
    HashNode* current = table[index];
    
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}

std::string HashTable::get(int key) const {
    size_t index = hash(key);
    HashNode* current = table[index];
    
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    throw std::runtime_error("Key not found: " + std::to_string(key));
}

size_t HashTable::size() const {
    return tableSize;
}

bool HashTable::empty() const {
    return tableSize == 0;
}

size_t HashTable::getLongestChain() const {
    size_t maxChain = 0;
    for (size_t i = 0; i < capacity; ++i) {
        size_t chainLength = 0;
        HashNode* current = table[i];
        while (current != nullptr) {
            chainLength++;
            current = current->next;
        }
        if (chainLength > maxChain) {
            maxChain = chainLength;
        }
    }
    return maxChain;
}

size_t HashTable::getShortestChain() const {
    size_t minChain = capacity;
    bool foundNonEmpty = false;
    
    for (size_t i = 0; i < capacity; ++i) {
        size_t chainLength = 0;
        HashNode* current = table[i];
        while (current != nullptr) {
            chainLength++;
            current = current->next;
        }
        
        if (chainLength > 0) {
            foundNonEmpty = true;
            if (chainLength < minChain) {
                minChain = chainLength;
            }
        }
    }
    return foundNonEmpty ? minChain : 0;
}

void HashTable::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* next = current->next;
            delete current;
            current = next;
        }
        table[i] = nullptr;
    }
    tableSize = 0;
}

void HashTable::print() const {
    std::cout << "HashTable (size: " << tableSize << ", capacity: " << capacity << "):" << std::endl;
    
    bool hasElements = false;
    for (size_t i = 0; i < capacity; ++i) {
        if (table[i] != nullptr) {
            hasElements = true;
            std::cout << "Bucket " << i << ": ";
            HashNode* current = table[i];
            while (current != nullptr) {
                std::cout << "(" << current->key << ":" << current->value << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
    
    if (!hasElements) {
        std::cout << "[empty]" << std::endl;
    }
}

void HashTable::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&tableSize), sizeof(tableSize));
    os.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
    
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        size_t bucketSize = 0;
        
        // Сначала подсчитываем размер бакета
        HashNode* temp = current;
        while (temp != nullptr) {
            bucketSize++;
            temp = temp->next;
        }
        
        os.write(reinterpret_cast<const char*>(&bucketSize), sizeof(bucketSize));
        
        // Затем записываем элементы
        while (current != nullptr) {
            os.write(reinterpret_cast<const char*>(&current->key), sizeof(current->key));
            size_t strLen = current->value.length();
            os.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
            os.write(current->value.c_str(), strLen);
            current = current->next;
        }
    }
}

void HashTable::deserialize(std::istream& is) {
    clear();
    delete[] table;
    
    is.read(reinterpret_cast<char*>(&tableSize), sizeof(tableSize));
    is.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
    
    table = new HashNode*[capacity];
    for (size_t i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
    
    for (size_t i = 0; i < capacity; ++i) {
        size_t bucketSize;
        is.read(reinterpret_cast<char*>(&bucketSize), sizeof(bucketSize));
        
        HashNode* last = nullptr;
        for (size_t j = 0; j < bucketSize; ++j) {
            int key;
            size_t strLen;
            is.read(reinterpret_cast<char*>(&key), sizeof(key));
            is.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
            
            std::string value(strLen, ' ');
            is.read(&value[0], strLen);
            
            HashNode* newNode = new HashNode(key, value);
            if (last == nullptr) {
                table[i] = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
        }
    }
}

void HashTable::serializeText(std::ostream& os) const {
    os << tableSize << "\n";
    os << capacity << "\n";
    
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        size_t bucketSize = 0;
        
        HashNode* temp = current;
        while (temp != nullptr) {
            bucketSize++;
            temp = temp->next;
        }
        
        os << bucketSize << "\n";
        while (current != nullptr) {
            os << current->key << "\n";
            
            std::string escaped = current->value;
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
            
            current = current->next;
        }
    }
}

void HashTable::deserializeText(std::istream& is) {
    clear();
    delete[] table;
    
    size_t newTableSize, newCapacity;
    is >> newTableSize;
    is.get();
    is >> newCapacity;
    is.get();
    
    table = new HashNode*[newCapacity];
    capacity = newCapacity;
    tableSize = 0;
    
    for (size_t i = 0; i < newCapacity; ++i) {
        table[i] = nullptr;
    }
    
    for (size_t i = 0; i < newCapacity; ++i) {
        size_t bucketSize;
        is >> bucketSize;
        is.get();
        
       
        for (size_t j = 0; j < bucketSize; ++j) {
            int key;
            is >> key;
            is.get();
            
            std::string line;
            std::getline(is, line);
            
            if (line.size() >= 2 && line.front() == '\"' && line.back() == '\"') {
                line = line.substr(1, line.size() - 2);
                
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
            
            insert(key, line);
        }
    }
}

// Новые методы для тестирования
double HashTable::loadFactor() const {
    if (capacity == 0) return 0.0;
    return static_cast<double>(tableSize) / capacity;
}

size_t HashTable::getCapacity() const {
    return capacity;
}

std::vector<int> HashTable::getAllKeys() const {
    std::vector<int> keys;
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            keys.push_back(current->key);
            current = current->next;
        }
    }
    return keys;
}

bool HashTable::checkIntegrity() const {
    size_t countedSize = 0;
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* current = table[i];
        while (current != nullptr) {
            countedSize++;
            // Проверяем, что элемент находится в правильном бакете
            size_t expectedIndex = hash(current->key);
            if (expectedIndex != i) {
                return false;
            }
            current = current->next;
        }
    }
    return countedSize == tableSize;
}