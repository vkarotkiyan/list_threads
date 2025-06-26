#include "list.h"
using namespace  std;

Node::Node(int value) : m_value(value), m_next(nullptr) {
    m_node_mutex = new mutex;
};
Node::~Node() { delete m_node_mutex; };


FineGrainedQueue::~FineGrainedQueue() {
    clear();
}

void FineGrainedQueue::push_back(int value) {
    Node* node = new Node(value);
    if (m_head == nullptr) {
        m_head = node;
        return;
    }
    Node* last = m_head;
    while (last->m_next != nullptr) {
        last = last->m_next;
    }
    last->m_next = node;
    return;
};

void FineGrainedQueue::insertIntoMiddle(int value, int pos) {
    if (pos < 0) {
        cout << "ERROR: bad parameter" << endl;
        return;
    }
    Node* current;
    Node* node = new Node(value);
    m_queue_mutex->lock();
    if (m_head == nullptr){ // если список пустой
        m_head = node;
        m_queue_mutex->unlock();
        return;
    }
    if (pos == 0){ // вставка в начало списка
        node->m_next = m_head;
        m_head = node;
        m_queue_mutex->unlock();
        return;
    }
    current = m_head;
    for (int i = 0; i < pos - 1; i++) {
        if (current->m_next == nullptr) break; // если pos > list.size
        current = current->m_next;
    }
    m_queue_mutex->unlock();
    current->m_node_mutex->lock();
    node->m_next = current->m_next;
    current->m_next = node;
    current->m_node_mutex->unlock();
};

void FineGrainedQueue::remove(int value){
    Node* current;
    Node* prev;
    m_queue_mutex->lock();
    if (m_head == nullptr){ // обработка случая пустого списка
        m_queue_mutex->unlock();
        return;
    }
    if (m_head->m_value == value){ // обработка случая удаления первого элемента
        current = this->m_head->m_next;
        delete m_head;
        m_head = current;
        m_queue_mutex->unlock();
        return;
    }
    prev = this->m_head;
    current = this->m_head->m_next;
    prev->m_node_mutex->lock();
    m_queue_mutex->unlock();
    if (current)
        current->m_node_mutex->lock();
    while (current) {
        if (current->m_value == value) {
            prev->m_next = current->m_next;
            prev->m_node_mutex->unlock();
            current->m_node_mutex->unlock();
            delete current;
            return;
        }
        Node* old_prev = prev;
        prev = current;
        current = current->m_next;
        old_prev->m_node_mutex->unlock();
        if (current)
            current->m_node_mutex->lock();
    }
    prev->m_node_mutex->unlock();
}

void FineGrainedQueue::show()
{
    Node* current = m_head;
    while(current != nullptr) {
        cout << current->m_value << " ";
        current = current->m_next;
    }
    cout << endl;
};

void FineGrainedQueue::clear() {
    Node* current = m_head;
    Node* temp = nullptr;
    while (current != nullptr) {
        temp = current->m_next;
        delete current;
        current = temp;
    }
};
