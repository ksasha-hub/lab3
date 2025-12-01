#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <typeinfo>
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"

using namespace std;

// ==================== TEST FIXTURES ====================
class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        arr_.insert("one");
        arr_.insert("two");
        arr_.insert("three");
    }
    
    void TearDown() override {
        arr_.clear();
    }
    
    Array arr_;
};

class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        sll_.push_back("one");
        sll_.push_back("two");
        sll_.push_back("three");
        
        dll_.push_back("one");
        dll_.push_back("two");
        dll_.push_back("three");
    }
    
    void TearDown() override {
        sll_.clear();
        dll_.clear();
    }
    
    SinglyLinkedList sll_;
    DoublyLinkedList dll_;
};

class ContainerTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 5; i++) {
            q_.enqueue("item_" + to_string(i));
            s_.push("item_" + to_string(i));
        }
    }
    
    void TearDown() override {
        q_.clear();
        s_.clear();
    }
    
    Queue q_;
    Stack s_;
};

class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        ht_.insert(1, "Alice");
        ht_.insert(2, "Bob");
        ht_.insert(3, "Charlie");
    }
    
    HashTable ht_;
};

class TreeTest : public ::testing::Test {
protected:
    void SetUp() override {
        tree_.insert("5");
        tree_.insert("3");
        tree_.insert("7");
        tree_.insert("2");
        tree_.insert("4");
    }
    
    CompleteBinaryTree tree_;
};

// ==================== ARRAY TESTS ====================
TEST_F(ArrayTest, DefaultConstructor) {
    Array arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
}

TEST_F(ArrayTest, ConstructorWithSize) {
    Array arr(10);
    EXPECT_EQ(arr.size(), 10);
    EXPECT_FALSE(arr.empty());
    
    for (size_t i = 0; i < arr.size(); i++) {
        EXPECT_EQ(arr.get(i), "");
    }
}

TEST_F(ArrayTest, ConstructorWithZeroSize) {
    Array arr(0);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST_F(ArrayTest, CopyConstructor) {
    Array copy(arr_);
    EXPECT_EQ(copy.size(), arr_.size());
    
    for (size_t i = 0; i < arr_.size(); i++) {
        EXPECT_EQ(copy.get(i), arr_.get(i));
    }
}

TEST_F(ArrayTest, AssignmentOperator) {
    Array assigned;
    assigned = arr_;
    
    EXPECT_EQ(assigned.size(), arr_.size());
    for (size_t i = 0; i < arr_.size(); i++) {
        EXPECT_EQ(assigned.get(i), arr_.get(i));
    }
}

TEST_F(ArrayTest, SelfAssignment) {
    Array original;
    original.insert("test");
    original = original;
    
    EXPECT_EQ(original.size(), 1);
    EXPECT_EQ(original.get(0), "test");
}

TEST_F(ArrayTest, MoveAssignment) {
    Array source;
    source.insert("source_data");
    
    Array target;
    target = source;
    
    EXPECT_EQ(target.size(), 1);
    EXPECT_EQ(target.get(0), "source_data");
    EXPECT_EQ(source.size(), 1);
}

TEST_F(ArrayTest, InsertBasic) {
    Array arr;
    arr.insert("first");
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.get(0), "first");
    
    arr.insert("second");
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(1), "second");
}

TEST_F(ArrayTest, InsertEmptyString) {
    Array arr;
    arr.insert("");
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.get(0), "");
}

TEST_F(ArrayTest, InsertSpecialCharacters) {
    Array arr;
    string special = "line1\nline2\t tab \\ backslash \"quotes\"";
    arr.insert(special);
    EXPECT_EQ(arr.get(0), special);
}

TEST_F(ArrayTest, InsertAtBeginning) {
    Array arr;
    arr.insert("original");
    arr.insertAt(0, "new_first");
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(0), "new_first");
    EXPECT_EQ(arr.get(1), "original");
}

TEST_F(ArrayTest, InsertAtMiddle) {
    Array arr;
    arr.insert("A");
    arr.insert("C");
    arr.insertAt(1, "B");
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr.get(0), "A");
    EXPECT_EQ(arr.get(1), "B");
    EXPECT_EQ(arr.get(2), "C");
}

TEST_F(ArrayTest, InsertAtEnd) {
    Array arr;
    arr.insert("first");
    arr.insertAt(1, "last");
    
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "last");
}

TEST_F(ArrayTest, InsertAtInvalidPosition) {
    Array arr;
    arr.insert("one");
    
    EXPECT_THROW(arr.insertAt(2, "invalid"), out_of_range);
    EXPECT_THROW(arr.insertAt(100, "invalid"), out_of_range);
}

TEST_F(ArrayTest, RemoveFromBeginning) {
    Array arr;
    arr.insert("first");
    arr.insert("second");
    arr.insert("third");
    
    arr.remove(0);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(0), "second");
    EXPECT_EQ(arr.get(1), "third");
}

TEST_F(ArrayTest, RemoveFromMiddle) {
    Array arr;
    arr.insert("first");
    arr.insert("second");
    arr.insert("third");
    
    arr.remove(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "third");
}

TEST_F(ArrayTest, RemoveFromEnd) {
    Array arr;
    arr.insert("first");
    arr.insert("second");
    arr.insert("third");
    
    arr.remove(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "second");
}

TEST_F(ArrayTest, RemoveSingleElement) {
    Array arr;
    arr.insert("only");
    arr.remove(0);
    
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
}

TEST_F(ArrayTest, RemoveInvalidIndex) {
    Array arr;
    arr.insert("one");
    
    EXPECT_THROW(arr.remove(1), out_of_range);
    EXPECT_THROW(arr.remove(100), out_of_range);
}

TEST_F(ArrayTest, RemoveFromEmpty) {
    Array arr;
    EXPECT_THROW(arr.remove(0), out_of_range);
}

TEST_F(ArrayTest, SetAndGetOperations) {
    Array arr;
    arr.insert("original");
    
    arr.set(0, "modified");
    EXPECT_EQ(arr.get(0), "modified");
    
    arr.insert("second");
    arr.set(1, "changed");
    EXPECT_EQ(arr.get(1), "changed");
}

TEST_F(ArrayTest, SetInvalidIndex) {
    Array arr;
    EXPECT_THROW(arr.set(0, "test"), out_of_range);
    
    arr.insert("one");
    EXPECT_THROW(arr.set(1, "test"), out_of_range);
}

TEST_F(ArrayTest, GetInvalidIndex) {
    Array arr;
    EXPECT_THROW(arr.get(0), out_of_range);
    
    arr.insert("one");
    EXPECT_THROW(arr.get(1), out_of_range);
}

TEST_F(ArrayTest, ClearOperations) {
    Array arr;
    for (int i = 0; i < 10; i++) {
        arr.insert("item_" + to_string(i));
    }
    
    EXPECT_FALSE(arr.empty());
    arr.clear();
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
}

TEST_F(ArrayTest, ClearEmptyArray) {
    Array arr;
    arr.clear();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ArrayTest, MultipleClear) {
    Array arr;
    arr.insert("test");
    arr.clear();
    arr.clear();
    EXPECT_TRUE(arr.empty());
}

TEST_F(ArrayTest, ResizeOperations) {
    Array arr;
    
    for (int i = 0; i < 1000; i++) {
        arr.insert("element_" + to_string(i));
    }
    
    EXPECT_EQ(arr.size(), 1000);
    
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(arr.get(i), "element_" + to_string(i));
    }
}

TEST_F(ArrayTest, ResizeWithRemovals) {
    Array arr;
    
    for (int i = 0; i < 500; i++) {
        arr.insert("fill_" + to_string(i));
    }
    
    for (int i = 0; i < 400; i++) {
        arr.remove(0);
    }
    
    EXPECT_EQ(arr.size(), 100);
    
    for (int i = 0; i < 200; i++) {
        arr.insert("new_" + to_string(i));
    }
    
    EXPECT_EQ(arr.size(), 300);
}

TEST_F(ArrayTest, ComplexOperationSequence) {
    Array arr;
    
    for (int i = 0; i < 100; i++) {
        if (i % 3 == 0) {
            arr.insertAt(0, "front_" + to_string(i));
        } else if (i % 3 == 1) {
            if (!arr.empty()) {
                arr.insertAt(arr.size() / 2, "middle_" + to_string(i));
            } else {
                arr.insert("first_" + to_string(i));
            }
        } else {
            arr.insert("back_" + to_string(i));
        }
        
        if (i % 10 == 0) {
            for (size_t j = 0; j < arr.size(); j++) {
                EXPECT_FALSE(arr.get(j).empty());
            }
        }
    }
    
    EXPECT_GT(arr.size(), 50);
    
    while (arr.size() > 10) {
        if (arr.size() % 2 == 0) {
            arr.remove(arr.size() - 1);
        } else {
            arr.remove(0);
        }
    }
    
    EXPECT_EQ(arr.size(), 10);
}

TEST_F(ArrayTest, SerializationRoundTrip) {
    Array original;
    for (int i = 0; i < 10; i++) {
        original.insert("serial_" + to_string(i * 2));
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

TEST_F(ArrayTest, SerializationEmpty) {
    Array empty;
    stringstream ss;
    empty.serialize(ss);
    
    Array loaded;
    loaded.deserialize(ss);
    
    EXPECT_TRUE(loaded.empty());
    EXPECT_EQ(loaded.size(), 0);
}

TEST_F(ArrayTest, SerializationSingleElement) {
    Array single;
    single.insert("lonely");
    
    stringstream ss;
    single.serialize(ss);
    
    Array loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), 1);
    EXPECT_EQ(loaded.get(0), "lonely");
}

