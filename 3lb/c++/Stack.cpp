#include "Stack.h"
#include <stdexcept>

Stack::Stack() : list() {}

void Stack::push(const std::string& value) {
    list.push_back(value);
}

std::string Stack::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    std::string value = list.get(list.size() - 1);
    list.pop_back();
    return value;
}

std::string Stack::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty");
    }
    return list.get(list.size() - 1);
}

bool Stack::empty() const {
    return list.empty();
}

size_t Stack::size() const {
    return list.size();
}

void Stack::clear() {
    list.clear();
}

void Stack::print() const {
    if (empty()) {
        std::cout << "Stack: [empty]" << std::endl;
        return;
    }
    
    std::cout << "Stack: [";
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << "\"" << list.get(i) << "\"";
        if (i < list.size() - 1) std::cout << " | ";
    }
    std::cout << "]" << std::endl;
}

void Stack::serialize(std::ostream& os) const {
    list.serialize(os);
}

void Stack::deserialize(std::istream& is) {
    list.deserialize(is);
}

void Stack::serializeText(std::ostream& os) const {
    list.serializeText(os);
}

void Stack::deserializeText(std::istream& is) {
    list.deserializeText(is);
}