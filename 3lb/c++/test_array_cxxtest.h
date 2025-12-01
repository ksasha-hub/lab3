#include <cxxtest/TestSuite.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"

using namespace std;

// ==================== ARRAY TESTS ====================
class ArrayTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        Array arr;
        TS_ASSERT(arr.empty());
        TS_ASSERT_EQUALS(arr.size(), 0u);
    }
    
    void testConstructorWithSize() {
        Array arr(5);
        TS_ASSERT_EQUALS(arr.size(), 5u);
        TS_ASSERT(!arr.empty());
        TS_ASSERT_EQUALS(arr.get(0), "");
        TS_ASSERT_EQUALS(arr.get(4), "");
    }
    
    void testCopyConstructor() {
        Array original;
        original.insert("one");
        original.insert("two");
        
        Array copy(original);
        TS_ASSERT_EQUALS(copy.size(), original.size());
        TS_ASSERT_EQUALS(copy.get(0), "one");
        TS_ASSERT_EQUALS(copy.get(1), "two");
    }
    
    void testAssignmentOperator() {
        Array original;
        original.insert("test");
        
        Array assigned;
        assigned = original;
        TS_ASSERT_EQUALS(assigned.size(), 1u);
        TS_ASSERT_EQUALS(assigned.get(0), "test");
        
        assigned = assigned;
        TS_ASSERT_EQUALS(assigned.size(), 1u);
    }
    
    void testInsertOperations() {
        Array arr;
        
        arr.insert("first");
        TS_ASSERT_EQUALS(arr.size(), 1u);
        TS_ASSERT_EQUALS(arr.get(0), "first");
        
        arr.insert("second");
        TS_ASSERT_EQUALS(arr.size(), 2u);
        TS_ASSERT_EQUALS(arr.get(1), "second");
    }
    
    void testInsertAtOperations() {
        Array arr;
        arr.insert("A");
        arr.insert("C");
        
        arr.insertAt(1, "B");
        TS_ASSERT_EQUALS(arr.size(), 3u);
        TS_ASSERT_EQUALS(arr.get(0), "A");
        TS_ASSERT_EQUALS(arr.get(1), "B");
        TS_ASSERT_EQUALS(arr.get(2), "C");
        
        arr.insertAt(0, "start");
        TS_ASSERT_EQUALS(arr.get(0), "start");
        
        arr.insertAt(arr.size(), "end");
        TS_ASSERT_EQUALS(arr.get(arr.size() - 1), "end");
    }
    
    void testRemoveOperations() {
        Array arr;
        for (int i = 0; i < 5; i++) {
            arr.insert("item_" + to_string(i));
        }
        
        arr.remove(2);
        TS_ASSERT_EQUALS(arr.size(), 4u);
        TS_ASSERT_EQUALS(arr.get(2), "item_3");
        
        arr.remove(0);
        TS_ASSERT_EQUALS(arr.get(0), "item_1");
        
        arr.remove(arr.size() - 1);
        TS_ASSERT_EQUALS(arr.get(arr.size() - 1), "item_3");
    }
    
    void testSetAndGetOperations() {
        Array arr;
        arr.insert("original");
        
        arr.set(0, "modified");
        TS_ASSERT_EQUALS(arr.get(0), "modified");
        
        for (int i = 0; i < 3; i++) {
            arr.insert("temp_" + to_string(i));
        }
        
        arr.set(2, "changed");
        TS_ASSERT_EQUALS(arr.get(2), "changed");
    }
    
    void testClearAndEmpty() {
        Array arr;
        for (int i = 0; i < 10; i++) {
            arr.insert("clear_" + to_string(i));
        }
        
        TS_ASSERT(!arr.empty());
        arr.clear();
        TS_ASSERT(arr.empty());
        TS_ASSERT_EQUALS(arr.size(), 0u);
        
        arr.clear();
        TS_ASSERT(arr.empty());
    }
    
    void testExceptionHandling() {
        Array arr;
        
        TS_ASSERT_THROWS(arr.get(0), out_of_range);
        TS_ASSERT_THROWS(arr.set(0, "test"), out_of_range);
        TS_ASSERT_THROWS(arr.remove(0), out_of_range);
        TS_ASSERT_THROWS(arr.insertAt(1, "test"), out_of_range);
        
        arr.insert("one");
        TS_ASSERT_THROWS(arr.get(1), out_of_range);
        TS_ASSERT_THROWS(arr.set(1, "test"), out_of_range);
        TS_ASSERT_THROWS(arr.remove(1), out_of_range);
        TS_ASSERT_THROWS(arr.insertAt(2, "test"), out_of_range);
    }
    
    void testResizeOperations() {
        Array arr;
        
        for (int i = 0; i < 50; i++) {
            arr.insert("resize_" + to_string(i));
        }
        
        TS_ASSERT_EQUALS(arr.size(), 50u);
        for (int i = 0; i < 50; i++) {
            TS_ASSERT_EQUALS(arr.get(i), "resize_" + to_string(i));
        }
    }
    
    void testSerialization() {
        Array original;
        for (int i = 0; i < 5; i++) {
            original.insert("serial_" + to_string(i));
        }
        
        stringstream ss;
        original.serialize(ss);
        
        Array loaded;
        loaded.deserialize(ss);
        
        TS_ASSERT_EQUALS(loaded.size(), original.size());
        for (size_t i = 0; i < original.size(); i++) {
            TS_ASSERT_EQUALS(loaded.get(i), original.get(i));
        }
    }
    
    void testTextSerialization() {
        Array original;
        original.insert("normal");
        original.insert("text with\nnewline");
        original.insert("text with \"quotes\"");
        
        stringstream ss;
        original.serializeText(ss);
        
        Array loaded;
        loaded.deserializeText(ss);
        
        TS_ASSERT_EQUALS(loaded.size(), original.size());
        TS_ASSERT_EQUALS(loaded.get(0), "normal");
        TS_ASSERT_EQUALS(loaded.get(1), "text with\nnewline");
        TS_ASSERT_EQUALS(loaded.get(2), "text with \"quotes\"");
    }
    
    void testComplexOperations() {
        Array arr;
        
        for (int i = 0; i < 30; i++) {
            if (i % 3 == 0) {
                arr.insertAt(0, "front_" + to_string(i));
            } else if (i % 3 == 1) {
                arr.insertAt(arr.size() / 2, "middle_" + to_string(i));
            } else {
                arr.insert("back_" + to_string(i));
            }
        }
        
        TS_ASSERT(arr.size() > 0);
        
        while (!arr.empty()) {
            if (arr.size() % 2 == 0) {
                arr.remove(0);
            } else {
                arr.remove(arr.size() - 1);
            }
        }
        
        TS_ASSERT(arr.empty());
    }
};

