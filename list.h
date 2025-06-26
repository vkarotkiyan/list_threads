#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <shared_mutex>

// Потокобезопасный список /////////////////////////////////////////////////////

struct Node {
    int m_value;
    Node* m_next;
    std::mutex* m_node_mutex;
    Node(int value);
    ~Node();
};

class FineGrainedQueue {
public:
    FineGrainedQueue() : m_head(nullptr){ m_queue_mutex = new std::mutex; };
    ~FineGrainedQueue();
    void push_back(int value);
    void insertIntoMiddle(int value, int pos); // Потокобезопасный метод
    void remove(int value); // Потокобезопасный метод
    void show();
    void clear();
private:
    Node* m_head;
    std::mutex* m_queue_mutex;
};
