#include "Queue.h"
#include <stdexcept>

Queue::Queue() : list() {}

void Queue::enqueue(const std::string& value) {
    list.push_back(value);
}

std::string Queue::dequeue() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    std::string value = list.get(0);
    list.pop_front();
    return value;
}

std::string Queue::front() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return list.get(0);
}

std::string Queue::back() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return list.get(list.size() - 1);
}

bool Queue::empty() const {
    return list.empty();
}

size_t Queue::size() const {
    return list.size();
}

void Queue::clear() {
    list.clear();
}

void Queue::print() const {
    if (empty()) {
        std::cout << "Queue: [empty]" << std::endl;
        return;
    }
    
    std::cout << "Queue: [";
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << "\"" << list.get(i) << "\"";
        if (i < list.size() - 1) std::cout << " <- ";
    }
    std::cout << "]" << std::endl;
}

void Queue::serialize(std::ostream& os) const {
    list.serialize(os);
}

void Queue::deserialize(std::istream& is) {
    list.deserialize(is);
}

void Queue::serializeText(std::ostream& os) const {
    list.serializeText(os);
}

void Queue::deserializeText(std::istream& is) {
    list.deserializeText(is);
}