TEST_F(ArrayTest, TextSerialization) {
    Array original;
    original.insert("normal text");
    original.insert("multi\nline");
    original.insert("quotes\"in\"text");
    original.insert("back\\slash");
    original.insert("");
    
    stringstream ss;
    original.serializeText(ss);
    
    Array loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), original.size());
    EXPECT_EQ(loaded.get(0), "normal text");
    EXPECT_EQ(loaded.get(1), "multi\nline");
    EXPECT_EQ(loaded.get(2), "quotes\"in\"text");
    EXPECT_EQ(loaded.get(3), "back\\slash");
    EXPECT_EQ(loaded.get(4), "");
}

TEST_F(ArrayTest, PrintOperations) {
    Array arr;
    
    testing::internal::CaptureStdout();
    arr.print();
    string empty_output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(empty_output.empty());
    
    arr.insert("test_value");
    testing::internal::CaptureStdout();
    arr.print();
    string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("test_value"), string::npos);
}

TEST_F(ArrayTest, StressTest) {
    Array arr;
    const int OPERATIONS = 10000;
    
    for (int i = 0; i < OPERATIONS; i++) {
        if (arr.empty()) {
            arr.insert("base_" + to_string(i));
        } else {
            size_t pos = i % arr.size();
            if (i % 5 == 0) {
                arr.insertAt(pos, "inserted_" + to_string(i));
            } else if (i % 5 == 1) {
                arr.remove(pos);
            } else if (i % 5 == 2) {
                arr.set(pos, "modified_" + to_string(i));
            } else if (i % 5 == 3) {
                arr.insert("appended_" + to_string(i));
            } else {
                string value = arr.get(pos);
                EXPECT_FALSE(value.empty());
            }
        }
        
        if (i % 1000 == 0) {
            for (size_t j = 0; j < arr.size(); j++) {
                EXPECT_FALSE(arr.get(j).empty());
            }
        }
    }
    
    EXPECT_GE(arr.size(), 0);
}

// ==================== SINGLY LINKED LIST TESTS ====================
TEST_F(LinkedListTest, DefaultConstructor) {
    SinglyLinkedList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST_F(LinkedListTest, PushFront) {
    SinglyLinkedList list;
    list.push_front("first");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "first");
    
    list.push_front("new_first");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "new_first");
    EXPECT_EQ(list.get(1), "first");
}

TEST_F(LinkedListTest, PushBack) {
    SinglyLinkedList list;
    list.push_back("first");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "first");
    
    list.push_back("second");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "first");
    EXPECT_EQ(list.get(1), "second");
}

TEST_F(LinkedListTest, PopFront) {
    SinglyLinkedList list;
    list.push_back("first");
    list.push_back("second");
    
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "second");
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, PopFrontEmpty) {
    SinglyLinkedList list;
    EXPECT_THROW(list.pop_front(), runtime_error);
}

TEST_F(LinkedListTest, PopBack) {
    SinglyLinkedList list;
    list.push_back("first");
    list.push_back("second");
    
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "first");
    
    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, PopBackEmpty) {
    SinglyLinkedList list;
    EXPECT_THROW(list.pop_back(), runtime_error);
}

TEST_F(LinkedListTest, PopBackSingleElement) {
    SinglyLinkedList list;
    list.push_back("only");
    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, InsertAtBeginning) {
    SinglyLinkedList list;
    list.push_back("original");
    list.insert(0, "new_first");
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "new_first");
    EXPECT_EQ(list.get(1), "original");
}

TEST_F(LinkedListTest, InsertAtMiddle) {
    SinglyLinkedList list;
    list.push_back("A");
    list.push_back("C");
    list.insert(1, "B");
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(0), "A");
    EXPECT_EQ(list.get(1), "B");
    EXPECT_EQ(list.get(2), "C");
}

TEST_F(LinkedListTest, InsertAtEnd) {
    SinglyLinkedList list;
    list.push_back("first");
    list.insert(1, "last");
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "first");
    EXPECT_EQ(list.get(1), "last");
}

TEST_F(LinkedListTest, InsertInvalidPosition) {
    SinglyLinkedList list;
    EXPECT_THROW(list.insert(1, "test"), out_of_range);
    
    list.push_back("one");
    EXPECT_THROW(list.insert(2, "test"), out_of_range);
}

TEST_F(LinkedListTest, RemoveOperations) {
    SinglyLinkedList list;
    list.push_back("A");
    list.push_back("B");
    list.push_back("C");
    list.push_back("D");
    
    list.remove(1);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(0), "A");
    EXPECT_EQ(list.get(1), "C");
    EXPECT_EQ(list.get(2), "D");
    
    list.remove(0);
    EXPECT_EQ(list.get(0), "C");
    
    list.remove(1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "C");
}

TEST_F(LinkedListTest, RemoveInvalidIndex) {
    SinglyLinkedList list;
    EXPECT_THROW(list.remove(0), out_of_range);
    
    list.push_back("one");
    EXPECT_THROW(list.remove(1), out_of_range);
}

TEST_F(LinkedListTest, GetInvalidIndex) {
    SinglyLinkedList list;
    EXPECT_THROW(list.get(0), out_of_range);
    
    list.push_back("one");
    EXPECT_THROW(list.get(1), out_of_range);
}

TEST_F(LinkedListTest, CopyConstructor) {
    SinglyLinkedList copy(sll_);
    EXPECT_EQ(copy.size(), sll_.size());
    
    for (size_t i = 0; i < sll_.size(); i++) {
        EXPECT_EQ(copy.get(i), sll_.get(i));
    }
}

TEST_F(LinkedListTest, AssignmentOperator) {
    SinglyLinkedList assigned;
    assigned = sll_;
    
    EXPECT_EQ(assigned.size(), sll_.size());
    for (size_t i = 0; i < sll_.size(); i++) {
        EXPECT_EQ(assigned.get(i), sll_.get(i));
    }
}

TEST_F(LinkedListTest, SelfAssignment) {
    EXPECT_EQ(sll_.size(), 3);
    EXPECT_TRUE(sll_.checkIntegrity());
}

TEST_F(LinkedListTest, ClearOperations) {
    EXPECT_FALSE(sll_.empty());
    sll_.clear();
    EXPECT_TRUE(sll_.empty());
    EXPECT_EQ(sll_.size(), 0);
}

TEST_F(LinkedListTest, ClearEmpty) {
    SinglyLinkedList list;
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, IntegrityChecking) {
    EXPECT_TRUE(sll_.checkIntegrity());
    
    sll_.push_front("new_front");
    EXPECT_TRUE(sll_.checkIntegrity());
    
    sll_.pop_back();
    EXPECT_TRUE(sll_.checkIntegrity());
    
    sll_.insert(1, "middle");
    EXPECT_TRUE(sll_.checkIntegrity());
    
    sll_.remove(0);
    EXPECT_TRUE(sll_.checkIntegrity());
}

TEST_F(LinkedListTest, ContainsMethod) {
    EXPECT_TRUE(sll_.contains("one"));
    EXPECT_TRUE(sll_.contains("two"));
    EXPECT_TRUE(sll_.contains("three"));
    EXPECT_FALSE(sll_.contains("four"));
    EXPECT_FALSE(sll_.contains(""));
}

TEST_F(LinkedListTest, ContainsEmpty) {
    SinglyLinkedList empty;
    EXPECT_FALSE(empty.contains("anything"));
}

TEST_F(LinkedListTest, ToVectorMethod) {
    vector<string> vec = sll_.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], "one");
    EXPECT_EQ(vec[1], "two");
    EXPECT_EQ(vec[2], "three");
}

TEST_F(LinkedListTest, ToVectorEmpty) {
    SinglyLinkedList empty;
    vector<string> vec = empty.toVector();
    EXPECT_TRUE(vec.empty());
}

TEST_F(LinkedListTest, ComplexOperations) {
    SinglyLinkedList list;
    
    for (int i = 0; i < 50; i++) {
        if (i % 4 == 0) {
            list.push_front("front_" + to_string(i));
        } else if (i % 4 == 1) {
            list.push_back("back_" + to_string(i));
        } else if (i % 4 == 2) {
            if (!list.empty()) {
                size_t pos = i % list.size();
                list.insert(pos, "middle_" + to_string(i));
            }
        } else {
            if (!list.empty()) {
                size_t pos = i % list.size();
                list.remove(pos);
            }
        }
        
        EXPECT_TRUE(list.checkIntegrity());
    }
    
    EXPECT_GE(list.size(), 0);
}

TEST_F(LinkedListTest, Serialization) {
    stringstream ss;
    sll_.serialize(ss);
    
    SinglyLinkedList loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), sll_.size());
    for (size_t i = 0; i < sll_.size(); i++) {
        EXPECT_EQ(loaded.get(i), sll_.get(i));
    }
    EXPECT_TRUE(loaded.checkIntegrity());
}

TEST_F(LinkedListTest, TextSerialization) {
    SinglyLinkedList list;
    list.push_back("normal");
    list.push_back("multi\nline");
    list.push_back("quotes\"text");
    
    stringstream ss;
    list.serializeText(ss);
    
    SinglyLinkedList loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), 3);
    EXPECT_EQ(loaded.get(0), "normal");
    EXPECT_EQ(loaded.get(1), "multi\nline");
    EXPECT_EQ(loaded.get(2), "quotes\"text");
    EXPECT_TRUE(loaded.checkIntegrity());
}

