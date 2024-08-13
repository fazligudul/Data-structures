//Fazlı Güdül
//Section 2
//student id: 22002785
#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template<typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& item) {
        top = new Node(item, top);
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        Node* node = top;
        T data = node->data;
        top = top->next;
        delete node;
        return data;
    }

    T& peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack<>::peek(): empty stack");
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

#endif // STACK_H
