#include <gtest/gtest.h>
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
TEST(ArrayTest, DefaultConstructor) {
    Array arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0u);
}

TEST(ArrayTest, ConstructorWithSize) {
    Array arr(10);
    EXPECT_EQ(arr.size(), 10u);
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.get(0), "");
    EXPECT_EQ(arr.get(9), "");
}

TEST(ArrayTest, CopyConstructor) {
    Array original;
    original.insert("one");
    original.insert("two");
    
    Array copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.get(0), "one");
    EXPECT_EQ(copy.get(1), "two");
}

TEST(ArrayTest, AssignmentOperator) {
    Array original;
    original.insert("test");
    
    Array assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), 1u);
    EXPECT_EQ(assigned.get(0), "test");
    
    assigned = assigned;
    EXPECT_EQ(assigned.size(), 1u);
}

TEST(ArrayTest, InsertOperations) {
    Array arr;
    
    arr.insert("first");
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr.get(0), "first");
    
    arr.insert("second");
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr.get(1), "second");
}

TEST(ArrayTest, InsertAtOperations) {
    Array arr;
    arr.insert("A");
    arr.insert("C");
    
    arr.insertAt(1, "B");
    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr.get(0), "A");
    EXPECT_EQ(arr.get(1), "B");
    EXPECT_EQ(arr.get(2), "C");
    
    arr.insertAt(0, "start");
    EXPECT_EQ(arr.get(0), "start");
    
    arr.insertAt(arr.size(), "end");
    EXPECT_EQ(arr.get(arr.size() - 1), "end");
}

TEST(ArrayTest, RemoveOperations) {
    Array arr;
    for (int i = 0; i < 5; i++) {
        arr.insert("item_" + to_string(i));
    }
    
    arr.remove(2);
    EXPECT_EQ(arr.size(), 4u);
    EXPECT_EQ(arr.get(2), "item_3");
    
    arr.remove(0);
    EXPECT_EQ(arr.get(0), "item_1");
    
    arr.remove(arr.size() - 1);
    EXPECT_EQ(arr.get(arr.size() - 1), "item_3");
}

TEST(ArrayTest, SetAndGetOperations) {
    Array arr;
    arr.insert("original");
    
    arr.set(0, "modified");
    EXPECT_EQ(arr.get(0), "modified");
    
    for (int i = 0; i < 3; i++) {
        arr.insert("temp_" + to_string(i));
    }
    
    arr.set(2, "changed");
    EXPECT_EQ(arr.get(2), "changed");
}

TEST(ArrayTest, ClearAndEmpty) {
    Array arr;
    for (int i = 0; i < 10; i++) {
        arr.insert("clear_" + to_string(i));
    }
    
    EXPECT_FALSE(arr.empty());
    arr.clear();
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0u);
    
    arr.clear();
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, ExceptionHandling) {
    Array arr;
    
    EXPECT_THROW(arr.get(0), out_of_range);
    EXPECT_THROW(arr.set(0, "test"), out_of_range);
    EXPECT_THROW(arr.remove(0), out_of_range);
    EXPECT_THROW(arr.insertAt(1, "test"), out_of_range);
    
    arr.insert("one");
    EXPECT_THROW(arr.get(1), out_of_range);
    EXPECT_THROW(arr.set(1, "test"), out_of_range);
    EXPECT_THROW(arr.remove(1), out_of_range);
    EXPECT_THROW(arr.insertAt(2, "test"), out_of_range);
}

TEST(ArrayTest, ResizeOperations) {
    Array arr;
    
    for (int i = 0; i < 100; i++) {
        arr.insert("resize_" + to_string(i));
    }
    
    EXPECT_EQ(arr.size(), 100u);
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(arr.get(i), "resize_" + to_string(i));
    }
}

TEST(ArrayTest, Serialization) {
    Array original;
    for (int i = 0; i < 5; i++) {
        original.insert("serial_" + to_string(i));
    }
    
    stringstream ss;
    original.serialize(ss);
    
    Array loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    for (size_t i = 0; i < original.size(); i++) {
        EXPECT_EQ(loaded.get(i), original.get(i));
    }
}

TEST(ArrayTest, SerializationEdgeCases) {
    Array empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    Array emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    
    Array single;
    single.insert("single");
    stringstream ss2;
    single.serialize(ss2);
    
    Array singleLoaded;
    singleLoaded.deserialize(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.get(0), "single");
}

TEST(ArrayTest, TextSerialization) {
    Array original;
    original.insert("normal");
    original.insert("text with\nnewline");
    original.insert("text with \"quotes\"");
    original.insert("back\\slash");
    
    stringstream ss;
    original.serializeText(ss);
    
    Array loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.get(0), "normal");
    EXPECT_EQ(loaded.get(1), "text with\nnewline");
    EXPECT_EQ(loaded.get(2), "text with \"quotes\"");
    EXPECT_EQ(loaded.get(3), "back\\slash");
}

TEST(ArrayTest, StressTest) {
    Array arr;
    
    for (int i = 0; i < 1000; i++) {
        arr.insert("stress_" + to_string(i));
    }
    EXPECT_EQ(arr.size(), 1000u);
    
    for (int i = 0; i < 500; i++) {
        arr.remove(0);
    }
    EXPECT_EQ(arr.size(), 500u);
    
    for (int i = 0; i < 250; i++) {
        arr.insert("new_" + to_string(i));
    }
    EXPECT_EQ(arr.size(), 750u);
}

TEST(ArrayTest, ComplexOperations) {
    Array arr;
    
    for (int i = 0; i < 50; i++) {
        if (i % 3 == 0) {
            arr.insertAt(0, "front_" + to_string(i));
        } else if (i % 3 == 1) {
            arr.insertAt(arr.size() / 2, "middle_" + to_string(i));
        } else {
            arr.insert("back_" + to_string(i));
        }
    }
    
    EXPECT_GT(arr.size(), 0u);
    
    while (!arr.empty()) {
        if (arr.size() % 2 == 0) {
            arr.remove(0);
        } else {
            arr.remove(arr.size() - 1);
        }
    }
    
    EXPECT_TRUE(arr.empty());
}

