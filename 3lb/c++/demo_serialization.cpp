#include <iostream>
#include <fstream>
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"
#include "SerializationUtils.h"

using namespace std;

void demonstrateArraySerialization() {
    cout << "=== Array Serialization Demo ===" << endl;
    
    Array arr;
    arr.insert("Hello");
    arr.insert("World");
    arr.insert("Test\nwith\nnewlines");
    arr.insert("Text with \"quotes\"");
    arr.insert("Back\\slash");
    
    cout << "Original array: ";
    arr.print();
    
    // Text serialization
    SerializationUtils::saveToTextFile(arr, "array_text.txt");
    SerializationUtils::saveToBinaryFile(arr, "array_binary.bin");
    
    Array arrFromText;
    Array arrFromBinary;
    
    SerializationUtils::loadFromTextFile(arrFromText, "array_text.txt");
    SerializationUtils::loadFromBinaryFile(arrFromBinary, "array_binary.bin");
    
    cout << "Array from text file: ";
    arrFromText.print();
    
    cout << "Array from binary file: ";
    arrFromBinary.print();
    
    cout << endl;
}

void demonstrateLinkedListSerialization() {
    cout << "=== Linked List Serialization Demo ===" << endl;
    
    SinglyLinkedList list;
    list.push_back("First");
    list.push_back("Second");
    list.push_back("Third with\nnewline");
    list.push_back("Fourth with \"quotes\"");
    list.push_back("Fifth with back\\slash");
    
    cout << "Original list: ";
    list.print();
    
    // Text serialization
    SerializationUtils::saveToTextFile(list, "list_text.txt");
    SerializationUtils::saveToBinaryFile(list, "list_binary.bin");
    
    SinglyLinkedList listFromText;
    SinglyLinkedList listFromBinary;
    
    SerializationUtils::loadFromTextFile(listFromText, "list_text.txt");
    SerializationUtils::loadFromBinaryFile(listFromBinary, "list_binary.bin");
    
    cout << "List from text file: ";
    listFromText.print();
    
    cout << "List from binary file: ";
    listFromBinary.print();
    
    cout << endl;
}

void demonstrateHashTableSerialization() {
    cout << "=== Hash Table Serialization Demo ===" << endl;
    
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie\nwith newline");
    ht.insert(4, "David with \"quotes\"");
    ht.insert(5, "Eve with back\\slash");
    
    cout << "Original hash table:" << endl;
    ht.print();
    
    // Text serialization
    SerializationUtils::saveToTextFile(ht, "hashtable_text.txt");
    SerializationUtils::saveToBinaryFile(ht, "hashtable_binary.bin");
    
    HashTable htFromText;
    HashTable htFromBinary;
    
    SerializationUtils::loadFromTextFile(htFromText, "hashtable_text.txt");
    SerializationUtils::loadFromBinaryFile(htFromBinary, "hashtable_binary.bin");
    
    cout << "Hash table from text file:" << endl;
    htFromText.print();
    
    cout << "Hash table from binary file:" << endl;
    htFromBinary.print();
    
    cout << endl;
}

void demonstrateTreeSerialization() {
    cout << "=== Complete Binary Tree Serialization Demo ===" << endl;
    
    CompleteBinaryTree tree;
    tree.insert("Root");
    tree.insert("Left\nChild");
    tree.insert("Right \"Child\"");
    tree.insert("Left-Left");
    tree.insert("Left-Right");
    tree.insert("Right-Left");
    tree.insert("Right-Right");
    
    cout << "Original tree: ";
    tree.print();
    
    cout << "Level order: ";
    auto level = tree.levelOrder();
    for (const auto& val : level) {
        cout << val << " ";
    }
    cout << endl;
    
    // Text serialization
    SerializationUtils::saveToTextFile(tree, "tree_text.txt");
    SerializationUtils::saveToBinaryFile(tree, "tree_binary.bin");
    
    CompleteBinaryTree treeFromText;
    CompleteBinaryTree treeFromBinary;
    
    SerializationUtils::loadFromTextFile(treeFromText, "tree_text.txt");
    SerializationUtils::loadFromBinaryFile(treeFromBinary, "tree_binary.bin");
    
    cout << "Tree from text file: ";
    treeFromText.print();
    
    cout << "Tree from binary file: ";
    treeFromBinary.print();
    
    cout << endl;
}

