#pragma once 

#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node{
        T data;
        Node* next;

        Node(T value, Node* nxt=nullptr) : data(value), next(nxt) {}
    };
    Node* head,tail;
    std::size_t count = 0;
public:
    Queue() = default;

    ~Queue(){
        dequeue_all();
    }

    void dequeue() {
        if (is_empty()) {
            throw std::runtime_error("Queue error: Queue is empty and you can't dequeue");
        }
        Node* old = head;
        head = head->next;
        delete old;
        count--;
    }

    void enqueue(Node& newNode) {
        if(newNode == nullptr) {
            throw std::runtime_error("Queue error: Adding a new null node");
        }
        newNode->next = tail;
        tail = newNode;
        count++;
    }

    const void is_empty() {
        return head == tail || head == nullptr || tail == nullptr;
    }
    void dequeue_all() {
        while(is_empty()) {
            dequeue();
        }
    }

    std::size_t size() {
        return count;
    }
};