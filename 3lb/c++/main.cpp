#include <iostream>
#include <fstream>
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"
#include "ConsoleInterface.h"

using namespace std;

void demonstrateArray() {
    cout << "=== Array Demonstration ===" << endl;
    Array arr;
    arr.insert("apple");
    arr.insert("banana");
    arr.insert("cherry");
    cout << "Original array: ";
    arr.print();
    
    arr.insertAt(1, "orange");
    cout << "After insert orange at index 1: ";
    arr.print();
    
    arr.set(2, "grape");
    cout << "After set index 2 to grape: ";
    arr.print();
    
    arr.remove(0);
    cout << "After remove index 0: ";
    arr.print();
    
    cout << "Size: " << arr.size() << endl;
    cout << "Empty: " << (arr.empty() ? "true" : "false") << endl;
}

void demonstrateSinglyLinkedList() {
    cout << "\n=== Singly Linked List Demonstration ===" << endl;
    SinglyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_front("zero");
    cout << "Original list: ";
    list.print();
    
    list.insert(2, "fifteen");
    cout << "After insert fifteen at index 2: ";
    list.print();
    
    list.remove(1);
    cout << "After remove index 1: ";
    list.print();
    
    cout << "Size: " << list.size() << endl;
}

void demonstrateDoublyLinkedList() {
    cout << "\n=== Doubly Linked List Demonstration ===" << endl;
    DoublyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_front("zero");
    cout << "Original list: ";
    list.print();
    
    list.insert(2, "middle");
    cout << "After insert middle at index 2: ";
    list.print();
    
    list.remove(1);
    cout << "After remove index 1: ";
    list.print();
    
    cout << "Size: " << list.size() << endl;
    cout << "Integrity: " << (list.checkIntegrity() ? "OK" : "FAIL") << endl;
}

void demonstrateQueue() {
    cout << "\n=== Queue Demonstration ===" << endl;
    Queue q;
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");
    cout << "Queue: ";
    q.print();
    
    cout << "Dequeue: " << q.dequeue() << endl;
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;
    cout << "Size: " << q.size() << endl;
    
    cout << "After dequeue: ";
    q.print();
}

void demonstrateStack() {
    cout << "\n=== Stack Demonstration ===" << endl;
    Stack s;
    s.push("base");
    s.push("middle");
    s.push("top");
    cout << "Stack: ";
    s.print();
    
    cout << "Pop: " << s.pop() << endl;
    cout << "Top: " << s.top() << endl;
    cout << "Size: " << s.size() << endl;
    
    cout << "After pop: ";
    s.print();
}

void demonstrateHashTable() {
    cout << "\n=== HashTable Demonstration ===" << endl;
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    ht.insert(17, "David");
    ht.print();
    
    cout << "Get key 2: " << ht.get(2) << endl;
    cout << "Contains key 3: " << (ht.contains(3) ? "true" : "false") << endl;
    
    ht.remove(2);
    cout << "After remove key 2: " << endl;
    ht.print();
}

void demonstrateTree() {
    cout << "\n=== Complete Binary Tree Demonstration ===" << endl;
    CompleteBinaryTree tree;
    tree.insert("five");
    tree.insert("three");
    tree.insert("seven");
    tree.insert("one");
    tree.insert("four");
    tree.insert("six");
    tree.insert("eight");
    
    tree.print();
    
    cout << "Root: " << tree.getRoot() << endl;
    cout << "Size: " << tree.size() << endl;
    cout << "Height: " << tree.height() << endl;
    
    auto inOrder = tree.inOrder();
    cout << "In-order: ";
    for (const string& val : inOrder) {
        cout << val << " ";
    }
    cout << endl;
    
    tree.remove();
    cout << "After remove root: ";
    tree.print();
}

int main(int argc, char* argv[]) {
    ConsoleInterface interface;
    
    // Если переданы аргументы командной строки, используем консольный интерфейс
    if (argc > 1) {
        interface.runFromCommandLine(argc, argv);
        return 0;
    }
    
    // Демонстрация всех структур данных
    cout << "🚀 Демонстрация структур данных" << endl;
    cout << "=================================" << endl;
    
    demonstrateArray();
    demonstrateSinglyLinkedList();
    demonstrateDoublyLinkedList();
    demonstrateQueue();
    demonstrateStack();
    demonstrateHashTable();
    demonstrateTree();
    
    cout << "\n🎯 Запуск интерактивного режима..." << endl;
    cout << "=================================" << endl;
    
    // Запуск интерактивного режима
    interface.interactiveMode();
    
    return 0;
}