void demonstrateAllStructures() {
    cout << "=== All Structures Serialization ===" << endl;
    
    // Test all structures
    Array arr;
    SinglyLinkedList sll;
    DoublyLinkedList dll;
    Queue q;
    Stack s;
    HashTable ht;
    CompleteBinaryTree tree;
    
    // Fill with coordinated data
    for (int i = 0; i < 5; ++i) {
        string value = "item_" + to_string(i);
        arr.insert(value);
        sll.push_back(value);
        dll.push_back(value);
        q.enqueue(value);
        s.push(value);
        ht.insert(i, value);
        tree.insert(value);
    }
    
    // Save all to text files
    SerializationUtils::saveToTextFile(arr, "all_array.txt");
    SerializationUtils::saveToTextFile(sll, "all_sll.txt");
    SerializationUtils::saveToTextFile(dll, "all_dll.txt");
    SerializationUtils::saveToTextFile(q, "all_queue.txt");
    SerializationUtils::saveToTextFile(s, "all_stack.txt");
    SerializationUtils::saveToTextFile(ht, "all_hashtable.txt");
    SerializationUtils::saveToTextFile(tree, "all_tree.txt");
    
    cout << "All structures saved to text files!" << endl;
    
    // Load back
    Array arr2;
    SinglyLinkedList sll2;
    DoublyLinkedList dll2;
    Queue q2;
    Stack s2;
    HashTable ht2;
    CompleteBinaryTree tree2;
    
    SerializationUtils::loadFromTextFile(arr2, "all_array.txt");
    SerializationUtils::loadFromTextFile(sll2, "all_sll.txt");
    SerializationUtils::loadFromTextFile(dll2, "all_dll.txt");
    SerializationUtils::loadFromTextFile(q2, "all_queue.txt");
    SerializationUtils::loadFromTextFile(s2, "all_stack.txt");
    SerializationUtils::loadFromTextFile(ht2, "all_hashtable.txt");
    SerializationUtils::loadFromTextFile(tree2, "all_tree.txt");
    
    cout << "All structures loaded from text files!" << endl;
    cout << "Array size: " << arr2.size() << endl;
    cout << "SinglyLinkedList size: " << sll2.size() << endl;
    cout << "DoublyLinkedList size: " << dll2.size() << endl;
    cout << "Queue size: " << q2.size() << endl;
    cout << "Stack size: " << s2.size() << endl;
    cout << "HashTable size: " << ht2.size() << endl;
    cout << "CompleteBinaryTree size: " << tree2.size() << endl;
    
    // Verify integrity
    cout << "SinglyLinkedList integrity: " << (sll2.checkIntegrity() ? "OK" : "FAIL") << endl;
    cout << "DoublyLinkedList integrity: " << (dll2.checkIntegrity() ? "OK" : "FAIL") << endl;
    cout << "HashTable integrity: " << (ht2.checkIntegrity() ? "OK" : "FAIL") << endl;
    cout << "CompleteBinaryTree completeness: " << (tree2.isComplete() ? "OK" : "FAIL") << endl;
}

void demonstrateComplexSerialization() {
    cout << "=== Complex Serialization Scenario ===" << endl;
    
    // Create a complex data structure scenario
    HashTable userDatabase;
    userDatabase.insert(1001, "Alice Johnson");
    userDatabase.insert(1002, "Bob Smith\nSenior Developer");
    userDatabase.insert(1003, "Charlie \"The Boss\" Brown");
    userDatabase.insert(1004, "Diana Prince\\Wonder Woman");
    
    // Create user lists
    SinglyLinkedList adminUsers;
    adminUsers.push_back("admin_alice");
    adminUsers.push_back("super_bob");
    
    DoublyLinkedList regularUsers;
    regularUsers.push_back("user_charlie");
    regularUsers.push_back("user_diana");
    
    // Save complex scenario
    SerializationUtils::saveToTextFile(userDatabase, "user_database.txt");
    SerializationUtils::saveToTextFile(adminUsers, "admin_users.txt");
    SerializationUtils::saveToTextFile(regularUsers, "regular_users.txt");
    
    cout << "Complex scenario saved to files!" << endl;
    
    // Load and verify
    HashTable loadedDatabase;
    SinglyLinkedList loadedAdmins;
    DoublyLinkedList loadedRegulars;
    
    SerializationUtils::loadFromTextFile(loadedDatabase, "user_database.txt");
    SerializationUtils::loadFromTextFile(loadedAdmins, "admin_users.txt");
    SerializationUtils::loadFromTextFile(loadedRegulars, "regular_users.txt");
    
    cout << "Loaded user database:" << endl;
    loadedDatabase.print();
    
    cout << "Loaded admin users: ";
    loadedAdmins.print();
    
    cout << "Loaded regular users: ";
    loadedRegulars.print();
}

int main() {
    cout << "Data Structures Serialization Demo" << endl;
    cout << "==================================" << endl;
    
    demonstrateArraySerialization();
    demonstrateLinkedListSerialization();
    demonstrateHashTableSerialization();
    demonstrateTreeSerialization();
    demonstrateAllStructures();
    demonstrateComplexSerialization();
    
    cout << "Demo completed successfully!" << endl;
    cout << "Check generated files:" << endl;
    cout << "- array_text.txt, array_binary.bin" << endl;
    cout << "- list_text.txt, list_binary.bin" << endl;
    cout << "- hashtable_text.txt, hashtable_binary.bin" << endl;
    cout << "- tree_text.txt, tree_binary.bin" << endl;
    cout << "- all_*.txt files" << endl;
    cout << "- user_database.txt, admin_users.txt, regular_users.txt" << endl;
    
    return 0;
}