// ==================== SINGLY LINKED LIST TESTS ====================
class SinglyLinkedListTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        SinglyLinkedList list;
        TS_ASSERT(list.empty());
        TS_ASSERT_EQUALS(list.size(), 0u);
    }
    
    void testPushOperations() {
        SinglyLinkedList list;
        
        list.push_front("front");
        TS_ASSERT_EQUALS(list.size(), 1u);
        TS_ASSERT_EQUALS(list.get(0), "front");
        
        list.push_back("back");
        TS_ASSERT_EQUALS(list.size(), 2u);
        TS_ASSERT_EQUALS(list.get(1), "back");
    }
    
    void testPopOperations() {
        SinglyLinkedList list;
        list.push_back("one");
        list.push_back("two");
        list.push_back("three");
        
        list.pop_front();
        TS_ASSERT_EQUALS(list.size(), 2u);
        TS_ASSERT_EQUALS(list.get(0), "two");
        
        list.pop_back();
        TS_ASSERT_EQUALS(list.size(), 1u);
        TS_ASSERT_EQUALS(list.get(0), "two");
        
        list.pop_front();
        TS_ASSERT(list.empty());
    }
    
    void testInsertOperations() {
        SinglyLinkedList list;
        list.push_back("A");
        list.push_back("C");
        
        list.insert(1, "B");
        TS_ASSERT_EQUALS(list.size(), 3u);
        TS_ASSERT_EQUALS(list.get(1), "B");
        
        list.insert(0, "start");
        TS_ASSERT_EQUALS(list.get(0), "start");
        
        list.insert(list.size(), "end");
        TS_ASSERT_EQUALS(list.get(list.size() - 1), "end");
    }
    
    void testRemoveOperations() {
        SinglyLinkedList list;
        for (int i = 0; i < 5; i++) {
            list.push_back("item_" + to_string(i));
        }
        
        list.remove(2);
        TS_ASSERT_EQUALS(list.size(), 4u);
        TS_ASSERT_EQUALS(list.get(2), "item_3");
        
        list.remove(0);
        TS_ASSERT_EQUALS(list.get(0), "item_1");
        
        list.remove(list.size() - 1);
        TS_ASSERT_EQUALS(list.get(list.size() - 1), "item_3");
    }
    
    void testCopyAndAssignment() {
        SinglyLinkedList original;
        original.push_back("one");
        original.push_back("two");
        
        SinglyLinkedList copy(original);
        TS_ASSERT_EQUALS(copy.size(), original.size());
        TS_ASSERT_EQUALS(copy.get(0), "one");
        TS_ASSERT_EQUALS(copy.get(1), "two");
        
        SinglyLinkedList assigned;
        assigned = original;
        TS_ASSERT_EQUALS(assigned.size(), original.size());
        
        assigned = assigned;
        TS_ASSERT_EQUALS(assigned.size(), original.size());
    }
    
    void testClearAndEmpty() {
        SinglyLinkedList list;
        for (int i = 0; i < 5; i++) {
            list.push_back("clear_" + to_string(i));
        }
        
        TS_ASSERT(!list.empty());
        list.clear();
        TS_ASSERT(list.empty());
        TS_ASSERT_EQUALS(list.size(), 0u);
    }
    
    void testExceptionHandling() {
        SinglyLinkedList list;
        
        TS_ASSERT_THROWS(list.get(0), out_of_range);
        TS_ASSERT_THROWS(list.remove(0), out_of_range);
        TS_ASSERT_THROWS(list.insert(1, "test"), out_of_range);
        TS_ASSERT_THROWS(list.pop_front(), runtime_error);
        TS_ASSERT_THROWS(list.pop_back(), runtime_error);
        
        list.push_back("one");
        TS_ASSERT_THROWS(list.get(1), out_of_range);
        TS_ASSERT_THROWS(list.remove(1), out_of_range);
        TS_ASSERT_THROWS(list.insert(2, "test"), out_of_range);
    }
    
    void testSerialization() {
        SinglyLinkedList original;
        for (int i = 0; i < 5; i++) {
            original.push_back("serial_" + to_string(i));
        }
        
        stringstream ss;
        original.serialize(ss);
        
        SinglyLinkedList loaded;
        loaded.deserialize(ss);
        
        TS_ASSERT_EQUALS(loaded.size(), original.size());
        for (size_t i = 0; i < original.size(); i++) {
            TS_ASSERT_EQUALS(loaded.get(i), original.get(i));
        }
    }
    
    void testIntegrityChecking() {
        SinglyLinkedList list;
        TS_ASSERT(list.checkIntegrity());
        
        list.push_back("test");
        TS_ASSERT(list.checkIntegrity());
        
        list.push_front("front");
        TS_ASSERT(list.checkIntegrity());
        
        list.pop_back();
        TS_ASSERT(list.checkIntegrity());
    }
    
    void testContainsMethod() {
        SinglyLinkedList list;
        TS_ASSERT(!list.contains("test"));
        
        list.push_back("apple");
        list.push_back("banana");
        
        TS_ASSERT(list.contains("apple"));
        TS_ASSERT(list.contains("banana"));
        TS_ASSERT(!list.contains("cherry"));
    }
    
    void testToVectorMethod() {
        SinglyLinkedList list;
        list.push_back("one");
        list.push_back("two");
        list.push_back("three");
        
        vector<string> vec = list.toVector();
        TS_ASSERT_EQUALS(vec.size(), 3u);
        TS_ASSERT_EQUALS(vec[0], "one");
        TS_ASSERT_EQUALS(vec[1], "two");
        TS_ASSERT_EQUALS(vec[2], "three");
    }
    
    void testComplexOperations() {
        SinglyLinkedList list;
        
        for (int i = 0; i < 20; i++) {
            if (i % 4 == 0) {
                list.push_front("front_" + to_string(i));
            } else if (i % 4 == 1) {
                list.push_back("back_" + to_string(i));
            } else if (i % 4 == 2) {
                if (!list.empty()) {
                    list.insert(list.size() / 2, "middle_" + to_string(i));
                }
            } else {
                if (!list.empty()) {
                    size_t pos = i % list.size();
                    list.insert(pos, "random_" + to_string(i));
                }
            }
            TS_ASSERT(list.checkIntegrity());
        }
        
        TS_ASSERT(list.size() > 0);
    }
};

