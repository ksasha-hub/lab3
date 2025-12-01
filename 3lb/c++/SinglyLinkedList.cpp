#include "SinglyLinkedList.h"
#include <sstream>
#include <algorithm>

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

SinglyLinkedList::~SinglyLinkedList() {
    clear();
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
    Node* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

SinglyLinkedList& SinglyLinkedList::operator=(const SinglyLinkedList& other) {
    if (this != &other) {
        clear();
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    return *this;
}

void SinglyLinkedList::push_front(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    listSize++;
}

void SinglyLinkedList::push_back(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    listSize++;
}

void SinglyLinkedList::pop_front() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* temp = head;
    head = head->next;
    
    if (head == nullptr) {
        tail = nullptr;
    }
    
    delete temp;
    listSize--;
}

void SinglyLinkedList::pop_back() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    listSize--;
}

void SinglyLinkedList::insert(size_t index, const std::string& value) {
    if (index > listSize) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        push_front(value);
    } else if (index == listSize) {
        push_back(value);
    } else {
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
        listSize++;
    }
}

void SinglyLinkedList::remove(size_t index) {
    if (index >= listSize) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        pop_front();
    } else {
        Node* current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        Node* nodeToDelete = current->next;
        current->next = nodeToDelete->next;
        
        if (nodeToDelete == tail) {
            tail = current;
        }
        
        delete nodeToDelete;
        listSize--;
    }
}

std::string SinglyLinkedList::get(size_t index) const {
    if (index >= listSize) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

size_t SinglyLinkedList::size() const {
    return listSize;
}

bool SinglyLinkedList::empty() const {
    return listSize == 0;
}

void SinglyLinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    listSize = 0;
}

void SinglyLinkedList::print() const {
    if (empty()) {
        std::cout << "SinglyLinkedList: [empty]" << std::endl;
        return;
    }
    
    Node* current = head;
    std::cout << "SinglyLinkedList: [";
    while (current != nullptr) {
        std::cout << "\"" << current->data << "\"";
        if (current->next != nullptr) std::cout << " -> ";
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

void SinglyLinkedList::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&listSize), sizeof(listSize));
    Node* current = head;
    while (current != nullptr) {
        size_t strLen = current->data.length();
        os.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
        os.write(current->data.c_str(), strLen);
        current = current->next;
    }
}

void SinglyLinkedList::deserialize(std::istream& is) {
    clear();
    size_t listSizeValue;
    is.read(reinterpret_cast<char*>(&listSizeValue), sizeof(listSizeValue));
    
    for (size_t i = 0; i < listSizeValue; ++i) {
        size_t strLen;
        is.read(reinterpret_cast<char*>(&strLen), sizeof(strLen));
        std::string value(strLen, ' ');
        is.read(&value[0], strLen);
        push_back(value);
    }
}

void SinglyLinkedList::serializeText(std::ostream& os) const {
    os << listSize << "\n";
    Node* current = head;
    while (current != nullptr) {
        std::string escaped = current->data;
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

void SinglyLinkedList::deserializeText(std::istream& is) {
    clear();
    size_t newSize;
    is >> newSize;
    is.get();
    
    for (size_t i = 0; i < newSize; ++i) {
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
        
        push_back(line);
    }
}

// Новые методы для тестирования
bool SinglyLinkedList::checkIntegrity() const {
    if (empty()) {
        return head == nullptr && tail == nullptr;
    }
    
    // Подсчет элементов при прямом проходе
    size_t count = 0;
    Node* current = head;
    const Node* last = nullptr;
    
    while (current != nullptr) {
        count++;
        last = current;
        current = current->next;
    }
    
    return count == listSize && last == tail;
}

std::vector<std::string> SinglyLinkedList::toVector() const {
    std::vector<std::string> result;
    Node* current = head;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

bool SinglyLinkedList::contains(const std::string& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}