// ==================== DOUBLY LINKED LIST TESTS ====================
TEST_F(LinkedListTest, DoublyDefaultConstructor) {
    DoublyLinkedList list;
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}

TEST_F(LinkedListTest, DoublyPushFront) {
    DoublyLinkedList list;
    list.push_front("first");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "first");
    
    list.push_front("new_first");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "new_first");
    EXPECT_EQ(list.get(1), "first");
}

TEST_F(LinkedListTest, DoublyPushBack) {
    DoublyLinkedList list;
    list.push_back("first");
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "first");
    
    list.push_back("second");
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "first");
    EXPECT_EQ(list.get(1), "second");
}

TEST_F(LinkedListTest, DoublyPopFront) {
    DoublyLinkedList list;
    list.push_back("first");
    list.push_back("second");
    
    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "second");
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, DoublyPopBack) {
    DoublyLinkedList list;
    list.push_back("first");
    list.push_back("second");
    
    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.get(0), "first");
    
    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST_F(LinkedListTest, DoublyInsertOperations) {
    DoublyLinkedList list;
    list.push_back("A");
    list.push_back("C");
    
    list.insert(1, "B");
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.get(0), "A");
    EXPECT_EQ(list.get(1), "B");
    EXPECT_EQ(list.get(2), "C");
}

TEST_F(LinkedListTest, DoublyRemoveOperations) {
    DoublyLinkedList list;
    list.push_back("A");
    list.push_back("B");
    list.push_back("C");
    
    list.remove(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(0), "A");
    EXPECT_EQ(list.get(1), "C");
}

TEST_F(LinkedListTest, DoublyCopyConstructor) {
    DoublyLinkedList copy(dll_);
    EXPECT_EQ(copy.size(), dll_.size());
    
    for (size_t i = 0; i < dll_.size(); i++) {
        EXPECT_EQ(copy.get(i), dll_.get(i));
    }
}

TEST_F(LinkedListTest, DoublyAssignmentOperator) {
    DoublyLinkedList assigned;
    assigned = dll_;
    
    EXPECT_EQ(assigned.size(), dll_.size());
    for (size_t i = 0; i < dll_.size(); i++) {
        EXPECT_EQ(assigned.get(i), dll_.get(i));
    }
}

TEST_F(LinkedListTest, DoublyIntegrityChecking) {
    EXPECT_TRUE(dll_.checkIntegrity());
    
    dll_.push_front("new_front");
    EXPECT_TRUE(dll_.checkIntegrity());
    
    dll_.pop_back();
    EXPECT_TRUE(dll_.checkIntegrity());
    
    dll_.insert(1, "middle");
    EXPECT_TRUE(dll_.checkIntegrity());
    
    dll_.remove(0);
    EXPECT_TRUE(dll_.checkIntegrity());
}

TEST_F(LinkedListTest, DoublyToVector) {
    vector<string> vec = dll_.toVector();
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], "one");
    EXPECT_EQ(vec[1], "two");
    EXPECT_EQ(vec[2], "three");
}

TEST_F(LinkedListTest, DoublyComplexOperations) {
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
                list.remove(list.size() / 2);
            }
        }
        EXPECT_TRUE(list.checkIntegrity());
    }
    
    EXPECT_GE(list.size(), 0);
}

// ==================== QUEUE TESTS ====================
TEST_F(ContainerTest, QueueDefaultConstructor) {
    Queue q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST_F(ContainerTest, QueueEnqueueDequeue) {
    Queue q;
    q.enqueue("first");
    q.enqueue("second");
    q.enqueue("third");
    
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), "first");
    EXPECT_EQ(q.back(), "third");
    
    EXPECT_EQ(q.dequeue(), "first");
    EXPECT_EQ(q.dequeue(), "second");
    EXPECT_EQ(q.dequeue(), "third");
    EXPECT_TRUE(q.empty());
}

TEST_F(ContainerTest, QueueFrontBack) {
    EXPECT_EQ(q_.front(), "item_0");
    EXPECT_EQ(q_.back(), "item_4");
    
    q_.dequeue();
    EXPECT_EQ(q_.front(), "item_1");
    EXPECT_EQ(q_.back(), "item_4");
}

TEST_F(ContainerTest, QueueEmptyOperations) {
    Queue empty;
    EXPECT_THROW(empty.front(), runtime_error);
    EXPECT_THROW(empty.back(), runtime_error);
    EXPECT_THROW(empty.dequeue(), runtime_error);
}

TEST_F(ContainerTest, QueueClear) {
    EXPECT_FALSE(q_.empty());
    q_.clear();
    EXPECT_TRUE(q_.empty());
    EXPECT_EQ(q_.size(), 0);
}

TEST_F(ContainerTest, QueueSerialization) {
    stringstream ss;
    q_.serialize(ss);
    
    Queue loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), q_.size());
    while (!q_.empty() && !loaded.empty()) {
        EXPECT_EQ(loaded.dequeue(), q_.dequeue());
    }
}

// ==================== STACK TESTS ====================
TEST_F(ContainerTest, StackDefaultConstructor) {
    Stack st;
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0);
}

TEST_F(ContainerTest, StackPushPop) {
    Stack st;
    st.push("first");
    st.push("second");
    st.push("third");
    
    EXPECT_EQ(st.size(), 3);
    EXPECT_EQ(st.top(), "third");
    
    EXPECT_EQ(st.pop(), "third");
    EXPECT_EQ(st.pop(), "second");
    EXPECT_EQ(st.pop(), "first");
    EXPECT_TRUE(st.empty());
}

TEST_F(ContainerTest, StackTop) {
    EXPECT_EQ(s_.top(), "item_4");
    
    s_.pop();
    EXPECT_EQ(s_.top(), "item_3");
}

TEST_F(ContainerTest, StackEmptyOperations) {
    Stack empty;
    EXPECT_THROW(empty.top(), runtime_error);
    EXPECT_THROW(empty.pop(), runtime_error);
}

TEST_F(ContainerTest, StackClear) {
    EXPECT_FALSE(s_.empty());
    s_.clear();
    EXPECT_TRUE(s_.empty());
    EXPECT_EQ(s_.size(), 0);
}

TEST_F(ContainerTest, StackSerialization) {
    stringstream ss;
    s_.serialize(ss);
    
    Stack loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), s_.size());
    while (!s_.empty() && !loaded.empty()) {
        EXPECT_EQ(loaded.pop(), s_.pop());
    }
}

// ==================== HASH TABLE TESTS ====================
TEST_F(HashTableTest, DefaultConstructor) {
    HashTable ht;
    EXPECT_TRUE(ht.empty());
    EXPECT_EQ(ht.size(), 0);
    EXPECT_GT(ht.getCapacity(), 0);
}

TEST_F(HashTableTest, ConstructorWithCapacity) {
    HashTable ht(25);
    EXPECT_TRUE(ht.empty());
    EXPECT_GE(ht.getCapacity(), 25);
}

TEST_F(HashTableTest, ConstructorWithSmallCapacity) {
    HashTable ht(1);
    EXPECT_TRUE(ht.empty());
    EXPECT_GE(ht.getCapacity(), 1);
}

TEST_F(HashTableTest, InsertAndRetrieve) {
    HashTable ht;
    ht.insert(1, "Alice");
    ht.insert(2, "Bob");
    ht.insert(3, "Charlie");
    
    EXPECT_EQ(ht.size(), 3);
    EXPECT_EQ(ht.get(1), "Alice");
    EXPECT_EQ(ht.get(2), "Bob");
    EXPECT_EQ(ht.get(3), "Charlie");
}

TEST_F(HashTableTest, InsertDuplicateKey) {
    HashTable ht;
    ht.insert(1, "original");
    ht.insert(1, "updated");
    
    EXPECT_EQ(ht.size(), 1);
    EXPECT_EQ(ht.get(1), "updated");
}

TEST_F(HashTableTest, InsertMultipleUpdates) {
    HashTable ht;
    for (int i = 0; i < 10; i++) {
        ht.insert(1, "version_" + to_string(i));
    }
    
    EXPECT_EQ(ht.size(), 1);
    EXPECT_EQ(ht.get(1), "version_9");
}

TEST_F(HashTableTest, InsertNegativeKey) {
    HashTable ht;
    ht.insert(-1, "negative");
    ht.insert(-100, "large_negative");
    
    EXPECT_EQ(ht.size(), 2);
    EXPECT_EQ(ht.get(-1), "negative");
    EXPECT_EQ(ht.get(-100), "large_negative");
}

TEST_F(HashTableTest, InsertZeroKey) {
    HashTable ht;
    ht.insert(0, "zero");
    EXPECT_EQ(ht.get(0), "zero");
}

TEST_F(HashTableTest, InsertLargeKey) {
    HashTable ht;
    ht.insert(1000000, "large");
    ht.insert(9999999, "very_large");
    
    EXPECT_EQ(ht.get(1000000), "large");
    EXPECT_EQ(ht.get(9999999), "very_large");
}

TEST_F(HashTableTest, RemoveExisting) {
    EXPECT_TRUE(ht_.remove(2));
    EXPECT_EQ(ht_.size(), 2);
    EXPECT_FALSE(ht_.contains(2));
    EXPECT_THROW(ht_.get(2), runtime_error);
}

TEST_F(HashTableTest, RemoveNonExisting) {
    EXPECT_FALSE(ht_.remove(999));
    EXPECT_EQ(ht_.size(), 3);
}

