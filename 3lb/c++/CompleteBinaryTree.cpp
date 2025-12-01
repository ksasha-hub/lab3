#include "CompleteBinaryTree.h"
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <queue>
#include <cmath>

CompleteBinaryTree::CompleteBinaryTree() : tree() {}

size_t CompleteBinaryTree::parent(size_t index) {
    return (index - 1) / 2;
}

size_t CompleteBinaryTree::leftChild(size_t index) {
    return 2 * index + 1;
}

size_t CompleteBinaryTree::rightChild(size_t index) {
    return 2 * index + 2;
}

bool CompleteBinaryTree::isLeaf(size_t index) const {
    return leftChild(index) >= tree.size();
}

void CompleteBinaryTree::heapifyUp(size_t index) {
    while (index > 0 && tree.get(parent(index)) > tree.get(index)) {
        // Swap with parent
        std::string temp = tree.get(parent(index));
        tree.set(parent(index), tree.get(index));
        tree.set(index, temp);
        index = parent(index);
    }
}

void CompleteBinaryTree::heapifyDown(size_t index) {
    while (!isLeaf(index)) {
        size_t left = leftChild(index);
        size_t right = rightChild(index);
        size_t smallest = index;

        if (left < tree.size() && tree.get(left) < tree.get(smallest)) {
            smallest = left;
        }
        if (right < tree.size() && tree.get(right) < tree.get(smallest)) {
            smallest = right;
        }

        if (smallest != index) {
            std::string temp = tree.get(index);
            tree.set(index, tree.get(smallest));
            tree.set(smallest, temp);
            index = smallest;
        } else {
            break;
        }
    }
}

void CompleteBinaryTree::insert(const std::string& value) {
    tree.insert(value);
    heapifyUp(tree.size() - 1);
}

void CompleteBinaryTree::remove() {
    if (empty()) {
        throw std::runtime_error("Tree is empty");
    }
    
    if (tree.size() == 1) {
        tree.remove(tree.size() - 1);
        return;
    }
    
    // Replace root with last element
    tree.set(0, tree.get(tree.size() - 1));
    tree.remove(tree.size() - 1);
    
    // Heapify down from root
    if (!empty()) {
        heapifyDown(0);
    }
}

std::string CompleteBinaryTree::getRoot() const {
    if (empty()) {
        throw std::runtime_error("Tree is empty");
    }
    return tree.get(0);
}

size_t CompleteBinaryTree::size() const {
    return tree.size();
}

bool CompleteBinaryTree::empty() const {
    return tree.empty();
}

std::vector<std::string> CompleteBinaryTree::levelOrder() const {
    std::vector<std::string> result;
    for (size_t i = 0; i < tree.size(); ++i) {
        result.push_back(tree.get(i));
    }
    return result;
}

std::vector<std::string> CompleteBinaryTree::inOrder() const {
    std::vector<std::string> result;
    inOrder(0, result);
    return result;
}

void CompleteBinaryTree::inOrder(size_t index, std::vector<std::string>& result) const {
    if (index >= tree.size()) return;
    
    inOrder(leftChild(index), result);
    result.push_back(tree.get(index));
    inOrder(rightChild(index), result);
}

std::vector<std::string> CompleteBinaryTree::preOrder() const {
    std::vector<std::string> result;
    preOrder(0, result);
    return result;
}

void CompleteBinaryTree::preOrder(size_t index, std::vector<std::string>& result) const {
    if (index >= tree.size()) return;
    
    result.push_back(tree.get(index));
    preOrder(leftChild(index), result);
    preOrder(rightChild(index), result);
}

std::vector<std::string> CompleteBinaryTree::postOrder() const {
    std::vector<std::string> result;
    postOrder(0, result);
    return result;
}

void CompleteBinaryTree::postOrder(size_t index, std::vector<std::string>& result) const {
    if (index >= tree.size()) return;
    
    postOrder(leftChild(index), result);
    postOrder(rightChild(index), result);
    result.push_back(tree.get(index));
}

void CompleteBinaryTree::clear() {
    tree.clear();
}

void CompleteBinaryTree::print() const {
    if (empty()) {
        std::cout << "Complete Binary Tree: [empty]" << std::endl;
        return;
    }
    
    std::cout << "Complete Binary Tree (level order): ";
    auto level = levelOrder();
    for (size_t i = 0; i < level.size(); ++i) {
        std::cout << "\"" << level[i] << "\"";
        if (i < level.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
}

void CompleteBinaryTree::serialize(std::ostream& os) const {
    tree.serialize(os);
}

void CompleteBinaryTree::deserialize(std::istream& is) {
    tree.deserialize(is);
}

void CompleteBinaryTree::serializeText(std::ostream& os) const {
    tree.serializeText(os);
}

void CompleteBinaryTree::deserializeText(std::istream& is) {
    tree.deserializeText(is);
}

std::vector<std::string> CompleteBinaryTree::getLevel(size_t level) const {
    std::vector<std::string> result;
    if (level >= height()) return result;
    
    size_t start = (1 << level) - 1; // 2^level - 1
    size_t end = std::min(start + (1 << level), tree.size());
    
    for (size_t i = start; i < end; ++i) {
        result.push_back(tree.get(i));
    }
    return result;
}

bool CompleteBinaryTree::isComplete() const {
    // Array-based representation is always complete
    return true;
}

size_t CompleteBinaryTree::height() const {
    if (empty()) return 0;
    
    size_t h = 0;
    size_t nodes = 1;
    while (nodes <= tree.size()) {
        h++;
        nodes = nodes * 2;
    }
    return h;
}