// ==================== DOUBLY LINKED LIST TESTS ====================
class DoublyLinkedListTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        DoublyLinkedList list;
        TS_ASSERT(list.empty());
        TS_ASSERT_EQUALS(list.size(), 0u);
    }
    
    void testPushOperations() {
        DoublyLinkedList list;
        
        list.push_front("front");
        TS_ASSERT_EQUALS(list.size(), 1u);
        TS_ASSERT_EQUALS(list.get(0), "front");
        
        list.push_back("back");
        TS_ASSERT_EQUALS(list.size(), 2u);
        TS_ASSERT_EQUALS(list.get(1), "back");
    }
    
    void testPopOperations() {
        DoublyLinkedList list;
        list.push_back("one");
        list.push_back("two");
        list.push_back("three");
        
        list.pop_front();
        TS_ASSERT_EQUALS(list.size(), 2u);
        TS_ASSERT_EQUALS(list.get(0), "two");
        
        list.pop_back();
        TS_ASSERT_EQUALS(list.size(), 1u);
        TS_ASSERT_EQUALS(list.get(0), "two");
        
        list.pop_front();
        TS_ASSERT(list.empty());
    }
    
    void testInsertOperations() {
        DoublyLinkedList list;
        list.push_back("A");
        list.push_back("C");
        
        list.insert(1, "B");
        TS_ASSERT_EQUALS(list.size(), 3u);
        TS_ASSERT_EQUALS(list.get(1), "B");
        
        list.insert(0, "start");
        TS_ASSERT_EQUALS(list.get(0), "start");
        
        list.insert(list.size(), "end");
        TS_ASSERT_EQUALS(list.get(list.size() - 1), "end");
    }
    
    void testRemoveOperations() {
        DoublyLinkedList list;
        for (int i = 0; i < 5; i++) {
            list.push_back("item_" + to_string(i));
        }
        
        list.remove(2);
        TS_ASSERT_EQUALS(list.size(), 4u);
        TS_ASSERT_EQUALS(list.get(2), "item_3");
        
        list.remove(0);
        TS_ASSERT_EQUALS(list.get(0), "item_1");
        
        list.remove(list.size() - 1);
        TS_ASSERT_EQUALS(list.get(list.size() - 1), "item_3");
    }
    
    void testCopyAndAssignment() {
        DoublyLinkedList original;
        original.push_back("one");
        original.push_back("two");
        
        DoublyLinkedList copy(original);
        TS_ASSERT_EQUALS(copy.size(), original.size());
        TS_ASSERT_EQUALS(copy.get(0), "one");
        TS_ASSERT_EQUALS(copy.get(1), "two");
        
        DoublyLinkedList assigned;
        assigned = original;
        TS_ASSERT_EQUALS(assigned.size(), original.size());
    }
    
    void testIntegrityChecking() {
        DoublyLinkedList list;
        TS_ASSERT(list.checkIntegrity());
        
        list.push_back("test");
        TS_ASSERT(list.checkIntegrity());
        
        list.push_front("front");
        TS_ASSERT(list.checkIntegrity());
        
        list.pop_back();
        TS_ASSERT(list.checkIntegrity());
    }
    
    void testToVectorMethod() {
        DoublyLinkedList list;
        list.push_back("one");
        list.push_back("two");
        list.push_back("three");
        
        vector<string> vec = list.toVector();
        TS_ASSERT_EQUALS(vec.size(), 3u);
        TS_ASSERT_EQUALS(vec[0], "one");
        TS_ASSERT_EQUALS(vec[1], "two");
        TS_ASSERT_EQUALS(vec[2], "three");
    }
    
    void testBoundaryOperations() {
        DoublyLinkedList list;
        
        list.insert(0, "first");
        TS_ASSERT_EQUALS(list.size(), 1u);
        TS_ASSERT_EQUALS(list.get(0), "first");
        
        list.insert(1, "last");
        TS_ASSERT_EQUALS(list.size(), 2u);
        TS_ASSERT_EQUALS(list.get(1), "last");
        
        list.remove(0);
        TS_ASSERT_EQUALS(list.size(), 1u);
        TS_ASSERT_EQUALS(list.get(0), "last");
        
        list.remove(0);
        TS_ASSERT(list.empty());
    }
};