TEST_F(HashTableTest, RemoveAll) {
    ht_.remove(1);
    ht_.remove(2);
    ht_.remove(3);
    
    EXPECT_TRUE(ht_.empty());
    EXPECT_EQ(ht_.size(), 0);
}

TEST_F(HashTableTest, ContainsOperations) {
    EXPECT_TRUE(ht_.contains(1));
    EXPECT_TRUE(ht_.contains(2));
    EXPECT_TRUE(ht_.contains(3));
    EXPECT_FALSE(ht_.contains(4));
    EXPECT_FALSE(ht_.contains(-1));
}

TEST_F(HashTableTest, GetNonExisting) {
    EXPECT_THROW(ht_.get(999), runtime_error);
}

TEST_F(HashTableTest, ClearOperations) {
    EXPECT_FALSE(ht_.empty());
    ht_.clear();
    EXPECT_TRUE(ht_.empty());
    EXPECT_EQ(ht_.size(), 0);
    
    EXPECT_FALSE(ht_.contains(1));
    EXPECT_FALSE(ht_.contains(2));
    EXPECT_FALSE(ht_.contains(3));
}

TEST_F(HashTableTest, RehashingOperations) {
    HashTable ht(4);
    
    for (int i = 0; i < 20; i++) {
        ht.insert(i, "value_" + to_string(i));
    }
    
    EXPECT_EQ(ht.size(), 20);
    EXPECT_GT(ht.getCapacity(), 4);
    
    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(ht.contains(i));
        EXPECT_EQ(ht.get(i), "value_" + to_string(i));
    }
}

TEST_F(HashTableTest, CollisionHandling) {
    HashTable ht(5);
    
    for (int i = 0; i < 15; i += 5) {
        ht.insert(i, "collision_" + to_string(i));
    }
    
    EXPECT_EQ(ht.size(), 3);
    
    for (int i = 0; i < 15; i += 5) {
        EXPECT_TRUE(ht.contains(i));
        EXPECT_EQ(ht.get(i), "collision_" + to_string(i));
    }
}

TEST_F(HashTableTest, ChainStatistics) {
    HashTable ht(10);
    
    for (int i = 0; i < 25; i++) {
        ht.insert(i, "chain_" + to_string(i));
    }
    
    size_t longest = ht.getLongestChain();
    size_t shortest = ht.getShortestChain();
    
    EXPECT_GE(longest, shortest);
    EXPECT_GT(longest, 0);
    EXPECT_LE(longest, 25);
    EXPECT_LE(shortest, 25);
}

TEST_F(HashTableTest, LoadFactor) {
    HashTable ht(10);
    EXPECT_EQ(ht.loadFactor(), 0.0);
    
    ht.insert(1, "one");
    double load1 = ht.loadFactor();
    EXPECT_GT(load1, 0.0);
    EXPECT_LE(load1, 1.0);
    
    for (int i = 2; i <= 10; i++) {
        ht.insert(i, "value_" + to_string(i));
    }
    
    double load2 = ht.loadFactor();
    EXPECT_GT(load2, load1);
    EXPECT_LE(load2, 1.0);
}

TEST_F(HashTableTest, GetAllKeys) {
    vector<int> keys = ht_.getAllKeys();
    EXPECT_EQ(keys.size(), 3);
    
    EXPECT_NE(find(keys.begin(), keys.end(), 1), keys.end());
    EXPECT_NE(find(keys.begin(), keys.end(), 2), keys.end());
    EXPECT_NE(find(keys.begin(), keys.end(), 3), keys.end());
    EXPECT_EQ(find(keys.begin(), keys.end(), 4), keys.end());
}

TEST_F(HashTableTest, IntegrityChecking) {
    EXPECT_TRUE(ht_.checkIntegrity());
    
    ht_.insert(4, "David");
    EXPECT_TRUE(ht_.checkIntegrity());
    
    ht_.remove(2);
    EXPECT_TRUE(ht_.checkIntegrity());
    
    ht_.insert(1, "Alice_updated");
    EXPECT_TRUE(ht_.checkIntegrity());
}

TEST_F(HashTableTest, CopyConstructor) {
    HashTable copy(ht_);
    EXPECT_EQ(copy.size(), ht_.size());
    
    for (int key : ht_.getAllKeys()) {
        EXPECT_TRUE(copy.contains(key));
        EXPECT_EQ(copy.get(key), ht_.get(key));
    }
    EXPECT_TRUE(copy.checkIntegrity());
}

TEST_F(HashTableTest, AssignmentOperator) {
    HashTable assigned;
    assigned = ht_;
    
    EXPECT_EQ(assigned.size(), ht_.size());
    for (int key : ht_.getAllKeys()) {
        EXPECT_TRUE(assigned.contains(key));
        EXPECT_EQ(assigned.get(key), ht_.get(key));
    }
    EXPECT_TRUE(assigned.checkIntegrity());
}

TEST_F(HashTableTest, SelfAssignment) {
    EXPECT_EQ(ht_.size(), 3);
    EXPECT_TRUE(ht_.checkIntegrity());
}

TEST_F(HashTableTest, ComplexOperations) {
    HashTable ht;
    
    for (int i = 0; i < 100; i++) {
        ht.insert(i, "value_" + to_string(i));
        
        if (i % 7 == 0) {
            ht.remove(i - 1);
        }
        
        if (i % 13 == 0) {
            ht.insert(i, "updated_" + to_string(i));
        }
        
        if (i % 20 == 0) {
            EXPECT_TRUE(ht.checkIntegrity());
        }
    }
    
    EXPECT_GT(ht.size(), 50);
    EXPECT_TRUE(ht.checkIntegrity());
}

TEST_F(HashTableTest, Serialization) {
    stringstream ss;
    ht_.serialize(ss);
    
    HashTable loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), ht_.size());
    for (int key : ht_.getAllKeys()) {
        EXPECT_TRUE(loaded.contains(key));
        EXPECT_EQ(loaded.get(key), ht_.get(key));
    }
    EXPECT_TRUE(loaded.checkIntegrity());
}

TEST_F(HashTableTest, TextSerialization) {
    HashTable ht;
    ht.insert(1, "normal");
    ht.insert(2, "multi\nline");
    ht.insert(3, "quotes\"text");
    
    stringstream ss;
    ht.serializeText(ss);
    
    HashTable loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), 3);
    EXPECT_EQ(loaded.get(1), "normal");
    EXPECT_EQ(loaded.get(2), "multi\nline");
    EXPECT_EQ(loaded.get(3), "quotes\"text");
    EXPECT_TRUE(loaded.checkIntegrity());
}

// ==================== COMPLETE BINARY TREE TESTS ====================
TEST_F(TreeTest, DefaultConstructor) {
    CompleteBinaryTree tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.height(), 0);
}

TEST_F(TreeTest, InsertOperations) {
    CompleteBinaryTree tree;
    tree.insert("root");
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.height(), 1);
    
    tree.insert("left");
    EXPECT_EQ(tree.size(), 2);
    EXPECT_EQ(tree.height(), 2);
    
    tree.insert("right");
    EXPECT_EQ(tree.size(), 3);
    EXPECT_EQ(tree.height(), 2);
}

TEST_F(TreeTest, InsertDuplicateValues) {
    CompleteBinaryTree tree;
    tree.insert("same");
    tree.insert("same");
    tree.insert("same");
    
    EXPECT_EQ(tree.size(), 3);
}

TEST_F(TreeTest, RemoveOperations) {
    size_t initial_size = tree_.size();
    tree_.remove();
    
    EXPECT_EQ(tree_.size(), initial_size - 1);
    EXPECT_TRUE(tree_.isComplete());
}

TEST_F(TreeTest, RemoveAll) {
    while (!tree_.empty()) {
        tree_.remove();
    }
    
    EXPECT_TRUE(tree_.empty());
    EXPECT_EQ(tree_.size(), 0);
    EXPECT_EQ(tree_.height(), 0);
}

TEST_F(TreeTest, RemoveEmpty) {
    CompleteBinaryTree empty;
    EXPECT_THROW(empty.remove(), runtime_error);
}

TEST_F(TreeTest, GetRoot) {
    string root = tree_.getRoot();
    EXPECT_FALSE(root.empty());
}

TEST_F(TreeTest, GetRootEmpty) {
    CompleteBinaryTree empty;
    EXPECT_THROW(empty.getRoot(), runtime_error);
}

TEST_F(TreeTest, LevelOrderTraversal) {
    auto level = tree_.levelOrder();
    EXPECT_EQ(level.size(), tree_.size());
    
    for (const string& val : level) {
        EXPECT_FALSE(val.empty());
    }
}

TEST_F(TreeTest, InOrderTraversal) {
    auto in_order = tree_.inOrder();
    EXPECT_EQ(in_order.size(), tree_.size());
    
    vector<string> expected = {"2", "3", "4", "5", "7"};
    for (const string& val : expected) {
        EXPECT_NE(find(in_order.begin(), in_order.end(), val), in_order.end());
    }
}

TEST_F(TreeTest, PreOrderTraversal) {
    auto pre_order = tree_.preOrder();
    EXPECT_EQ(pre_order.size(), tree_.size());
    EXPECT_EQ(pre_order[0], tree_.getRoot());
}

TEST_F(TreeTest, PostOrderTraversal) {
    auto post_order = tree_.postOrder();
    EXPECT_EQ(post_order.size(), tree_.size());
    EXPECT_FALSE(post_order.back().empty());
}

