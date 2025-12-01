#include "DoublyLinkedList.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), listSize(0) {
    Node* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& other) {
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

void DoublyLinkedList::push_front(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (empty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    listSize++;
}

void DoublyLinkedList::push_back(const std::string& value) {
    Node* newNode = new Node(value);
    
    if (empty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
}

void DoublyLinkedList::pop_front() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* temp = head;
    head = head->next;
    
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr; // Список стал пустым
    }
    
    delete temp;
    listSize--;
}

void DoublyLinkedList::pop_back() {
    if (empty()) {
        throw std::runtime_error("List is empty");
    }
    
    Node* temp = tail;
    tail = tail->prev;
    
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr; // Список стал пустым
    }
    
    delete temp;
    listSize--;
}

void DoublyLinkedList::insert(size_t index, const std::string& value) {
    if (index > listSize) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        push_front(value);
    } else if (index == listSize) {
        push_back(value);
    } else {
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        Node* newNode = new Node(value);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        
        listSize++;
    }
}

void DoublyLinkedList::remove(size_t index) {
    if (index >= listSize) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        pop_front();
    } else if (index == listSize - 1) {
        pop_back();
    } else {
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
        listSize--;
    }
}

std::string DoublyLinkedList::get(size_t index) const {
    if (index >= listSize) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

size_t DoublyLinkedList::size() const {
    return listSize;
}

bool DoublyLinkedList::empty() const {
    return listSize == 0;
}

void DoublyLinkedList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    listSize = 0;
}

void DoublyLinkedList::print() const {
    if (empty()) {
        std::cout << "DoublyLinkedList: [empty]" << std::endl;
        return;
    }
    
    Node* current = head;
    std::cout << "DoublyLinkedList: [";
    while (current != nullptr) {
        std::cout << "\"" << current->data << "\"";
        if (current->next != nullptr) std::cout << " <-> ";
        current = current->next;
    }
    std::cout << "]" << std::endl;
}

void DoublyLinkedList::serialize(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&listSize), sizeof(listSize));
    Node* current = head;
    while (current != nullptr) {
        size_t strLen = current->data.length();
        os.write(reinterpret_cast<const char*>(&strLen), sizeof(strLen));
        os.write(current->data.c_str(), strLen);
        current = current->next;
    }
}

void DoublyLinkedList::deserialize(std::istream& is) {
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

void DoublyLinkedList::serializeText(std::ostream& os) const {
    os << listSize << "\n";
    Node* current = head;
    while (current != nullptr) {
        // Экранируем специальные символы
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

void DoublyLinkedList::deserializeText(std::istream& is) {
    clear();
    size_t newSize;
    is >> newSize;
    is.get(); // Пропускаем перевод строки
    
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
        
        push_back(line);
    }
}

// Новые методы для лучшего тестирования
bool DoublyLinkedList::checkIntegrity() const {
    if (empty()) {
        return head == nullptr && tail == nullptr;
    }
    
    // Проверка прямого прохода
    size_t forwardCount = 0;
    Node* current = head;
    const Node* last = nullptr;
    
    while (current != nullptr) {
        forwardCount++;
        last = current;
        current = current->next;
    }
    
    // Проверка обратного прохода
    size_t backwardCount = 0;
    current = tail;
    
    while (current != nullptr) {
        backwardCount++;
        current = current->prev;
    }
    
    return forwardCount == listSize && 
           backwardCount == listSize && 
           last == tail;
}

std::vector<std::string> DoublyLinkedList::toVector() const {
    std::vector<std::string> result;
    Node* current = head;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}