// ==================== QUEUE TESTS ====================
class QueueTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        Queue q;
        TS_ASSERT(q.empty());
        TS_ASSERT_EQUALS(q.size(), 0u);
    }
    
    void testEnqueueDequeue() {
        Queue q;
        
        q.enqueue("first");
        q.enqueue("second");
        q.enqueue("third");
        
        TS_ASSERT_EQUALS(q.size(), 3u);
        TS_ASSERT_EQUALS(q.front(), "first");
        TS_ASSERT_EQUALS(q.back(), "third");
        
        TS_ASSERT_EQUALS(q.dequeue(), "first");
        TS_ASSERT_EQUALS(q.dequeue(), "second");
        TS_ASSERT_EQUALS(q.dequeue(), "third");
        TS_ASSERT(q.empty());
    }
    
    void testExceptionHandling() {
        Queue q;
        
        TS_ASSERT_THROWS(q.front(), runtime_error);
        TS_ASSERT_THROWS(q.back(), runtime_error);
        TS_ASSERT_THROWS(q.dequeue(), runtime_error);
    }
    
    void testClearAndEmpty() {
        Queue q;
        for (int i = 0; i < 5; i++) {
            q.enqueue("item_" + to_string(i));
        }
        
        TS_ASSERT(!q.empty());
        q.clear();
        TS_ASSERT(q.empty());
    }
    
    void testSerialization() {
        Queue original;
        original.enqueue("one");
        original.enqueue("two");
        original.enqueue("three");
        
        stringstream ss;
        original.serialize(ss);
        
        Queue loaded;
        loaded.deserialize(ss);
        
        TS_ASSERT_EQUALS(loaded.size(), original.size());
        while (!original.empty() && !loaded.empty()) {
            TS_ASSERT_EQUALS(loaded.dequeue(), original.dequeue());
        }
    }
};