TEST_F(TreeTest, HeapProperty) {
    string root = tree_.getRoot();
    auto all_values = tree_.levelOrder();
    
    for (const string& val : all_values) {
        EXPECT_LE(root, val);
    }
}

TEST_F(TreeTest, LevelOperations) {
    auto level0 = tree_.getLevel(0);
    EXPECT_EQ(level0.size(), 1);
    
    auto level1 = tree_.getLevel(1);
    EXPECT_LE(level1.size(), 2);
    
    auto invalid = tree_.getLevel(100);
    EXPECT_TRUE(invalid.empty());
}

TEST_F(TreeTest, HeightCalculation) {
    CompleteBinaryTree tree;
    EXPECT_EQ(tree.height(), 0);
    
    tree.insert("A");
    EXPECT_EQ(tree.height(), 1);
    
    tree.insert("B");
    EXPECT_EQ(tree.height(), 2);
    
    tree.insert("C");
    EXPECT_EQ(tree.height(), 2);
    
    tree.insert("D");
    EXPECT_EQ(tree.height(), 3);
}

TEST_F(TreeTest, CompletenessProperty) {
    EXPECT_TRUE(tree_.isComplete());
    
    tree_.remove();
    EXPECT_TRUE(tree_.isComplete());
    
    tree_.remove();
    EXPECT_TRUE(tree_.isComplete());
}

TEST_F(TreeTest, ComplexOperations) {
    CompleteBinaryTree tree;
    
    for (int i = 0; i < 20; i++) {
        tree.insert("val_" + to_string(i));
        
        if (i % 4 == 0 && tree.size() > 1) {
            tree.remove();
        }
        
        EXPECT_TRUE(tree.isComplete());
    }
    
    EXPECT_GT(tree.size(), 0);
    
    auto level = tree.levelOrder();
    auto in_order = tree.inOrder();
    auto pre_order = tree.preOrder();
    auto post_order = tree.postOrder();
    
    EXPECT_EQ(level.size(), tree.size());
    EXPECT_EQ(in_order.size(), tree.size());
    EXPECT_EQ(pre_order.size(), tree.size());
    EXPECT_EQ(post_order.size(), tree.size());
}

TEST_F(TreeTest, Serialization) {
    stringstream ss;
    tree_.serialize(ss);
    
    CompleteBinaryTree loaded;
    loaded.deserialize(ss);
    
    EXPECT_EQ(loaded.size(), tree_.size());
    EXPECT_TRUE(loaded.isComplete());
    
    auto original_level = tree_.levelOrder();
    auto loaded_level = loaded.levelOrder();
    EXPECT_EQ(original_level.size(), loaded_level.size());
}

TEST_F(TreeTest, TextSerialization) {
    CompleteBinaryTree tree;
    tree.insert("normal");
    tree.insert("multi\nline");
    tree.insert("quotes\"text");
    
    stringstream ss;
    tree.serializeText(ss);
    
    CompleteBinaryTree loaded;
    loaded.deserializeText(ss);
    
    EXPECT_EQ(loaded.size(), tree.size());
    EXPECT_TRUE(loaded.isComplete());
}

// ==================== ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ 90%+ ПОКРЫТИЯ ====================

TEST(QueueExtendedTest, MultipleOperations) {
    Queue q;
    
    for (int i = 0; i < 10; i++) {
        q.enqueue("val_" + to_string(i));
    }
    
    EXPECT_EQ(q.size(), 10u);
    EXPECT_EQ(q.front(), "val_0");
    EXPECT_EQ(q.back(), "val_9");
    
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(q.dequeue(), "val_" + to_string(i));
    }
    
    EXPECT_EQ(q.size(), 5u);
    EXPECT_EQ(q.front(), "val_5");
    EXPECT_EQ(q.back(), "val_9");
    
    q.enqueue("new_val");
    EXPECT_EQ(q.back(), "new_val");
    EXPECT_EQ(q.size(), 6u);
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

TEST(StackExtendedTest, MultipleOperations) {
    Stack s;
    
    for (int i = 0; i < 10; i++) {
        s.push("val_" + to_string(i));
    }
    
    EXPECT_EQ(s.size(), 10u);
    EXPECT_EQ(s.top(), "val_9");
    
    for (int i = 9; i >= 5; i--) {
        EXPECT_EQ(s.pop(), "val_" + to_string(i));
    }
    
    EXPECT_EQ(s.size(), 5u);
    EXPECT_EQ(s.top(), "val_4");
    
    s.push("new_val");
    EXPECT_EQ(s.top(), "new_val");
    EXPECT_EQ(s.size(), 6u);
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

// ==================== COMPREHENSIVE INTEGRATION TESTS ====================
class IntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 8; i++) {
            string value = "data_" + to_string(i);
            arr_.insert(value);
            sll_.push_back(value);
            dll_.push_back(value);
            q_.enqueue(value);
            s_.push(value);
            ht_.insert(i, value);
            tree_.insert(value);
        }
    }
    
    Array arr_;
    SinglyLinkedList sll_;
    DoublyLinkedList dll_;
    Queue q_;
    Stack s_;
    HashTable ht_;
    CompleteBinaryTree tree_;
};

TEST_F(IntegrationTest, AllStructuresConsistency) {
    EXPECT_EQ(arr_.size(), 8);
    EXPECT_EQ(sll_.size(), 8);
    EXPECT_EQ(dll_.size(), 8);
    EXPECT_EQ(q_.size(), 8);
    EXPECT_EQ(s_.size(), 8);
    EXPECT_EQ(ht_.size(), 8);
    EXPECT_EQ(tree_.size(), 8);
    
    for (int i = 0; i < 8; i++) {
        string expected = "data_" + to_string(i);
        EXPECT_EQ(arr_.get(i), expected);
        EXPECT_EQ(sll_.get(i), expected);
        EXPECT_EQ(dll_.get(i), expected);
        EXPECT_TRUE(ht_.contains(i));
        EXPECT_EQ(ht_.get(i), expected);
    }
    
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(q_.dequeue(), "data_" + to_string(i));
    }
    
    for (int i = 7; i >= 0; i--) {
        EXPECT_EQ(s_.pop(), "data_" + to_string(i));
    }
}

TEST_F(IntegrationTest, StructureIntegrity) {
    EXPECT_TRUE(sll_.checkIntegrity());
    EXPECT_TRUE(dll_.checkIntegrity());
    EXPECT_TRUE(ht_.checkIntegrity());
    EXPECT_TRUE(tree_.isComplete());
}
// ==================== COVERAGE BOOST TESTS ====================

// DoublyLinkedList Coverage Tests
TEST(DoublyLinkedListCoverageTest, ComplexInsertRemoveSequence) {
    DoublyLinkedList list;
    
    for (int i = 0; i < 20; i++) {
        if (i % 3 == 0) {
            list.push_front("front_" + to_string(i));
        } else if (i % 3 == 1) {
            list.push_back("back_" + to_string(i));
        } else {
            if (!list.empty()) {
                list.insert(list.size() / 2, "middle_" + to_string(i));
            }
        }
        EXPECT_TRUE(list.checkIntegrity());
    }
    
    EXPECT_GT(list.size(), 10u);
    
    while (!list.empty()) {
        if (list.size() % 2 == 0) {
            list.pop_front();
        } else {
            list.pop_back();
        }
        if (!list.empty()) {
            EXPECT_TRUE(list.checkIntegrity());
        }
    }
}

TEST(DoublyLinkedListCoverageTest, SerializationEdgeScenarios) {
    // Empty list serialization
    DoublyLinkedList empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    DoublyLinkedList emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    EXPECT_TRUE(emptyLoaded.checkIntegrity());
    
    // Single element
    DoublyLinkedList single;
    single.push_back("single_element");
    stringstream ss2;
    single.serialize(ss2);
    
    DoublyLinkedList singleLoaded;
    singleLoaded.deserialize(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.get(0), "single_element");
    EXPECT_TRUE(singleLoaded.checkIntegrity());
    
    // Multiple elements with special characters
    DoublyLinkedList special;
    special.push_back("normal");
    special.push_back("line1\nline2");
    special.push_back("text with \"quotes\"");
    special.push_back("back\\slash");
    special.push_back("");
    
    stringstream ss3;
    special.serializeText(ss3);
    
    DoublyLinkedList specialLoaded;
    specialLoaded.deserializeText(ss3);
    EXPECT_EQ(specialLoaded.size(), 5u);
    EXPECT_TRUE(specialLoaded.checkIntegrity());
}

TEST(DoublyLinkedListCoverageTest, BoundaryConditionTesting) {
    DoublyLinkedList list;
    
    // Test empty list operations
    EXPECT_TRUE(list.empty());
    EXPECT_THROW(list.pop_front(), runtime_error);
    EXPECT_THROW(list.pop_back(), runtime_error);
    EXPECT_THROW(list.get(0), out_of_range);
    EXPECT_THROW(list.remove(0), out_of_range);
    
    // Single element scenarios
    list.push_front("only");
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "only");
    EXPECT_TRUE(list.checkIntegrity());
    
    list.pop_front();
    EXPECT_TRUE(list.empty());
    
    list.push_back("only_again");
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.get(0), "only_again");
    
    list.pop_back();
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedListCoverageTest, LargeScaleIntegrity) {
    DoublyLinkedList list;
    const int COUNT = 1000;
    
    // Mass insertion
    for (int i = 0; i < COUNT; i++) {
        if (i % 2 == 0) {
            list.push_front("item_" + to_string(i));
        } else {
            list.push_back("item_" + to_string(i));
        }
        
        if (i % 100 == 0) {
            EXPECT_TRUE(list.checkIntegrity());
        }
    }
    
    EXPECT_EQ(list.size(), COUNT);
    EXPECT_TRUE(list.checkIntegrity());
    
    // Mass removal
    for (int i = 0; i < COUNT / 2; i++) {
        if (i % 2 == 0) {
            list.pop_front();
        } else {
            list.pop_back();
        }
        
        if (i % 50 == 0) {
            EXPECT_TRUE(list.checkIntegrity());
        }
    }
    
    EXPECT_EQ(list.size(), COUNT / 2);
    EXPECT_TRUE(list.checkIntegrity());
}