// ==================== SINGLY LINKED LIST TESTS ====================
TEST(SinglyLinkedListTest, DefaultConstructor) {
    SinglyLinkedList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(SinglyLinkedListTest, PushOperations) {
    SinglyLinkedList list;
    
    list.push_front("front");
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "front");
    
    list.push_back("back");
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.get(1), "back");
}

TEST(SinglyLinkedListTest, PopOperations) {
    SinglyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");
    
    list.pop_front();
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.get(0), "two");
    
    list.pop_back();
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "two");
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(SinglyLinkedListTest, InsertOperations) {
    SinglyLinkedList list;
    list.push_back("A");
    list.push_back("C");
    
    list.insert(1, "B");
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.get(1), "B");
    
    list.insert(0, "start");
    EXPECT_EQ(list.get(0), "start");
    
    list.insert(list.size(), "end");
    EXPECT_EQ(list.get(list.size() - 1), "end");
}

TEST(SinglyLinkedListTest, RemoveOperations) {
    SinglyLinkedList list;
    for (int i = 0; i < 5; i++) {
        list.push_back("item_" + to_string(i));
    }
    
    list.remove(2);
    EXPECT_EQ(list.size(), 4u);
    EXPECT_EQ(list.get(2), "item_3");
    
    list.remove(0);
    EXPECT_EQ(list.get(0), "item_1");
    
    list.remove(list.size() - 1);
    EXPECT_EQ(list.get(list.size() - 1), "item_3");
}

TEST(SinglyLinkedListTest, CopyAndAssignment) {
    SinglyLinkedList original;
    original.push_back("one");
    original.push_back("two");
    
    SinglyLinkedList copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.get(0), "one");
    EXPECT_EQ(copy.get(1), "two");
    
    SinglyLinkedList assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), original.size());
    
    assigned = assigned;
    EXPECT_EQ(assigned.size(), original.size());
}

TEST(SinglyLinkedListTest, ClearAndEmpty) {
    SinglyLinkedList list;
    for (int i = 0; i < 5; i++) {
        list.push_back("clear_" + to_string(i));
    }
    
    EXPECT_FALSE(list.empty());
    list.clear();
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(SinglyLinkedListTest, ExceptionHandling) {
    SinglyLinkedList list;
    
    EXPECT_THROW(list.get(0), out_of_range);
    EXPECT_THROW(list.remove(0), out_of_range);
    EXPECT_THROW(list.insert(1, "test"), out_of_range);
    EXPECT_THROW(list.pop_front(), runtime_error);
    EXPECT_THROW(list.pop_back(), runtime_error);
    
    list.push_back("one");
    EXPECT_THROW(list.get(1), out_of_range);
    EXPECT_THROW(list.remove(1), out_of_range);
    EXPECT_THROW(list.insert(2, "test"), out_of_range);
}

TEST(SinglyLinkedListTest, Serialization) {
    SinglyLinkedList original;
    for (int i = 0; i < 5; i++) {
        original.push_back("serial_" + to_string(i));
    }
    
    stringstream ss;
    original.serialize(ss);
    
    SinglyLinkedList loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    for (size_t i = 0; i < original.size(); i++) {
        EXPECT_EQ(loaded.get(i), original.get(i));
    }
}

TEST(SinglyLinkedListTest, IntegrityChecking) {
    SinglyLinkedList list;
    EXPECT_TRUE(list.checkIntegrity());
    
    list.push_back("test");
    EXPECT_TRUE(list.checkIntegrity());
    
    list.push_front("front");
    EXPECT_TRUE(list.checkIntegrity());
    
    list.pop_back();
    EXPECT_TRUE(list.checkIntegrity());
    
    list.pop_front();
    EXPECT_TRUE(list.checkIntegrity());
}

TEST(SinglyLinkedListTest, ContainsMethod) {
    SinglyLinkedList list;
    EXPECT_FALSE(list.contains("test"));
    
    list.push_back("apple");
    list.push_back("banana");
    
    EXPECT_TRUE(list.contains("apple"));
    EXPECT_TRUE(list.contains("banana"));
    EXPECT_FALSE(list.contains("cherry"));
    
    list.remove(0);
    EXPECT_FALSE(list.contains("apple"));
    EXPECT_TRUE(list.contains("banana"));
}

TEST(SinglyLinkedListTest, ToVectorMethod) {
    SinglyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");
    
    vector<string> vec = list.toVector();
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], "one");
    EXPECT_EQ(vec[1], "two");
    EXPECT_EQ(vec[2], "three");
}

TEST(SinglyLinkedListTest, ComplexOperations) {
    SinglyLinkedList list;
    
    for (int i = 0; i < 20; i++) {
        if (i % 4 == 0) {
            list.push_front("front_" + to_string(i));
        } else if (i % 4 == 1) {
            list.push_back("back_" + to_string(i));
        } else if (i % 4 == 2) {
            if (!list.empty()) {
                list.insert(list.size() / 2, "middle_" + to_string(i));
            } else {
                list.push_back("back_" + to_string(i));
            }
        } else {
            if (!list.empty()) {
                size_t pos = i % list.size();
                list.insert(pos, "random_" + to_string(i));
            }
        }
        EXPECT_TRUE(list.checkIntegrity());
    }
    
    EXPECT_GT(list.size(), 0u);
    
    while (!list.empty()) {
        if (list.size() > 1) {
            list.remove(list.size() / 2);
        } else {
            list.pop_front();
        }
        EXPECT_TRUE(list.checkIntegrity());
    }
}

