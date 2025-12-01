#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

#include "Array.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>

class CompleteBinaryTree {
private:
    Array tree;
    
    static size_t parent(size_t index);
    static size_t leftChild(size_t index);
    static size_t rightChild(size_t index);
    bool isLeaf(size_t index) const;
    
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
    
    void inOrder(size_t index, std::vector<std::string>& result) const;
    void preOrder(size_t index, std::vector<std::string>& result) const;
    void postOrder(size_t index, std::vector<std::string>& result) const;

public:
    CompleteBinaryTree();
    
    void insert(const std::string& value);
    void remove();
    std::string getRoot() const;
    size_t size() const;
    bool empty() const;
    
    std::vector<std::string> levelOrder() const;
    std::vector<std::string> inOrder() const;
    std::vector<std::string> preOrder() const;
    std::vector<std::string> postOrder() const;
    
    std::vector<std::string> getLevel(size_t level) const;
    bool isComplete() const;
    size_t height() const;
    
    void clear();
    void print() const;
    
    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);
    
    void serializeText(std::ostream& os) const;
    void deserializeText(std::istream& is);
};

#endif