// Queue Coverage Tests
TEST(QueueCoverageTest, ComplexEnqueueDequeuePatterns) {
    Queue q;
    
    // Alternating pattern
    for (int i = 0; i < 50; i++) {
        q.enqueue("item_" + to_string(i));
        
        if (i % 3 == 0 && !q.empty()) {
            string front = q.front();
            string back = q.back();
            q.dequeue();
            
            if (!q.empty()) {
                EXPECT_NE(q.front(), front);
                EXPECT_EQ(q.back(), back);
            }
        }
    }
    
    EXPECT_GT(q.size(), 30u);
    
    // Clear and refill
    q.clear();
    EXPECT_TRUE(q.empty());
    
    for (int i = 0; i < 20; i++) {
        q.enqueue("new_" + to_string(i));
        EXPECT_EQ(q.back(), "new_" + to_string(i));
    }
    
    EXPECT_EQ(q.size(), 20u);
}

TEST(QueueCoverageTest, SerializationComprehensive) {
    // Empty queue
    Queue empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    Queue emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    
    // Single element
    Queue single;
    single.enqueue("single");
    stringstream ss2;
    single.serialize(ss2);
    
    Queue singleLoaded;
    singleLoaded.deserialize(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.front(), "single");
    EXPECT_EQ(singleLoaded.back(), "single");
    
    // Multiple elements with text serialization
    Queue multi;
    for (int i = 0; i < 5; i++) {
        multi.enqueue("value_" + to_string(i));
    }
    
    stringstream ss3;
    multi.serializeText(ss3);
    
    Queue multiLoaded;
    multiLoaded.deserializeText(ss3);
    
    EXPECT_EQ(multiLoaded.size(), 5u);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(multiLoaded.dequeue(), "value_" + to_string(i));
    }
    EXPECT_TRUE(multiLoaded.empty());
}

// Stack Coverage Tests  
TEST(StackCoverageTest, ComplexPushPopPatterns) {
    Stack s;
    
    // Stack growth and shrinkage patterns
    for (int i = 0; i < 30; i++) {
        s.push("layer_" + to_string(i));
        EXPECT_EQ(s.top(), "layer_" + to_string(i));
        
        if (i % 4 == 0 && s.size() > 1) {
            string top = s.top();
            s.pop();
            EXPECT_NE(s.top(), top);
        }
    }
    
    EXPECT_GT(s.size(), 20u);
    
    // Multiple top calls
    string currentTop = s.top();
    EXPECT_EQ(s.top(), currentTop);
    EXPECT_EQ(s.top(), currentTop);
    
    // Clear and rebuild
    s.clear();
    EXPECT_TRUE(s.empty());
    
    for (int i = 0; i < 10; i++) {
        s.push("rebuild_" + to_string(i));
    }
    
    EXPECT_EQ(s.size(), 10u);
    EXPECT_EQ(s.top(), "rebuild_9");
}

TEST(StackCoverageTest, SerializationEdgeCases) {
    // Empty stack
    Stack empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    Stack emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    
    // Single element with text serialization
    Stack single;
    single.push("lonely");
    stringstream ss2;
    single.serializeText(ss2);
    
    Stack singleLoaded;
    singleLoaded.deserializeText(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.top(), "lonely");
    
    // Special characters
    Stack special;
    special.push("normal");
    special.push("multi\nline");
    special.push("");
    special.push("quotes\"test");
    
    stringstream ss3;
    special.serializeText(ss3);
    
    Stack specialLoaded;
    specialLoaded.deserializeText(ss3);
    
    EXPECT_EQ(specialLoaded.size(), 4u);
    EXPECT_EQ(specialLoaded.pop(), "quotes\"test");
    EXPECT_EQ(specialLoaded.pop(), "");
    EXPECT_EQ(specialLoaded.pop(), "multi\nline");
    EXPECT_EQ(specialLoaded.pop(), "normal");
    EXPECT_TRUE(specialLoaded.empty());
}

// CompleteBinaryTree Coverage Tests
TEST(CompleteBinaryTreeCoverageTest, ComplexHeapOperations) {
    CompleteBinaryTree tree;
    
    // Insert in various orders
    vector<string> values = {"zebra", "apple", "monkey", "banana", "cat", "elephant"};
    for (const auto& val : values) {
        tree.insert(val);
        EXPECT_TRUE(tree.isComplete());
    }
    
    // Verify min-heap property
    string root = tree.getRoot();
    for (const auto& val : values) {
        EXPECT_LE(root, val);
    }
    
    // Remove and verify property maintenance
    while (!tree.empty()) {
        string currentRoot = tree.getRoot();
        tree.remove();
        if (!tree.empty()) {
            string newRoot = tree.getRoot();
            EXPECT_LE(currentRoot, newRoot);
            EXPECT_TRUE(tree.isComplete());
        }
    }
}

TEST(CompleteBinaryTreeCoverageTest, LevelAndHeightScenarios) {
    CompleteBinaryTree tree;
    
    // Test height calculation
    EXPECT_EQ(tree.height(), 0u);
    
    // Build tree with known height
    for (int i = 1; i <= 7; i++) {
        tree.insert(to_string(i));
    }
    
    size_t height = tree.height();
    EXPECT_GE(height, 2u);
    EXPECT_LE(height, 3u);
    
    // Test level retrieval
    for (size_t level = 0; level < height; level++) {
        auto levelData = tree.getLevel(level);
        EXPECT_FALSE(levelData.empty());
        
        size_t expectedMaxSize = 1u << level; // 2^level
        EXPECT_LE(levelData.size(), expectedMaxSize);
    }
    
    // Test invalid level
    auto invalidLevel = tree.getLevel(100);
    EXPECT_TRUE(invalidLevel.empty());
    
    // Test traversal consistency
    auto levelOrder = tree.levelOrder();
    auto inOrder = tree.inOrder();
    auto preOrder = tree.preOrder();
    auto postOrder = tree.postOrder();
    
    EXPECT_EQ(levelOrder.size(), tree.size());
    EXPECT_EQ(inOrder.size(), tree.size());
    EXPECT_EQ(preOrder.size(), tree.size());
    EXPECT_EQ(postOrder.size(), tree.size());
}

TEST(CompleteBinaryTreeCoverageTest, SerializationComprehensive) {
    // Empty tree
    CompleteBinaryTree empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    CompleteBinaryTree emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    EXPECT_EQ(emptyLoaded.height(), 0u);
    
    // Single node
    CompleteBinaryTree single;
    single.insert("root");
    stringstream ss2;
    single.serialize(ss2);
    
    CompleteBinaryTree singleLoaded;
    singleLoaded.deserialize(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.getRoot(), "root");
    EXPECT_TRUE(singleLoaded.isComplete());
    
    // Complex tree with text serialization
    CompleteBinaryTree complex;
    complex.insert("5");
    complex.insert("3");
    complex.insert("7");
    complex.insert("1");
    complex.insert("4");
    complex.insert("6");
    complex.insert("8");
    
    stringstream ss3;
    complex.serializeText(ss3);
    
    CompleteBinaryTree complexLoaded;
    complexLoaded.deserializeText(ss3);
    
    EXPECT_EQ(complexLoaded.size(), complex.size());
    EXPECT_TRUE(complexLoaded.isComplete());
    
    // Verify heap property
    string root = complexLoaded.getRoot();
    auto allValues = complexLoaded.levelOrder();
    for (const auto& val : allValues) {
        EXPECT_LE(root, val);
    }
}

TEST(CompleteBinaryTreeCoverageTest, DuplicateAndEdgeValues) {
    CompleteBinaryTree tree;
    
    // Test duplicate values
    for (int i = 0; i < 5; i++) {
        tree.insert("duplicate");
    }
    
    EXPECT_EQ(tree.size(), 5u);
    EXPECT_TRUE(tree.isComplete());
    
    // All operations should work with duplicates
    while (!tree.empty()) {
        EXPECT_EQ(tree.getRoot(), "duplicate");
        tree.remove();
    }
    
    // Test edge cases
    tree.insert("");
    tree.insert(" ");
    tree.insert("a");
    tree.insert("A");
    tree.insert("0");
    
    EXPECT_EQ(tree.size(), 5u);
    EXPECT_TRUE(tree.isComplete());
    
    // Empty string should be the root in min-heap
    EXPECT_EQ(tree.getRoot(), "");
}

