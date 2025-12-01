#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <random>
#include "Array.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "HashTable.h"
#include "CompleteBinaryTree.h"

using namespace std;
using namespace std::chrono;

class Benchmark {
private:
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dis;

public:
    Benchmark() : gen(rd()), dis(1, 10000) {}

    string randomString(size_t length = 10) {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        
        string result;
        result.reserve(length);
        for (size_t i = 0; i < length; ++i) {
            result += alphanum[dis(gen) % (sizeof(alphanum) - 1)];
        }
        return result;
    }

    int randomInt() {
        return dis(gen);
    }

    template<typename Func>
    long long measureTime(Func&& func) {
        auto start = high_resolution_clock::now();
        func();
        auto end = high_resolution_clock::now();
        return duration_cast<milliseconds>(end - start).count();
    }

    void benchmarkArray(int operations = 10000) {
        cout << "=== Array Benchmark ===" << endl;
        
        Array arr;
        long long insertTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                arr.insert(randomString());
            }
        });
        cout << "Insert " << operations << " elements: " << insertTime << " ms" << endl;

        long long accessTime = measureTime([&]() {
            for (int i = 0; i < min(1000, operations); i++) {
                arr.get(i % arr.size());
            }
        });
        cout << "Access 1000 elements: " << accessTime << " ms" << endl;

        long long removeTime = measureTime([&]() {
            while (!arr.empty()) {
                arr.remove(0);
            }
        });
        cout << "Remove all elements: " << removeTime << " ms" << endl;
        cout << endl;
    }

    void benchmarkSinglyLinkedList(int operations = 10000) {
        cout << "=== Singly Linked List Benchmark ===" << endl;
        
        SinglyLinkedList list;
        long long insertTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                list.push_back(randomString());
            }
        });
        cout << "Insert " << operations << " elements: " << insertTime << " ms" << endl;

        long long accessTime = measureTime([&]() {
            for (int i = 0; i < min(1000, operations); i++) {
                list.get(i % list.size());
            }
        });
        cout << "Access 1000 elements: " << accessTime << " ms" << endl;

        long long removeTime = measureTime([&]() {
            while (!list.empty()) {
                list.pop_front();
            }
        });
        cout << "Remove all elements: " << removeTime << " ms" << endl;
        cout << endl;
    }

    void benchmarkDoublyLinkedList(int operations = 10000) {
        cout << "=== Doubly Linked List Benchmark ===" << endl;
        
        DoublyLinkedList list;
        long long insertTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                list.push_back(randomString());
            }
        });
        cout << "Insert " << operations << " elements: " << insertTime << " ms" << endl;

        long long accessTime = measureTime([&]() {
            for (int i = 0; i < min(1000, operations); i++) {
                list.get(i % list.size());
            }
        });
        cout << "Access 1000 elements: " << accessTime << " ms" << endl;

        long long removeTime = measureTime([&]() {
            while (!list.empty()) {
                list.pop_front();
            }
        });
        cout << "Remove all elements: " << removeTime << " ms" << endl;
        cout << endl;
    }

    void benchmarkQueue(int operations = 10000) {
        cout << "=== Queue Benchmark ===" << endl;
        
        Queue q;
        long long enqueueTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                q.enqueue(randomString());
            }
        });
        cout << "Enqueue " << operations << " elements: " << enqueueTime << " ms" << endl;

        long long dequeueTime = measureTime([&]() {
            while (!q.empty()) {
                q.dequeue();
            }
        });
        cout << "Dequeue all elements: " << dequeueTime << " ms" << endl;
        cout << endl;
    }

    void benchmarkStack(int operations = 10000) {
        cout << "=== Stack Benchmark ===" << endl;
        
        Stack s;
        long long pushTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                s.push(randomString());
            }
        });
        cout << "Push " << operations << " elements: " << pushTime << " ms" << endl;

        long long popTime = measureTime([&]() {
            while (!s.empty()) {
                s.pop();
            }
        });
        cout << "Pop all elements: " << popTime << " ms" << endl;
        cout << endl;
    }

    void benchmarkHashTable(int operations = 10000) {
        cout << "=== Hash Table Benchmark ===" << endl;
        
        HashTable ht;
        long long insertTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                ht.insert(i, randomString());
            }
        });
        cout << "Insert " << operations << " elements: " << insertTime << " ms" << endl;

        long long accessTime = measureTime([&]() {
            for (int i = 0; i < min(1000, operations); i++) {
                ht.get(i % operations);
            }
        });
        cout << "Access 1000 elements: " << accessTime << " ms" << endl;

        long long removeTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                ht.remove(i);
            }
        });
        cout << "Remove all elements: " << removeTime << " ms" << endl;
        cout << endl;
    }

    void benchmarkTree(int operations = 10000) {
        cout << "=== Complete Binary Tree Benchmark ===" << endl;
        
        CompleteBinaryTree tree;
        long long insertTime = measureTime([&]() {
            for (int i = 0; i < operations; i++) {
                tree.insert(randomString());
            }
        });
        cout << "Insert " << operations << " elements: " << insertTime << " ms" << endl;

        long long removeTime = measureTime([&]() {
            while (!tree.empty()) {
                tree.remove();
            }
        });
        cout << "Remove all elements: " << removeTime << " ms" << endl;
        cout << endl;
    }

    void runAllBenchmarks(int operations = 10000) {
        cout << "🚀 Running Benchmarks (" << operations << " operations each)" << endl;
        cout << "=========================================" << endl;
        
        benchmarkArray(operations);
        benchmarkSinglyLinkedList(operations);
        benchmarkDoublyLinkedList(operations);
        benchmarkQueue(operations);
        benchmarkStack(operations);
        benchmarkHashTable(operations);
        benchmarkTree(operations);
        
        cout << "✅ All benchmarks completed!" << endl;
    }
};

int main(int argc, char* argv[]) {
    Benchmark bench;
    int operations = 10000;
    
    if (argc > 1) {
        try {
            operations = stoi(argv[1]);
        } catch (...) {
            cout << "Invalid operation count. Using default: 10000" << endl;
        }
    }
    
    bench.runAllBenchmarks(operations);
    
    return 0;
}