// ==================== STACK TESTS ====================
class StackTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        Stack s;
        TS_ASSERT(s.empty());
        TS_ASSERT_EQUALS(s.size(), 0u);
    }
    
    void testPushPop() {
        Stack s;
        
        s.push("first");
        s.push("second");
        s.push("third");
        
        TS_ASSERT_EQUALS(s.size(), 3u);
        TS_ASSERT_EQUALS(s.top(), "third");
        
        TS_ASSERT_EQUALS(s.pop(), "third");
        TS_ASSERT_EQUALS(s.pop(), "second");
        TS_ASSERT_EQUALS(s.pop(), "first");
        TS_ASSERT(s.empty());
    }
    
    void testExceptionHandling() {
        Stack s;
        
        TS_ASSERT_THROWS(s.top(), runtime_error);
        TS_ASSERT_THROWS(s.pop(), runtime_error);
    }
    
    void testClearAndEmpty() {
        Stack s;
        for (int i = 0; i < 5; i++) {
            s.push("item_" + to_string(i));
        }
        
        TS_ASSERT(!s.empty());
        s.clear();
        TS_ASSERT(s.empty());
    }
    
    void testSerialization() {
        Stack original;
        original.push("one");
        original.push("two");
        original.push("three");
        
        stringstream ss;
        original.serialize(ss);
        
        Stack loaded;
        loaded.deserialize(ss);
        
        TS_ASSERT_EQUALS(loaded.size(), original.size());
        while (!original.empty() && !loaded.empty()) {
            TS_ASSERT_EQUALS(loaded.pop(), original.pop());
        }
    }
};

// ==================== HASH TABLE TESTS ====================
class HashTableTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        HashTable ht;
        TS_ASSERT(ht.empty());
        TS_ASSERT_EQUALS(ht.size(), 0u);
    }
    
    void testConstructorWithCapacity() {
        HashTable ht(15);
        TS_ASSERT(ht.empty());
        TS_ASSERT(ht.getCapacity() >= 15u);
    }
    
    void testInsertAndGet() {
        HashTable ht;
        
        ht.insert(1, "Alice");
        ht.insert(2, "Bob");
        ht.insert(3, "Charlie");
        
        TS_ASSERT_EQUALS(ht.size(), 3u);
        TS_ASSERT_EQUALS(ht.get(1), "Alice");
        TS_ASSERT_EQUALS(ht.get(2), "Bob");
        TS_ASSERT_EQUALS(ht.get(3), "Charlie");
    }
    
    void testUpdateOperations() {
        HashTable ht;
        ht.insert(1, "original");
        TS_ASSERT_EQUALS(ht.get(1), "original");
        
        ht.insert(1, "updated");
        TS_ASSERT_EQUALS(ht.size(), 1u);
        TS_ASSERT_EQUALS(ht.get(1), "updated");
    }
    
    void testRemoveOperations() {
        HashTable ht;
        ht.insert(1, "one");
        ht.insert(2, "two");
        ht.insert(3, "three");
        
        TS_ASSERT(ht.remove(2));
        TS_ASSERT_EQUALS(ht.size(), 2u);
        TS_ASSERT(!ht.contains(2));
        
        TS_ASSERT(!ht.remove(999));
        TS_ASSERT_EQUALS(ht.size(), 2u);
    }
    
    void testContainsOperations() {
        HashTable ht;
        TS_ASSERT(!ht.contains(1));
        
        ht.insert(1, "test");
        TS_ASSERT(ht.contains(1));
        
        ht.remove(1);
        TS_ASSERT(!ht.contains(1));
    }
    
    void testExceptionHandling() {
        HashTable ht;
        TS_ASSERT_THROWS(ht.get(999), runtime_error);
        
        ht.insert(1, "test");
        TS_ASSERT_EQUALS(ht.get(1), "test");
        
        ht.remove(1);
        TS_ASSERT_THROWS(ht.get(1), runtime_error);
    }
    
    void testRehashing() {
        HashTable ht(4);
        
        for (int i = 0; i < 15; i++) {
            ht.insert(i, "value_" + to_string(i));
        }
        
        TS_ASSERT_EQUALS(ht.size(), 15u);
        for (int i = 0; i < 15; i++) {
            TS_ASSERT(ht.contains(i));
            TS_ASSERT_EQUALS(ht.get(i), "value_" + to_string(i));
        }
    }
    
    void testChainStatistics() {
        HashTable ht(8);
        for (int i = 0; i < 12; i++) {
            ht.insert(i, "chain_" + to_string(i));
        }
        
        size_t longest = ht.getLongestChain();
        size_t shortest = ht.getShortestChain();
        
        TS_ASSERT(longest >= shortest);
        TS_ASSERT(longest > 0u);
    }
    
    void testIntegrityChecking() {
        HashTable ht;
        TS_ASSERT(ht.checkIntegrity());
        
        for (int i = 0; i < 8; i++) {
            ht.insert(i, "test_" + to_string(i));
            TS_ASSERT(ht.checkIntegrity());
        }
        
        for (int i = 0; i < 4; i++) {
            ht.remove(i);
            TS_ASSERT(ht.checkIntegrity());
        }
    }
    
    void testGetAllKeys() {
        HashTable ht;
        ht.insert(1, "one");
        ht.insert(2, "two");
        ht.insert(3, "three");
        
        vector<int> keys = ht.getAllKeys();
        TS_ASSERT_EQUALS(keys.size(), 3u);
        TS_ASSERT_DIFFERS(find(keys.begin(), keys.end(), 1), keys.end());
        TS_ASSERT_DIFFERS(find(keys.begin(), keys.end(), 2), keys.end());
        TS_ASSERT_DIFFERS(find(keys.begin(), keys.end(), 3), keys.end());
    }
};