TEST(SinglyLinkedListTest, TextSerialization) {
    SinglyLinkedList original;
    original.push_back("normal");
    original.push_back("text with\nnewline");
    original.push_back("text with \"quotes\"");
    
    stringstream ss;
    original.serializeText(ss);
    
    SinglyLinkedList loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.get(0), "normal");
    EXPECT_EQ(loaded.get(1), "text with\nnewline");
    EXPECT_EQ(loaded.get(2), "text with \"quotes\"");
}

// ==================== DOUBLY LINKED LIST TESTS ====================
TEST(DoublyLinkedListTest, DefaultConstructor) {
    DoublyLinkedList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

TEST(DoublyLinkedListTest, PushOperations) {
    DoublyLinkedList list;
    
    list.push_front("front");
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "front");
    
    list.push_back("back");
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.get(1), "back");
}

TEST(DoublyLinkedListTest, PopOperations) {
    DoublyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");
    
    list.pop_front();
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.get(0), "two");
    
    list.pop_back();
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "two");
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedListTest, InsertOperations) {
    DoublyLinkedList list;
    list.push_back("A");
    list.push_back("C");
    
    list.insert(1, "B");
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.get(1), "B");
    
    list.insert(0, "start");
    EXPECT_EQ(list.get(0), "start");
    
    list.insert(list.size(), "end");
    EXPECT_EQ(list.get(list.size() - 1), "end");
}

TEST(DoublyLinkedListTest, RemoveOperations) {
    DoublyLinkedList list;
    for (int i = 0; i < 5; i++) {
        list.push_back("item_" + to_string(i));
    }
    
    list.remove(2);
    EXPECT_EQ(list.size(), 4u);
    EXPECT_EQ(list.get(2), "item_3");
    
    list.remove(0);
    EXPECT_EQ(list.get(0), "item_1");
    
    list.remove(list.size() - 1);
    EXPECT_EQ(list.get(list.size() - 1), "item_3");
}

TEST(DoublyLinkedListTest, CopyAndAssignment) {
    DoublyLinkedList original;
    original.push_back("one");
    original.push_back("two");
    
    DoublyLinkedList copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.get(0), "one");
    EXPECT_EQ(copy.get(1), "two");
    
    DoublyLinkedList assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), original.size());
    
    assigned = assigned;
    EXPECT_EQ(assigned.size(), original.size());
}

TEST(DoublyLinkedListTest, IntegrityChecking) {
    DoublyLinkedList list;
    EXPECT_TRUE(list.checkIntegrity());
    
    list.push_back("test");
    EXPECT_TRUE(list.checkIntegrity());
    
    list.push_front("front");
    EXPECT_TRUE(list.checkIntegrity());
    
    list.pop_back();
    EXPECT_TRUE(list.checkIntegrity());
    
    list.pop_front();
    EXPECT_TRUE(list.checkIntegrity());
}

TEST(DoublyLinkedListTest, ToVectorMethod) {
    DoublyLinkedList list;
    list.push_back("one");
    list.push_back("two");
    list.push_back("three");
    
    vector<string> vec = list.toVector();
    EXPECT_EQ(vec.size(), 3u);
    EXPECT_EQ(vec[0], "one");
    EXPECT_EQ(vec[1], "two");
    EXPECT_EQ(vec[2], "three");
}

TEST(DoublyLinkedListTest, ComplexOperations) {
    DoublyLinkedList list;
    
    for (int i = 0; i < 30; i++) {
        if (i % 5 == 0) {
            list.push_front("front_" + to_string(i));
        } else if (i % 5 == 1) {
            list.push_back("back_" + to_string(i));
        } else if (i % 5 == 2) {
            if (!list.empty()) {
                list.insert(0, "new_front_" + to_string(i));
            }
        } else if (i % 5 == 3) {
            if (!list.empty()) {
                list.insert(list.size(), "new_back_" + to_string(i));
            }
        } else {
            if (!list.empty() && list.size() > 1) {
                list.insert(list.size() / 2, "middle_" + to_string(i));
            }
        }
        EXPECT_TRUE(list.checkIntegrity());
    }
    
    EXPECT_GT(list.size(), 0u);
}

TEST(DoublyLinkedListTest, BoundaryOperations) {
    DoublyLinkedList list;
    
    list.insert(0, "first");
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "first");
    
    list.insert(1, "last");
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.get(1), "last");
    
    list.remove(0);
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "last");
    
    list.remove(0);
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedListTest, TextSerialization) {
    DoublyLinkedList original;
    original.push_back("normal");
    original.push_back("multi\nline");
    original.push_back("quotes\"test");
    
    stringstream ss;
    original.serializeText(ss);
    
    DoublyLinkedList loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.get(0), "normal");
    EXPECT_EQ(loaded.get(1), "multi\nline");
    EXPECT_EQ(loaded.get(2), "quotes\"test");
}

// ==================== QUEUE TESTS ====================
TEST(QueueTest, DefaultConstructor) {
    Queue q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, EnqueueDequeue) {
    Queue q;
    
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");
    
    EXPECT_EQ(q.size(), 3u);
    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "third");
    
    EXPECT_EQ(q.dequeue(), "first");
    EXPECT_EQ(q.dequeue(), "second");
    EXPECT_EQ(q.dequeue(), "third");
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, ExceptionHandling) {
    Queue q;
    
    EXPECT_THROW(q.front(), runtime_error);
    EXPECT_THROW(q.back(), runtime_error);
    EXPECT_THROW(q.dequeue(), runtime_error);
}

TEST(QueueTest, ClearAndEmpty) {
    Queue q;
    for (int i = 0; i < 5; i++) {
        q.enqueue("item_" + to_string(i));
    }
    
    EXPECT_FALSE(q.empty());
    q.clear();
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Serialization) {
    Queue original;
    original.enqueue("one");
    original.enqueue("two");
    original.enqueue("three");
    
    stringstream ss;
    original.serialize(ss);
    
    Queue loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    while (!original.empty() && !loaded.empty()) {
        EXPECT_EQ(loaded.dequeue(), original.dequeue());
    }
}