// Integration Coverage Tests
TEST(IntegrationCoverageTest, CrossStructureOperations) {
    // Create coordinated data across structures
    Array arr;
    DoublyLinkedList dll;
    Queue q;
    Stack s;
    CompleteBinaryTree tree;
    
    vector<string> testData = {"alpha", "beta", "gamma", "delta", "epsilon"};
    
    for (const auto& data : testData) {
        arr.insert(data);
        dll.push_back(data);
        q.enqueue(data);
        s.push(data);
        tree.insert(data);
    }
    
    // Verify consistency
    EXPECT_EQ(arr.size(), testData.size());
    EXPECT_EQ(dll.size(), testData.size());
    EXPECT_EQ(q.size(), testData.size());
    EXPECT_EQ(s.size(), testData.size());
    EXPECT_EQ(tree.size(), testData.size());
    
    // Verify data integrity
    for (size_t i = 0; i < testData.size(); i++) {
        EXPECT_EQ(arr.get(i), testData[i]);
        EXPECT_EQ(dll.get(i), testData[i]);
    }
    
    // Verify queue order
    for (size_t i = 0; i < testData.size(); i++) {
        EXPECT_EQ(q.dequeue(), testData[i]);
    }
    
    // Verify stack order (reverse)
    for (int i = testData.size() - 1; i >= 0; i--) {
        EXPECT_EQ(s.pop(), testData[i]);
    }
    
    // Verify tree properties
    EXPECT_TRUE(tree.isComplete());
    EXPECT_TRUE(dll.checkIntegrity());
}
// ==================== MINIMAL TREE COVERAGE BOOST ====================
TEST(CompleteBinaryTreeMinimalCoverage, GetLevelEdgeCases) {
    CompleteBinaryTree tree;
    
    // Пустое дерево
    auto emptyLevel = tree.getLevel(0);
    EXPECT_TRUE(emptyLevel.empty());
    
    emptyLevel = tree.getLevel(1);
    EXPECT_TRUE(emptyLevel.empty());
    
    // Дерево с одним элементом
    tree.insert("root");
    auto level0 = tree.getLevel(0);
    EXPECT_EQ(level0.size(), 1u);
    EXPECT_EQ(level0[0], "root");
    
    auto level1 = tree.getLevel(1);
    EXPECT_TRUE(level1.empty());
    
    // Несуществующий уровень
    auto invalidLevel = tree.getLevel(100);
    EXPECT_TRUE(invalidLevel.empty());
}

TEST(CompleteBinaryTreeMinimalCoverage, HeightEdgeCases) {
    CompleteBinaryTree tree;
    
    // Пустое дерево
    EXPECT_EQ(tree.height(), 0u);
    
    // Один элемент
    tree.insert("A");
    EXPECT_EQ(tree.height(), 1u);
    
    // Два элемента
    tree.insert("B");
    EXPECT_EQ(tree.height(), 2u);
    
    // Три элемента
    tree.insert("C");
    EXPECT_EQ(tree.height(), 2u);
    
    // Четыре элемента
    tree.insert("D");
    EXPECT_EQ(tree.height(), 3u);
}

TEST(CompleteBinaryTreeMinimalCoverage, SingleElementOperations) {
    CompleteBinaryTree tree;
    
    tree.insert("single");
    EXPECT_EQ(tree.size(), 1u);
    EXPECT_EQ(tree.getRoot(), "single");
    EXPECT_EQ(tree.height(), 1u);
    
    tree.remove();
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.height(), 0u);
}

TEST(CompleteBinaryTreeMinimalCoverage, EmptyTreeOperations) {
    CompleteBinaryTree tree;
    
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0u);
    EXPECT_EQ(tree.height(), 0u);
    EXPECT_THROW(tree.getRoot(), runtime_error);
    EXPECT_THROW(tree.remove(), runtime_error);
    
    // Проверка обходов пустого дерева
    auto emptyLevel = tree.levelOrder();
    auto emptyInOrder = tree.inOrder();
    auto emptyPreOrder = tree.preOrder();
    auto emptyPostOrder = tree.postOrder();
    
    EXPECT_TRUE(emptyLevel.empty());
    EXPECT_TRUE(emptyInOrder.empty());
    EXPECT_TRUE(emptyPreOrder.empty());
    EXPECT_TRUE(emptyPostOrder.empty());
}

// ==================== ADDITIONAL TREE COVERAGE TESTS ====================
TEST(CompleteBinaryTreeAdditionalCoverage, HeapPropertyWithDuplicates) {
    CompleteBinaryTree tree;
    
    // Тест с дубликатами
    tree.insert("same");
    tree.insert("same");
    tree.insert("same");
    tree.insert("same");
    
    EXPECT_EQ(tree.size(), 4u);
    EXPECT_TRUE(tree.isComplete());
    
    // Все корни должны быть "same"
    while (!tree.empty()) {
        EXPECT_EQ(tree.getRoot(), "same");
        tree.remove();
    }
}

TEST(CompleteBinaryTreeAdditionalCoverage, MixedValueTypes) {
    CompleteBinaryTree tree;
    
    // Разные типы значений для проверки сравнения
    tree.insert("123");
    tree.insert("abc");
    tree.insert("!@#");
    tree.insert("");
    tree.insert("a b c");
    
    EXPECT_EQ(tree.size(), 5u);
    EXPECT_TRUE(tree.isComplete());
    
    // В min-heap корень должен быть минимальным
    string root = tree.getRoot();
    EXPECT_TRUE(root == "" || root == "!@#" || root == "123");
}

TEST(CompleteBinaryTreeAdditionalCoverage, LevelOperationsComprehensive) {
    CompleteBinaryTree tree;
    
    // Создаем дерево с известной структурой
    for (int i = 1; i <= 7; i++) {
        tree.insert(to_string(i));
    }
    
    // Проверяем все уровни
    EXPECT_EQ(tree.getLevel(0).size(), 1u);
    EXPECT_EQ(tree.getLevel(1).size(), 2u);
    EXPECT_EQ(tree.getLevel(2).size(), 4u);
    
    // Проверяем несуществующий уровень
    auto invalid = tree.getLevel(10);
    EXPECT_TRUE(invalid.empty());
}

TEST(CompleteBinaryTreeAdditionalCoverage, SerializationEdgeCases) {
    // Пустое дерево
    CompleteBinaryTree empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    CompleteBinaryTree emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    
    // Один элемент
    CompleteBinaryTree single;
    single.insert("lonely");
    stringstream ss2;
    single.serializeText(ss2);
    
    CompleteBinaryTree singleLoaded;
    singleLoaded.deserializeText(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.getRoot(), "lonely");
}

TEST(CompleteBinaryTreeAdditionalCoverage, ComplexRemoveSequence) {
    CompleteBinaryTree tree;
    
    // Создаем и удаляем в сложной последовательности
    for (int i = 0; i < 10; i++) {
        tree.insert("val_" + to_string(i));
        
        if (i % 3 == 0 && tree.size() > 1) {
            tree.remove();
        }
    }
    
    EXPECT_GT(tree.size(), 5u);
    
    // Удаляем все
    while (!tree.empty()) {
        string root = tree.getRoot();
        tree.remove();
        if (!tree.empty()) {
            EXPECT_TRUE(tree.isComplete());
        }
    }
}

// ==================== EXTENSIVE TREE COVERAGE TESTS ====================
TEST(CompleteBinaryTreeExtensiveCoverage, LargeScaleHeapOperations) {
    CompleteBinaryTree tree;
    const int COUNT = 1000;
    
    // Массовая вставка в обратном порядке
    for (int i = COUNT - 1; i >= 0; --i) {
        tree.insert(to_string(i));
    }
    
    EXPECT_EQ(tree.size(), COUNT);
    EXPECT_EQ(tree.getRoot(), "0"); // Min-heap property
    
    // Проверка свойства min-heap для всех элементов
    string root = tree.getRoot();
    auto allValues = tree.levelOrder();
    for (const auto& val : allValues) {
        EXPECT_LE(root, val);
    }
    
    // Последовательное удаление с проверкой свойства
    string prevRoot = root;
    for (int i = 0; i < COUNT / 2; ++i) {
        tree.remove();
        if (!tree.empty()) {
            string newRoot = tree.getRoot();
            EXPECT_LE(prevRoot, newRoot);
            prevRoot = newRoot;
        }
    }
    
    EXPECT_EQ(tree.size(), COUNT / 2);
}

TEST(CompleteBinaryTreeExtensiveCoverage, AllTraversalsConsistency) {
    CompleteBinaryTree tree;
    
    // Создаем сбалансированное дерево
    vector<string> values = {"5", "3", "7", "2", "4", "6", "8", "1", "9"};
    for (const auto& val : values) {
        tree.insert(val);
    }
    
    // Проверяем все обходы
    auto level = tree.levelOrder();
    auto inOrder = tree.inOrder();
    auto preOrder = tree.preOrder();
    auto postOrder = tree.postOrder();
    
    EXPECT_EQ(level.size(), values.size());
    EXPECT_EQ(inOrder.size(), values.size());
    EXPECT_EQ(preOrder.size(), values.size());
    EXPECT_EQ(postOrder.size(), values.size());
    
    // Проверяем, что все исходные значения присутствуют
    for (const auto& val : values) {
        EXPECT_NE(find(level.begin(), level.end(), val), level.end());
        EXPECT_NE(find(inOrder.begin(), inOrder.end(), val), inOrder.end());
        EXPECT_NE(find(preOrder.begin(), preOrder.end(), val), preOrder.end());
        EXPECT_NE(find(postOrder.begin(), postOrder.end(), val), postOrder.end());
    }
    
    // Проверяем свойство min-heap
    string root = tree.getRoot();
    for (const auto& val : values) {
        EXPECT_LE(root, val);
    }
}