// ==================== COMPLETE BINARY TREE TESTS ====================
class CompleteBinaryTreeTest : public CxxTest::TestSuite {
public:
    void testDefaultConstructor() {
        CompleteBinaryTree tree;
        TS_ASSERT(tree.empty());
        TS_ASSERT_EQUALS(tree.size(), 0u);
    }
    
    void testInsertOperations() {
        CompleteBinaryTree tree;
        
        tree.insert("five");
        tree.insert("three");
        tree.insert("seven");
        
        TS_ASSERT(!tree.empty());
        TS_ASSERT_EQUALS(tree.size(), 3u);
    }
    
    void testRemoveOperations() {
        CompleteBinaryTree tree;
        
        for (int i = 0; i < 5; i++) {
            tree.insert(to_string(i));
        }
        
        tree.remove();
        TS_ASSERT_EQUALS(tree.size(), 4u);
        
        while (!tree.empty()) {
            tree.remove();
        }
        TS_ASSERT(tree.empty());
    }
    
    void testGetRootOperations() {
        CompleteBinaryTree tree;
        
        TS_ASSERT_THROWS(tree.getRoot(), runtime_error);
        
        tree.insert("root");
        TS_ASSERT_EQUALS(tree.getRoot(), "root");
        
        tree.insert("child");
        string root = tree.getRoot();
        TS_ASSERT(!root.empty());
    }
    
    void testTraversalOperations() {
        CompleteBinaryTree tree;
        
        tree.insert("4");
        tree.insert("2");
        tree.insert("6");
        tree.insert("1");
        tree.insert("3");
        tree.insert("5");
        tree.insert("7");
        
        auto level = tree.levelOrder();
        auto in = tree.inOrder();
        auto pre = tree.preOrder();
        auto post = tree.postOrder();
        
        TS_ASSERT_EQUALS(level.size(), 7u);
        TS_ASSERT_EQUALS(in.size(), 7u);
        TS_ASSERT_EQUALS(pre.size(), 7u);
        TS_ASSERT_EQUALS(post.size(), 7u);
    }
    
    void testExceptionHandling() {
        CompleteBinaryTree tree;
        
        TS_ASSERT_THROWS(tree.getRoot(), runtime_error);
        TS_ASSERT_THROWS(tree.remove(), runtime_error);
        
        tree.insert("test");
        TS_ASSERT_EQUALS(tree.getRoot(), "test");
        tree.remove();
        TS_ASSERT(tree.empty());
    }
    
    void testSerialization() {
        CompleteBinaryTree original;
        original.insert("5");
        original.insert("3");
        original.insert("7");
        
        stringstream ss;
        original.serialize(ss);
        
        CompleteBinaryTree loaded;
        loaded.deserialize(ss);
        
        TS_ASSERT_EQUALS(loaded.size(), original.size());
    }
    
    void testHeapProperty() {
        CompleteBinaryTree tree;
        
        tree.insert("z");
        tree.insert("x");
        tree.insert("y");
        tree.insert("a");
        
        string root = tree.getRoot();
        TS_ASSERT_EQUALS(root, "a");
    }
    
    void testLevelOperations() {
        CompleteBinaryTree tree;
        
        for (int i = 0; i < 7; i++) {
            tree.insert(to_string(i));
        }
        
        auto level0 = tree.getLevel(0);
        auto level1 = tree.getLevel(1);
        auto level2 = tree.getLevel(2);
        
        TS_ASSERT_EQUALS(level0.size(), 1u);
        TS_ASSERT_EQUALS(level1.size(), 2u);
        TS_ASSERT_EQUALS(level2.size(), 4u);
    }
    
    void testHeightOperations() {
        CompleteBinaryTree tree;
        TS_ASSERT_EQUALS(tree.height(), 0u);
        
        tree.insert("root");
        TS_ASSERT_EQUALS(tree.height(), 1u);
        
        tree.insert("child");
        TS_ASSERT_EQUALS(tree.height(), 2u);
    }
};

// ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ 90%+ ПОКРЫТИЯ ====================
class ExtendedQueueTest : public CxxTest::TestSuite {
public:
    void testQueueOperations() {
        Queue q;
        q.enqueue("first");
        q.enqueue("second");
        q.enqueue("third");
        
        TS_ASSERT_EQUALS(q.front(), "first");
        TS_ASSERT_EQUALS(q.back(), "third");
        TS_ASSERT_EQUALS(q.size(), 3u);
        TS_ASSERT(!q.empty());
        
        TS_ASSERT_EQUALS(q.dequeue(), "first");
        TS_ASSERT_EQUALS(q.dequeue(), "second");
        TS_ASSERT_EQUALS(q.dequeue(), "third");
        TS_ASSERT(q.empty());
    }
    