TEST(QueueTest, ComplexOperations) {
    Queue q;
    
    for (int i = 0; i < 20; i++) {
        q.enqueue("item_" + to_string(i));
        
        if (i % 3 == 0) {
            q.dequeue();
        }
    }
    
    EXPECT_GT(q.size(), 0u);
    
    q.clear();
    EXPECT_TRUE(q.empty());
    
    for (int i = 0; i < 10; i++) {
        q.enqueue("new_" + to_string(i));
    }
    
    EXPECT_EQ(q.size(), 10u);
}

// ==================== STACK TESTS ====================
TEST(StackTest, DefaultConstructor) {
    Stack s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(StackTest, PushPop) {
    Stack s;
    
    s.push("first");
    s.push("second");
    s.push("third");
    
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s.top(), "third");
    
    EXPECT_EQ(s.pop(), "third");
    EXPECT_EQ(s.pop(), "second");
    EXPECT_EQ(s.pop(), "first");
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, ExceptionHandling) {
    Stack s;
    
    EXPECT_THROW(s.top(), runtime_error);
    EXPECT_THROW(s.pop(), runtime_error);
}

TEST(StackTest, ClearAndEmpty) {
    Stack s;
    for (int i = 0; i < 5; i++) {
        s.push("item_" + to_string(i));
    }
    
    EXPECT_FALSE(s.empty());
    s.clear();
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, Serialization) {
    Stack original;
    original.push("one");
    original.push("two");
    original.push("three");
    
    stringstream ss;
    original.serialize(ss);
    
    Stack loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    while (!original.empty() && !loaded.empty()) {
        EXPECT_EQ(loaded.pop(), original.pop());
    }
}

TEST(StackTest, ComplexOperations) {
    Stack s;
    
    for (int i = 0; i < 15; i++) {
        s.push("item_" + to_string(i));
        
        if (i % 4 == 0) {
            s.pop();
        }
    }
    
    EXPECT_GT(s.size(), 0u);
    
    string top = s.top();
    EXPECT_FALSE(top.empty());
    EXPECT_EQ(s.top(), top);
    
    s.clear();
    EXPECT_TRUE(s.empty());
    
    for (int i = 0; i < 5; i++) {
        s.push("new_" + to_string(i));
    }
    
    EXPECT_EQ(s.size(), 5u);
}

// ==================== HASH TABLE TESTS ====================
TEST(HashTableTest, DefaultConstructor) {
    HashTable ht;
    EXPECT_TRUE(ht.empty());
    EXPECT_EQ(ht.size(), 0u);
}

TEST(HashTableTest, ConstructorWithCapacity) {
    HashTable ht(20);
    EXPECT_TRUE(ht.empty());
    EXPECT_GE(ht.getCapacity(), 20u);
}

TEST(HashTableTest, InsertAndGet) {
    HashTable ht;
    
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    
    EXPECT_EQ(ht.size(), 3u);
    EXPECT_EQ(ht.get(1), "Alice");
    EXPECT_EQ(ht.get(2), "Bob");
    EXPECT_EQ(ht.get(3), "Charlie");
}

TEST(HashTableTest, UpdateOperations) {
    HashTable ht;
    ht.insert(1, "original");
    EXPECT_EQ(ht.get(1), "original");
    
    ht.insert(1, "updated");
    EXPECT_EQ(ht.size(), 1u);
    EXPECT_EQ(ht.get(1), "updated");
}

TEST(HashTableTest, RemoveOperations) {
    HashTable ht;
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(3, "three");
    
    EXPECT_TRUE(ht.remove(2));
    EXPECT_EQ(ht.size(), 2u);
    EXPECT_FALSE(ht.contains(2));
    
    EXPECT_FALSE(ht.remove(999));
    EXPECT_EQ(ht.size(), 2u);
}

TEST(HashTableTest, ContainsOperations) {
    HashTable ht;
    EXPECT_FALSE(ht.contains(1));
    
    ht.insert(1, "test");
    EXPECT_TRUE(ht.contains(1));
    
    ht.remove(1);
    EXPECT_FALSE(ht.contains(1));
}

TEST(HashTableTest, ExceptionHandling) {
    HashTable ht;
    EXPECT_THROW(ht.get(999), runtime_error);
    
    ht.insert(1, "test");
    EXPECT_NO_THROW(ht.get(1));
    
    ht.remove(1);
    EXPECT_THROW(ht.get(1), runtime_error);
}

TEST(HashTableTest, Rehashing) {
    HashTable ht(4);
    
    for (int i = 0; i < 20; i++) {
        ht.insert(i, "value_" + to_string(i));
    }
    
    EXPECT_EQ(ht.size(), 20u);
    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(ht.contains(i));
        EXPECT_EQ(ht.get(i), "value_" + to_string(i));
    }
    
    EXPECT_GT(ht.getCapacity(), 4u);
}

TEST(HashTableTest, ChainStatistics) {
    HashTable ht(8);
    for (int i = 0; i < 16; i++) {
        ht.insert(i, "chain_" + to_string(i));
    }
    
    size_t longest = ht.getLongestChain();
    size_t shortest = ht.getShortestChain();
    
    EXPECT_GE(longest, shortest);
    EXPECT_GT(longest, 0u);
}

TEST(HashTableTest, IntegrityChecking) {
    HashTable ht;
    EXPECT_TRUE(ht.checkIntegrity());
    
    for (int i = 0; i < 10; i++) {
        ht.insert(i, "test_" + to_string(i));
        EXPECT_TRUE(ht.checkIntegrity());
    }
    
    for (int i = 0; i < 5; i++) {
        ht.remove(i);
        EXPECT_TRUE(ht.checkIntegrity());
    }
}

