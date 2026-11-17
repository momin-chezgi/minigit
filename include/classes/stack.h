#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value, Node* nxt = nullptr)
            : data(value), next(nxt) {}
    };

    Node* head = nullptr;
    std::size_t count = 0;

public:
    Stack() = default;

    ~Stack() {
        popAll();
    }

    void push(const T& newData) {
        head = new Node(newData, head);
        count++;
    }

    void pop() {
        if (is_empty()) {
            throw std::runtime_error("Stack overflow: cannot pop from an empty stack");
        }

        Node* old = head;
        head = old->next;
        delete old;
        count--;
    }

    T& top() {
        if (is_empty()) {
            throw std::runtime_error("Stack is empty: can't access top element");
        }
        return head->data;
    }

    const T& top() const {
        if (is_empty()) {
            throw std::runtime_error("Stack is empty: can't access top element");
        }
        return head->data;
    }

    bool is_empty() const noexcept {
        return head == nullptr;
    }

    std::size_t size() const noexcept {
        return count;
    }

    void popAll() {
        while (!is_empty()) {
            pop();
        }
    }
};