    void testQueueClear() {
        Queue q;
        for (int i = 0; i < 5; i++) {
            q.enqueue("item_" + to_string(i));
        }
        
        TS_ASSERT(!q.empty());
        q.clear();
        TS_ASSERT(q.empty());
        TS_ASSERT_EQUALS(q.size(), 0u);
    }
};

class ExtendedStackTest : public CxxTest::TestSuite {
public:
    void testStackOperations() {
        Stack s;
        s.push("first");
        s.push("second");
        s.push("third");
        
        TS_ASSERT_EQUALS(s.top(), "third");
        TS_ASSERT_EQUALS(s.size(), 3u);
        TS_ASSERT(!s.empty());
        
        TS_ASSERT_EQUALS(s.pop(), "third");
        TS_ASSERT_EQUALS(s.pop(), "second");
        TS_ASSERT_EQUALS(s.pop(), "first");
        TS_ASSERT(s.empty());
    }
    
    void testStackClear() {
        Stack s;
        for (int i = 0; i < 5; i++) {
            s.push("item_" + to_string(i));
        }
        
        TS_ASSERT(!s.empty());
        s.clear();
        TS_ASSERT(s.empty());
        TS_ASSERT_EQUALS(s.size(), 0u);
    }
};

class ExtendedTreeTest : public CxxTest::TestSuite {
public:
    void testEdgeCases() {
        CompleteBinaryTree tree;
        
        TS_ASSERT(tree.empty());
        TS_ASSERT_EQUALS(tree.size(), 0u);
        TS_ASSERT_EQUALS(tree.height(), 0u);
        TS_ASSERT_THROWS(tree.getRoot(), runtime_error);
        TS_ASSERT_THROWS(tree.remove(), runtime_error);
        
        tree.insert("single");
        TS_ASSERT_EQUALS(tree.getRoot(), "single");
        TS_ASSERT_EQUALS(tree.size(), 1u);
        TS_ASSERT_EQUALS(tree.height(), 1u);
        
        tree.remove();
        TS_ASSERT(tree.empty());
    }
    
    void testHeapPropertyComplex() {
        CompleteBinaryTree tree;
        
        tree.insert("m");
        tree.insert("a");
        tree.insert("z");
        tree.insert("b");
        
        string root = tree.getRoot();
        TS_ASSERT_EQUALS(root, "a");
        
        tree.remove();
        TS_ASSERT_LESS_THAN_EQUALS(tree.getRoot(), "z");
    }
    
    void testLevelOperationsComprehensive() {
        CompleteBinaryTree tree;
        
        for (int i = 1; i <= 7; i++) {
            tree.insert(to_string(i));
        }
        
        TS_ASSERT_EQUALS(tree.height(), 3u);
        
        auto level0 = tree.getLevel(0);
        auto level1 = tree.getLevel(1);
        auto level2 = tree.getLevel(2);
        
        TS_ASSERT_EQUALS(level0.size(), 1u);
        TS_ASSERT_EQUALS(level1.size(), 2u);
        TS_ASSERT_EQUALS(level2.size(), 4u);
        
        auto invalid = tree.getLevel(10);
        TS_ASSERT(invalid.empty());
    }
    
    void testTraversalConsistency() {
        CompleteBinaryTree tree;
        
        tree.insert("4");
        tree.insert("2");
        tree.insert("6");
        tree.insert("1");
        tree.insert("3");
        tree.insert("5");
        tree.insert("7");
        
        auto level = tree.levelOrder();
        auto in = tree.inOrder();
        auto pre = tree.preOrder();
        auto post = tree.postOrder();
        
        TS_ASSERT_EQUALS(level.size(), 7u);
        TS_ASSERT_EQUALS(in.size(), 7u);
        TS_ASSERT_EQUALS(pre.size(), 7u);
        TS_ASSERT_EQUALS(post.size(), 7u);
        
        for (const string& val : {"1", "2", "3", "4", "5", "6", "7"}) {
            TS_ASSERT_DIFFERS(find(level.begin(), level.end(), val), level.end());
            TS_ASSERT_DIFFERS(find(in.begin(), in.end(), val), in.end());
            TS_ASSERT_DIFFERS(find(pre.begin(), pre.end(), val), pre.end());
            TS_ASSERT_DIFFERS(find(post.begin(), post.end(), val), post.end());
        }
    }
};