TEST(HashTableTest, GetAllKeys) {
    HashTable ht;
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(3, "three");
    
    vector<int> keys = ht.getAllKeys();
    EXPECT_EQ(keys.size(), 3u);
    EXPECT_NE(find(keys.begin(), keys.end(), 1), keys.end());
    EXPECT_NE(find(keys.begin(), keys.end(), 2), keys.end());
    EXPECT_NE(find(keys.begin(), keys.end(), 3), keys.end());
}

TEST(HashTableTest, LoadFactor) {
    HashTable ht(10);
    EXPECT_DOUBLE_EQ(ht.loadFactor(), 0.0);
    
    ht.insert(1, "one");
    double load1 = ht.loadFactor();
    EXPECT_GT(load1, 0.0);
    EXPECT_LE(load1, 1.0);
    
    for (int i = 2; i <= 5; i++) {
        ht.insert(i, "value_" + to_string(i));
    }
    
    double load2 = ht.loadFactor();
    EXPECT_GT(load2, load1);
    EXPECT_LE(load2, 1.0);
}

TEST(HashTableTest, CollisionHandling) {
    HashTable ht(5);
    
    for (int i = 0; i < 15; i += 5) {
        ht.insert(i, "collision_" + to_string(i));
    }
    
    EXPECT_EQ(ht.size(), 3u);
    
    for (int i = 0; i < 15; i += 5) {
        EXPECT_TRUE(ht.contains(i));
        EXPECT_EQ(ht.get(i), "collision_" + to_string(i));
    }
}

TEST(HashTableTest, ComplexOperations) {
    HashTable ht;
    
    for (int i = 0; i < 50; i++) {
        ht.insert(i, "value_" + to_string(i));
        
        if (i % 7 == 0) {
            ht.remove(i - 1);
        }
        
        if (i % 10 == 0) {
            EXPECT_TRUE(ht.checkIntegrity());
        }
    }
    
    EXPECT_GT(ht.size(), 0u);
    EXPECT_TRUE(ht.checkIntegrity());
}

TEST(HashTableTest, Serialization) {
    HashTable original;
    for (int i = 0; i < 10; i++) {
        original.insert(i, "serial_" + to_string(i));
    }
    
    stringstream ss;
    original.serialize(ss);
    
    HashTable loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    for (int i = 0; i < 10; i++) {
        EXPECT_TRUE(loaded.contains(i));
        EXPECT_EQ(loaded.get(i), "serial_" + to_string(i));
    }
}

TEST(HashTableTest, TextSerialization) {
    HashTable original;
    original.insert(1, "normal");
    original.insert(2, "multi\nline");
    original.insert(3, "quotes\"here");
    
    stringstream ss;
    original.serializeText(ss);
    
    HashTable loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.get(1), "normal");
    EXPECT_EQ(loaded.get(2), "multi\nline");
    EXPECT_EQ(loaded.get(3), "quotes\"here");
}

// ==================== COMPLETE BINARY TREE TESTS ====================
TEST(CompleteBinaryTreeTest, DefaultConstructor) {
    CompleteBinaryTree tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0u);
}

TEST(CompleteBinaryTreeTest, InsertOperations) {
    CompleteBinaryTree tree;
    
    tree.insert("five");
    tree.insert("three");
    tree.insert("seven");
    
    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 3u);
}

TEST(CompleteBinaryTreeTest, RemoveOperations) {
    CompleteBinaryTree tree;
    
    for (int i = 0; i < 5; i++) {
        tree.insert(to_string(i));
    }
    
    tree.remove();
    EXPECT_EQ(tree.size(), 4u);
    
    while (!tree.empty()) {
        tree.remove();
    }
    EXPECT_TRUE(tree.empty());
}

TEST(CompleteBinaryTreeTest, GetRootOperations) {
    CompleteBinaryTree tree;
    
    EXPECT_THROW(tree.getRoot(), runtime_error);
    
    tree.insert("root");
    EXPECT_EQ(tree.getRoot(), "root");
    
    tree.insert("child");
    string root = tree.getRoot();
    EXPECT_FALSE(root.empty());
}

TEST(CompleteBinaryTreeTest, TraversalOperations) {
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
    
    EXPECT_EQ(level.size(), 7u);
    EXPECT_EQ(in.size(), 7u);
    EXPECT_EQ(pre.size(), 7u);
    EXPECT_EQ(post.size(), 7u);
    
    for (const string& val : {"1", "2", "3", "4", "5", "6", "7"}) {
        EXPECT_NE(find(level.begin(), level.end(), val), level.end());
        EXPECT_NE(find(in.begin(), in.end(), val), in.end());
        EXPECT_NE(find(pre.begin(), pre.end(), val), pre.end());
        EXPECT_NE(find(post.begin(), post.end(), val), post.end());
    }
}

TEST(CompleteBinaryTreeTest, ExceptionHandling) {
    CompleteBinaryTree tree;
    
    EXPECT_THROW(tree.getRoot(), runtime_error);
    EXPECT_THROW(tree.remove(), runtime_error);
    
    tree.insert("test");
    EXPECT_NO_THROW(tree.getRoot());
    EXPECT_NO_THROW(tree.remove());
    
    EXPECT_THROW(tree.getRoot(), runtime_error);
}

TEST(CompleteBinaryTreeTest, Serialization) {
    CompleteBinaryTree original;
    original.insert("5");
    original.insert("3");
    original.insert("7");
    original.insert("2");
    original.insert("4");
    
    stringstream ss;
    original.serialize(ss);
    
    CompleteBinaryTree loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    
    auto originalLevel = original.levelOrder();
    auto loadedLevel = loaded.levelOrder();
    EXPECT_EQ(originalLevel.size(), loadedLevel.size());
}