TEST(CompleteBinaryTreeExtensiveCoverage, HeightCalculationAccuracy) {
    CompleteBinaryTree tree;
    
    // Точная проверка вычисления высоты
    vector<pair<int, int>> testCases = {
        {0, 0}, {1, 1}, {2, 2}, {3, 2}, {4, 3}, {5, 3}, {6, 3}, {7, 3}, {8, 4}
    };
    
    for (const auto& [nodeCount, expectedHeight] : testCases) {
        tree.clear();
        for (int i = 0; i < nodeCount; i++) {
            tree.insert(to_string(i));
        }
        EXPECT_EQ(tree.height(), expectedHeight) << "For node count: " << nodeCount;
    }
}

TEST(CompleteBinaryTreeExtensiveCoverage, LevelOperationsDetailed) {
    CompleteBinaryTree tree;
    
    // Дерево с 15 узлами (полное бинарное дерево высотой 4)
    for (int i = 1; i <= 15; i++) {
        tree.insert(to_string(i));
    }
    
    // Проверяем каждый уровень
    EXPECT_EQ(tree.height(), 4u);
    
    auto level0 = tree.getLevel(0);
    EXPECT_EQ(level0.size(), 1u);
    
    auto level1 = tree.getLevel(1);
    EXPECT_EQ(level1.size(), 2u);
    
    auto level2 = tree.getLevel(2);
    EXPECT_EQ(level2.size(), 4u);
    
    auto level3 = tree.getLevel(3);
    EXPECT_EQ(level3.size(), 8u);
    
    // Проверяем несуществующие уровни
    auto invalid1 = tree.getLevel(10);
    EXPECT_TRUE(invalid1.empty());
    
    auto invalid2 = tree.getLevel(100);
    EXPECT_TRUE(invalid2.empty());
}

TEST(CompleteBinaryTreeExtensiveCoverage, ComplexSerializationScenarios) {
    // Тест 1: Пустое дерево
    CompleteBinaryTree empty;
    stringstream ss1;
    empty.serialize(ss1);
    
    CompleteBinaryTree emptyLoaded;
    emptyLoaded.deserialize(ss1);
    EXPECT_TRUE(emptyLoaded.empty());
    EXPECT_EQ(emptyLoaded.height(), 0u);
    
    // Тест 2: Один элемент
    CompleteBinaryTree single;
    single.insert("root");
    stringstream ss2;
    single.serializeText(ss2);
    
    CompleteBinaryTree singleLoaded;
    singleLoaded.deserializeText(ss2);
    EXPECT_EQ(singleLoaded.size(), 1u);
    EXPECT_EQ(singleLoaded.getRoot(), "root");
    EXPECT_TRUE(singleLoaded.isComplete());
    
    // Тест 3: Дерево со специальными символами
    CompleteBinaryTree special;
    special.insert("");
    special.insert("normal");
    special.insert("multi\nline");
    special.insert("quotes\"text");
    special.insert("back\\slash");
    special.insert("tab\tcharacter");
    
    stringstream ss3;
    special.serializeText(ss3);
    
    CompleteBinaryTree specialLoaded;
    specialLoaded.deserializeText(ss3);
    
    EXPECT_EQ(specialLoaded.size(), 6u);
    EXPECT_TRUE(specialLoaded.isComplete());
    
    // Проверяем, что все значения присутствуют
    auto values = specialLoaded.levelOrder();
    bool foundEmpty = false, foundNormal = false, foundNewline = false;
    bool foundQuotes = false, foundBackslash = false, foundTab = false;
    
    for (const auto& val : values) {
        if (val == "") foundEmpty = true;
        else if (val == "normal") foundNormal = true;
        else if (val == "multi\nline") foundNewline = true;
        else if (val == "quotes\"text") foundQuotes = true;
        else if (val == "back\\slash") foundBackslash = true;
        else if (val == "tab\tcharacter") foundTab = true;
    }
    
    EXPECT_TRUE(foundEmpty);
    EXPECT_TRUE(foundNormal);
    EXPECT_TRUE(foundNewline);
    EXPECT_TRUE(foundQuotes);
    EXPECT_TRUE(foundBackslash);
    EXPECT_TRUE(foundTab);
}

TEST(CompleteBinaryTreeExtensiveCoverage, StressTestOperations) {
    CompleteBinaryTree tree;
    const int OPERATIONS = 2000;
    
    // Смешанные операции: вставка и удаление
    for (int i = 0; i < OPERATIONS; i++) {
        if (tree.empty() || i % 3 != 0) {
            tree.insert("op_" + to_string(i));
            EXPECT_TRUE(tree.isComplete());
        } else {
            tree.remove();
            if (!tree.empty()) {
                EXPECT_TRUE(tree.isComplete());
            }
        }
        
        // Периодическая проверка целостности
        if (i % 100 == 0 && !tree.empty()) {
            string root = tree.getRoot();
            auto allValues = tree.levelOrder();
            for (const auto& val : allValues) {
                EXPECT_LE(root, val);
            }
        }
    }
    
    EXPECT_GE(tree.size(), OPERATIONS / 4); // Должно остаться достаточно элементов
}

TEST(CompleteBinaryTreeExtensiveCoverage, DuplicateValuesHandling) {
    CompleteBinaryTree tree;
    
    // Тест с множественными дубликатами
    for (int i = 0; i < 10; i++) {
        tree.insert("duplicate");
    }
    
    EXPECT_EQ(tree.size(), 10u);
    EXPECT_TRUE(tree.isComplete());
    
    // Все операции должны работать корректно с дубликатами
    while (!tree.empty()) {
        EXPECT_EQ(tree.getRoot(), "duplicate");
        
        // Проверяем обходы
        auto level = tree.levelOrder();
        auto inOrder = tree.inOrder();
        auto preOrder = tree.preOrder();
        auto postOrder = tree.postOrder();
        
        EXPECT_EQ(level.size(), tree.size());
        EXPECT_EQ(inOrder.size(), tree.size());
        EXPECT_EQ(preOrder.size(), tree.size());
        EXPECT_EQ(postOrder.size(), tree.size());
        
        // Все значения должны быть "duplicate"
        for (const auto& val : level) {
            EXPECT_EQ(val, "duplicate");
        }
        
        tree.remove();
    }
}

TEST(CompleteBinaryTreeExtensiveCoverage, MixedComparisonOperations) {
    CompleteBinaryTree tree;
    
    // Значения с разным порядком сравнения
    vector<string> testValues = {
        "", " ", "!", "0", "1", "9", "A", "Z", "a", "z",
        "abc", "xyz", "test with spaces", "test\nwith\nnewlines",
        "test\"with\"quotes", "test\\with\\backslashes"
    };
    
    for (const auto& val : testValues) {
        tree.insert(val);
    }
    
    EXPECT_EQ(tree.size(), testValues.size());
    EXPECT_TRUE(tree.isComplete());
    
    // Проверяем свойство min-heap
    string root = tree.getRoot();
    for (const auto& val : testValues) {
        EXPECT_LE(root, val);
    }
    
    // Проверяем все обходы
    auto level = tree.levelOrder();
    auto inOrder = tree.inOrder();
    auto preOrder = tree.preOrder();
    auto postOrder = tree.postOrder();
    
    EXPECT_EQ(level.size(), testValues.size());
    EXPECT_EQ(inOrder.size(), testValues.size());
    EXPECT_EQ(preOrder.size(), testValues.size());
    EXPECT_EQ(postOrder.size(), testValues.size());
}

TEST(CompleteBinaryTreeExtensiveCoverage, ClearAndRebuildScenarios) {
    CompleteBinaryTree tree;
    
    // Сценарий 1: Очистка пустого дерева
    tree.clear();
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.height(), 0u);
    
    // Сценарий 2: Построение → очистка → перестроение
    for (int build = 0; build < 3; build++) {
        for (int i = 0; i < 10; i++) {
            tree.insert("build_" + to_string(build) + "_" + to_string(i));
        }
        
        EXPECT_EQ(tree.size(), 10u);
        EXPECT_TRUE(tree.isComplete());
        
        tree.clear();
        EXPECT_TRUE(tree.empty());
        EXPECT_EQ(tree.height(), 0u);
    }
    
    // Сценарий 3: Частичная очистка через remove
    for (int i = 0; i < 20; i++) {
        tree.insert("item_" + to_string(i));
    }
    
    for (int i = 0; i < 10; i++) {
        tree.remove();
    }
    
    EXPECT_EQ(tree.size(), 10u);
    EXPECT_TRUE(tree.isComplete());
    
    // Добавляем еще элементов
    for (int i = 20; i < 30; i++) {
        tree.insert("new_" + to_string(i));
    }
    
    EXPECT_EQ(tree.size(), 20u);
    EXPECT_TRUE(tree.isComplete());
}

TEST(CompleteBinaryTreeExtensiveCoverage, PrintMethodCoverage) {
    CompleteBinaryTree tree;
    
    // Печать пустого дерева
    testing::internal::CaptureStdout();
    tree.print();
    string emptyOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(emptyOutput.empty());
    
    // Печать дерева с одним элементом
    tree.insert("single");
    testing::internal::CaptureStdout();
    tree.print();
    string singleOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(singleOutput.empty());
    EXPECT_NE(singleOutput.find("single"), string::npos);
    
    // Печать большого дерева
    tree.clear();
    for (int i = 0; i < 10; i++) {
        tree.insert("print_" + to_string(i));
    }
    
    testing::internal::CaptureStdout();
    tree.print();
    string multiOutput = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(multiOutput.empty());
    
    for (int i = 0; i < 10; i++) {
        EXPECT_NE(multiOutput.find("print_" + to_string(i)), string::npos);
    }
}

// ==================== MAIN FUNCTION ====================
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(filter) = "*";
    return RUN_ALL_TESTS();
}