// ==================== COMPREHENSIVE TESTS ====================
class ComprehensiveTest : public CxxTest::TestSuite {
public:
    void testAllStructuresIntegration() {
        Array arr;
        SinglyLinkedList sll;
        DoublyLinkedList dll;
        Queue q;
        Stack s;
        HashTable ht;
        CompleteBinaryTree tree;
        
        for (int i = 0; i < 5; i++) {
            string value = "test_" + to_string(i);
            arr.insert(value);
            sll.push_back(value);
            dll.push_back(value);
            q.enqueue(value);
            s.push(value);
            ht.insert(i, value);
            tree.insert(value);
        }
        
        TS_ASSERT_EQUALS(arr.size(), 5u);
        TS_ASSERT_EQUALS(sll.size(), 5u);
        TS_ASSERT_EQUALS(dll.size(), 5u);
        TS_ASSERT_EQUALS(q.size(), 5u);
        TS_ASSERT_EQUALS(s.size(), 5u);
        TS_ASSERT_EQUALS(ht.size(), 5u);
        TS_ASSERT_EQUALS(tree.size(), 5u);
        
        TS_ASSERT(sll.checkIntegrity());
        TS_ASSERT(dll.checkIntegrity());
        TS_ASSERT(ht.checkIntegrity());
    }
    
    void testSerializationAllStructures() {
        Array arr;
        SinglyLinkedList sll;
        DoublyLinkedList dll;
        Queue q;
        Stack s;
        HashTable ht;
        CompleteBinaryTree tree;
        
        for (int i = 0; i < 3; i++) {
            string value = "serial_" + to_string(i);
            arr.insert(value);
            sll.push_back(value);
            dll.push_back(value);
            q.enqueue(value);
            s.push(value);
            ht.insert(i, value);
            tree.insert(value);
        }
        
        stringstream ss;
        arr.serialize(ss);
        sll.serialize(ss);
        dll.serialize(ss);
        q.serialize(ss);
        s.serialize(ss);
        ht.serialize(ss);
        tree.serialize(ss);
        
        Array arr2;
        SinglyLinkedList sll2;
        DoublyLinkedList dll2;
        Queue q2;
        Stack s2;
        HashTable ht2;
        CompleteBinaryTree tree2;
        
        arr2.deserialize(ss);
        sll2.deserialize(ss);
        dll2.deserialize(ss);
        q2.deserialize(ss);
        s2.deserialize(ss);
        ht2.deserialize(ss);
        tree2.deserialize(ss);
        
        TS_ASSERT_EQUALS(arr2.size(), arr.size());
        TS_ASSERT_EQUALS(sll2.size(), sll.size());
        TS_ASSERT_EQUALS(dll2.size(), dll.size());
        TS_ASSERT_EQUALS(q2.size(), q.size());
        TS_ASSERT_EQUALS(s2.size(), s.size());
        TS_ASSERT_EQUALS(ht2.size(), ht.size());
        TS_ASSERT_EQUALS(tree2.size(), tree.size());
    }
    
    void testStressTest() {
        const int COUNT = 50;
        
        SinglyLinkedList sll;
        DoublyLinkedList dll;
        HashTable ht;
        CompleteBinaryTree tree;
        
        for (int i = 0; i < COUNT; i++) {
            string value = "stress_" + to_string(i);
            sll.push_back(value);
            dll.push_back(value);
            ht.insert(i, value);
            tree.insert(value);
        }
        
        TS_ASSERT_EQUALS(sll.size(), COUNT);
        TS_ASSERT_EQUALS(dll.size(), COUNT);
        TS_ASSERT_EQUALS(ht.size(), COUNT);
        TS_ASSERT_EQUALS(tree.size(), COUNT);
        
        for (int i = 0; i < COUNT; i += 2) {
            sll.pop_front();
            dll.pop_front();
            ht.remove(i);
            if (tree.size() > 1) {
                tree.remove();
            }
        }
        
        TS_ASSERT_LESS_THAN(sll.size(), COUNT);
        TS_ASSERT_LESS_THAN(dll.size(), COUNT);
        TS_ASSERT_LESS_THAN(ht.size(), COUNT);
        TS_ASSERT_LESS_THAN(tree.size(), COUNT);
    }
    
    void testBoundaryConditions() {
        Array emptyArr;
        SinglyLinkedList emptySll;
        DoublyLinkedList emptyDll;
        Queue emptyQ;
        Stack emptyS;
        HashTable emptyHt;
        CompleteBinaryTree emptyTree;
        
        TS_ASSERT(emptyArr.empty());
        TS_ASSERT(emptySll.empty());
        TS_ASSERT(emptyDll.empty());
        TS_ASSERT(emptyQ.empty());
        TS_ASSERT(emptyS.empty());
        TS_ASSERT(emptyHt.empty());
        TS_ASSERT(emptyTree.empty());
        
        TS_ASSERT_THROWS(emptySll.pop_front(), runtime_error);
        TS_ASSERT_THROWS(emptyDll.pop_front(), runtime_error);
        TS_ASSERT_THROWS(emptyQ.dequeue(), runtime_error);
        TS_ASSERT_THROWS(emptyS.pop(), runtime_error);
        TS_ASSERT_THROWS(emptyTree.remove(), runtime_error);
        TS_ASSERT_THROWS(emptyHt.get(1), runtime_error);
    }
};