TEST(CompleteBinaryTreeTest, HeapProperty) {
    CompleteBinaryTree tree;
    
    tree.insert("z");
    tree.insert("x");
    tree.insert("y");
    tree.insert("a");
    tree.insert("m");
    tree.insert("b");
    
    string root = tree.getRoot();
    EXPECT_EQ(root, "a");
    
    tree.remove();
    string newRoot = tree.getRoot();
    EXPECT_LT(newRoot, "z");
}

TEST(CompleteBinaryTreeTest, LevelOperations) {
    CompleteBinaryTree tree;
    
    for (int i = 1; i <= 7; i++) {
        tree.insert(to_string(i));
    }
    
    EXPECT_EQ(tree.height(), 3u);
    
    auto level0 = tree.getLevel(0);
    auto level1 = tree.getLevel(1);
    auto level2 = tree.getLevel(2);
    
    EXPECT_EQ(level0.size(), 1u);
    EXPECT_EQ(level1.size(), 2u);
    EXPECT_EQ(level2.size(), 4u);
    
    auto invalid = tree.getLevel(10);
    EXPECT_TRUE(invalid.empty());
}

TEST(CompleteBinaryTreeTest, HeightOperations) {
    CompleteBinaryTree tree;
    EXPECT_EQ(tree.height(), 0u);
    
    tree.insert("root");
    EXPECT_EQ(tree.height(), 1u);
    
    tree.insert("child1");
    EXPECT_EQ(tree.height(), 2u);
    
    tree.insert("child2");
    EXPECT_EQ(tree.height(), 2u);
    
    tree.insert("grandchild");
    EXPECT_EQ(tree.height(), 3u);
}

TEST(CompleteBinaryTreeTest, CompletenessProperty) {
    CompleteBinaryTree tree;
    EXPECT_TRUE(tree.isComplete());
    
    for (int i = 0; i < 10; i++) {
        tree.insert(to_string(i));
        EXPECT_TRUE(tree.isComplete());
    }
}

TEST(CompleteBinaryTreeTest, ComplexOperations) {
    CompleteBinaryTree tree;
    
    for (int i = 0; i < 20; i++) {
        tree.insert("val_" + to_string(i));
        
        if (i % 4 == 0 && tree.size() > 1) {
            tree.remove();
        }
    }
    
    EXPECT_GT(tree.size(), 0u);
    EXPECT_TRUE(tree.isComplete());
    
    auto level = tree.levelOrder();
    auto in = tree.inOrder();
    auto pre = tree.preOrder();
    auto post = tree.postOrder();
    
    EXPECT_EQ(level.size(), tree.size());
    EXPECT_EQ(in.size(), tree.size());
    EXPECT_EQ(pre.size(), tree.size());
    EXPECT_EQ(post.size(), tree.size());
}

TEST(CompleteBinaryTreeTest, TextSerialization) {
    CompleteBinaryTree original;
    original.insert("normal");
    original.insert("multi\nline");
    original.insert("quotes\"test");
    
    stringstream ss;
    original.serializeText(ss);
    
    CompleteBinaryTree loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.getRoot(), original.getRoot());
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ 90%+ ПОКРЫТИЯ ====================

TEST(QueueExtendedTest, FrontBackOperations) {
    Queue q;
    q.enqueue("first");
    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "first");
    
    q.enqueue("second");
    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "second");
    
    q.enqueue("third");
    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "third");
}

TEST(QueueExtendedTest, MixedOperations) {
    Queue q;
    
    for (int i = 0; i < 10; i++) {
        q.enqueue("item_" + to_string(i));
        if (i % 3 == 0) {
            q.dequeue();
        }
    }
    
    EXPECT_GT(q.size(), 0u);
    EXPECT_FALSE(q.empty());
    
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0u);
}

TEST(QueueExtendedTest, SerializationSpecialChars) {
    Queue original;
    original.enqueue("normal");
    original.enqueue("multi\nline");
    original.enqueue("quotes\"text");
    original.enqueue("back\\slash");
    original.enqueue("");
    
    stringstream ss;
    original.serializeText(ss);
    
    Queue loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.dequeue(), "normal");
    EXPECT_EQ(loaded.dequeue(), "multi\nline");
    EXPECT_EQ(loaded.dequeue(), "quotes\"text");
    EXPECT_EQ(loaded.dequeue(), "back\\slash");
    EXPECT_EQ(loaded.dequeue(), "");
    EXPECT_TRUE(loaded.empty());
}

TEST(QueueExtendedTest, PrintOperations) {
    Queue q;
    
    testing::internal::CaptureStdout();
    q.print();
    string emptyOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(emptyOutput.empty());
    
    q.enqueue("test");
    testing::internal::CaptureStdout();
    q.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("test"), string::npos);
}

TEST(StackExtendedTest, TopOperations) {
    Stack s;
    s.push("bottom");
    EXPECT_EQ(s.top(), "bottom");
    
    s.push("middle");
    EXPECT_EQ(s.top(), "middle");
    
    s.push("top");
    EXPECT_EQ(s.top(), "top");
    
    EXPECT_EQ(s.top(), "top");
    EXPECT_EQ(s.top(), "top");
}

TEST(StackExtendedTest, MixedOperations) {
    Stack s;
    
    for (int i = 0; i < 15; i++) {
        s.push("item_" + to_string(i));
        if (i % 4 == 0 && s.size() > 1) {
            s.pop();
        }
    }
    
    EXPECT_GT(s.size(), 0u);
    EXPECT_FALSE(s.empty());
    
    string lastTop = s.top();
    s.pop();
    if (!s.empty()) {
        EXPECT_NE(s.top(), lastTop);
    }
}

