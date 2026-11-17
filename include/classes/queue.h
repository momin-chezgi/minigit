#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value, Node* nxt = nullptr)
            : data(value), next(nxt) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t count = 0;

public:
    Queue() = default;

    ~Queue() {
        dequeue_all();
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        ++count;
    }

    void dequeue() {
        if (is_empty()) {
            throw std::runtime_error("Queue error: Queue is empty and you can't dequeue");
        }

        Node* old = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete old;
        --count;
    }

    T& front() {
        if (is_empty()) {
            throw std::runtime_error("Queue is empty: can't access front element");
        }
        return head->data;
    }

    const T& front() const {
        if (is_empty()) {
            throw std::runtime_error("Queue is empty: can't access front element");
        }
        return head->data;
    }

    bool is_empty() const noexcept {
        return head == nullptr;
    }

    void dequeue_all() {
        while (!is_empty()) {
            dequeue();
        }
    }

    std::size_t size() const noexcept {
        return count;
    }
};