TEST(StackExtendedTest, SerializationSpecialChars) {
    Stack original;
    original.push("normal");
    original.push("multi\nline");
    original.push("quotes\"text");
    original.push("back\\slash");
    original.push("");
    
    stringstream ss;
    original.serializeText(ss);
    
    Stack loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.pop(), "");
    EXPECT_EQ(loaded.pop(), "back\\slash");
    EXPECT_EQ(loaded.pop(), "quotes\"text");
    EXPECT_EQ(loaded.pop(), "multi\nline");
    EXPECT_EQ(loaded.pop(), "normal");
    EXPECT_TRUE(loaded.empty());
}

TEST(StackExtendedTest, PrintOperations) {
    Stack s;
    
    testing::internal::CaptureStdout();
    s.print();
    string emptyOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(emptyOutput.empty());
    
    s.push("test_value");
    testing::internal::CaptureStdout();
    s.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("test_value"), string::npos);
}

TEST(StackExtendedTest, ClearOperations) {
    Stack s;
    
    s.clear();
    EXPECT_TRUE(s.empty());
    
    for (int i = 0; i < 5; i++) {
        s.push("item_" + to_string(i));
    }
    EXPECT_FALSE(s.empty());
    s.clear();
    EXPECT_TRUE(s.empty());
}

TEST(TreeExtendedTest, EdgeCaseOperations) {
    CompleteBinaryTree tree;
    
    tree.insert("single");
    EXPECT_EQ(tree.size(), 1u);
    EXPECT_EQ(tree.getRoot(), "single");
    EXPECT_EQ(tree.height(), 1u);
    
    tree.remove();
    EXPECT_TRUE(tree.empty());
}

TEST(TreeExtendedTest, HeapPropertyMaintenance) {
    CompleteBinaryTree tree;
    
    tree.insert("z");
    tree.insert("y");
    tree.insert("x");
    tree.insert("w");
    tree.insert("v");
    
    EXPECT_EQ(tree.getRoot(), "v");
    
    tree.remove();
    EXPECT_EQ(tree.getRoot(), "w");
    
    tree.remove();
    EXPECT_EQ(tree.getRoot(), "x");
}

TEST(TreeExtendedTest, LevelOperationsEdgeCases) {
    CompleteBinaryTree tree;
    
    auto emptyLevel = tree.getLevel(0);
    EXPECT_TRUE(emptyLevel.empty());
    
    emptyLevel = tree.getLevel(1);
    EXPECT_TRUE(emptyLevel.empty());
    
    tree.insert("root");
    auto level0 = tree.getLevel(0);
    EXPECT_EQ(level0.size(), 1u);
    EXPECT_EQ(level0[0], "root");
    
    auto level1 = tree.getLevel(1);
    EXPECT_TRUE(level1.empty());
}

TEST(TreeExtendedTest, TraversalEdgeCases) {
    CompleteBinaryTree tree;
    
    auto emptyLevel = tree.levelOrder();
    auto emptyInOrder = tree.inOrder();
    auto emptyPreOrder = tree.preOrder();
    auto emptyPostOrder = tree.postOrder();
    
    EXPECT_TRUE(emptyLevel.empty());
    EXPECT_TRUE(emptyInOrder.empty());
    EXPECT_TRUE(emptyPreOrder.empty());
    EXPECT_TRUE(emptyPostOrder.empty());
    
    tree.insert("only");
    
    auto level = tree.levelOrder();
    auto inOrder = tree.inOrder();
    auto preOrder = tree.preOrder();
    auto postOrder = tree.postOrder();
    
    EXPECT_EQ(level.size(), 1u);
    EXPECT_EQ(inOrder.size(), 1u);
    EXPECT_EQ(preOrder.size(), 1u);
    EXPECT_EQ(postOrder.size(), 1u);
    EXPECT_EQ(level[0], "only");
    EXPECT_EQ(inOrder[0], "only");
    EXPECT_EQ(preOrder[0], "only");
    EXPECT_EQ(postOrder[0], "only");
}

TEST(TreeExtendedTest, ComplexHeapOperations) {
    CompleteBinaryTree tree;
    
    vector<string> values = {"m", "a", "z", "b", "y", "c", "x"};
    for (const auto& val : values) {
        tree.insert(val);
    }
    
    string root = tree.getRoot();
    for (const auto& val : values) {
        EXPECT_LE(root, val);
    }
    
    while (!tree.empty()) {
        string currentRoot = tree.getRoot();
        tree.remove();
        if (!tree.empty()) {
            string newRoot = tree.getRoot();
            EXPECT_LE(currentRoot, newRoot);
        }
    }
}

TEST(TreeExtendedTest, HeightCalculationAccuracy) {
    CompleteBinaryTree tree;
    
    EXPECT_EQ(tree.height(), 0u);
    
    tree.insert("1");
    EXPECT_EQ(tree.height(), 1u);
    
    tree.insert("2");
    EXPECT_EQ(tree.height(), 2u);
    
    tree.insert("3");
    EXPECT_EQ(tree.height(), 2u);
    
    tree.insert("4");
    EXPECT_EQ(tree.height(), 3u);
    
    tree.insert("5");
    EXPECT_EQ(tree.height(), 3u);
    
    tree.insert("6");
    EXPECT_EQ(tree.height(), 3u);
    
    tree.insert("7");
    EXPECT_EQ(tree.height(), 3u);
    
    tree.insert("8");
    EXPECT_EQ(tree.height(), 4u);
}

TEST(TreeExtendedTest, SerializationEdgeCases) {
    CompleteBinaryTree empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    CompleteBinaryTree emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    
    CompleteBinaryTree single;
    single.insert("lonely");
    stringstream ss2;
    single.serialize(ss2);
    
    CompleteBinaryTree singleLoaded;
    singleLoaded.deserialize(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.getRoot(), "lonely");
}

TEST(TreeExtendedTest, TextSerializationSpecialChars) {
    CompleteBinaryTree tree;
    
    // Вставляем элементы в определенном порядке для предсказуемости
    // В min-heap наименьший элемент всегда будет корнем
    tree.insert("");  // Пустая строка - минимальная
    tree.insert("back\\slash");
    tree.insert("line1\nline2"); 
    tree.insert("normal");
    tree.insert("text with \"quotes\"");
    
    stringstream ss;
    tree.serializeText(ss);
    
    CompleteBinaryTree loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), 5u);
    
    // В min-heap корень должен быть пустой строкой (наименьшей)
    EXPECT_EQ(loaded.getRoot(), "");
    
    // Проверяем, что дерево сохранило свойство полноты
    EXPECT_TRUE(loaded.isComplete());
    
    // Проверяем, что все элементы присутствуют
    auto values = loaded.levelOrder();
    bool has_empty = false, has_normal = false, has_newline = false, 
         has_quotes = false, has_backslash = false;
         
    for (const auto& val : values) {
        if (val == "") has_empty = true;
        else if (val == "normal") has_normal = true;
        else if (val == "line1\nline2") has_newline = true;
        else if (val == "text with \"quotes\"") has_quotes = true;
        else if (val == "back\\slash") has_backslash = true;
    }
    
    EXPECT_TRUE(has_empty);
    EXPECT_TRUE(has_normal);
    EXPECT_TRUE(has_newline);
    EXPECT_TRUE(has_quotes);
    EXPECT_TRUE(has_backslash);
}

TEST(TreeExtendedTest, LargeScaleOperations) {
    CompleteBinaryTree tree;
    const int COUNT = 1000;
    
    for (int i = COUNT - 1; i >= 0; --i) {
        tree.insert(to_string(i));
    }
    
    EXPECT_EQ(tree.size(), COUNT);
    EXPECT_EQ(tree.getRoot(), "0");
    
    for (int i = 0; i < COUNT / 2; ++i) {
        string root = tree.getRoot();
        tree.remove();
        if (!tree.empty()) {
            string newRoot = tree.getRoot();
            EXPECT_LE(root, newRoot);
        }
    }
    
    EXPECT_EQ(tree.size(), COUNT / 2);
}

TEST(TreeExtendedTest, DuplicateValues) {
    CompleteBinaryTree tree;
    
    tree.insert("same");
    tree.insert("same");
    tree.insert("same");
    tree.insert("same");
    
    EXPECT_EQ(tree.size(), 4u);
    EXPECT_TRUE(tree.isComplete());
    
    while (!tree.empty()) {
        EXPECT_EQ(tree.getRoot(), "same");
        tree.remove();
    }
}

TEST(TreeExtendedTest, MixedValueTypes) {
    CompleteBinaryTree tree;
    
    tree.insert("123");
    tree.insert("abc");
    tree.insert("!@#");
    tree.insert("");
    tree.insert("a b c");
    
    EXPECT_EQ(tree.size(), 5u);
    EXPECT_TRUE(tree.isComplete());
    
    string root = tree.getRoot();
    EXPECT_TRUE(root.empty() || root == "!@#" || root == "123");
}

TEST(TreeExtendedTest, GetLevelBoundary) {
    CompleteBinaryTree tree;
    
    auto invalidLevel = tree.getLevel(10);
    EXPECT_TRUE(invalidLevel.empty());
    
    tree.insert("root");
    auto level0 = tree.getLevel(0);
    EXPECT_EQ(level0.size(), 1u);
    
    auto level1 = tree.getLevel(1);
    EXPECT_TRUE(level1.empty());
}

TEST(TreeExtendedTest, ClearOperations) {
    CompleteBinaryTree tree;
    
    for (int i = 0; i < 5; i++) {
        tree.insert("item_" + to_string(i));
    }
    
    EXPECT_FALSE(tree.empty());
    tree.clear();
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0u);
    EXPECT_EQ(tree.height(), 0u);
    
    tree.clear();
    EXPECT_TRUE(tree.empty());
}

TEST(TreeExtendedTest, PrintOperations) {
    CompleteBinaryTree tree;
    
    testing::internal::CaptureStdout();
    tree.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    
    CompleteBinaryTree empty;
    testing::internal::CaptureStdout();
    empty.print();
    string emptyOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(emptyOutput.empty());
    
    tree.insert("test");
    tree.insert("values");
    testing::internal::CaptureStdout();
    tree.print();
    string nonEmptyOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(nonEmptyOutput.empty());
    EXPECT_NE(nonEmptyOutput.find("test"), string::npos);
}

// ==================== COMPREHENSIVE INTEGRATION TESTS ====================
TEST(ComprehensiveTest, QueueStackIntegration) {
    Queue q;
    Stack s;
    
    for (int i = 0; i < 10; i++) {
        string value = "item_" + to_string(i);
        q.enqueue(value);
        s.push(value);
    }
    
    EXPECT_EQ(q.size(), 10u);
    EXPECT_EQ(s.size(), 10u);
    
    EXPECT_EQ(q.dequeue(), "item_0");
    EXPECT_EQ(s.pop(), "item_9");
    
    q.clear();
    s.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_TRUE(s.empty());
}

TEST(ComprehensiveTest, TreeSerializationIntegration) {
    CompleteBinaryTree original;
    
    vector<string> values = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    for (const auto& val : values) {
        original.insert(val);
    }
    
    stringstream ss1;
    original.serialize(ss1);
    CompleteBinaryTree fromBinary;
    fromBinary.deserialize(ss1);
    EXPECT_EQ(fromBinary.size(), original.size());
    
    stringstream ss2;
    original.serializeText(ss2);
    CompleteBinaryTree fromText;
    fromText.deserializeText(ss2);
    EXPECT_EQ(fromText.size(), original.size());
    
    EXPECT_EQ(fromBinary.getRoot(), original.getRoot());
    EXPECT_EQ(fromText.getRoot(), original.getRoot());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}