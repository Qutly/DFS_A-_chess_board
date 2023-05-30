#ifndef STOS_STOS_H
#define STOS_STOS_H
#include <iostream>
#include <string>

template <typename E>
class Stack {
private:
    struct Node {
        E data;
        Node* next;
        Node(const E& data, Node* next)
                : data(data), next(next) {}
    };
    Node* head;
    int length;
public:
    Stack()
        : head(nullptr), length(0) {}
    void push(const E& data);
    E pop();
    bool isEmpty() const;
    std::pair<int,int> peek();
    void print();
};

template <typename E>
    void Stack<E>::push(const E& data) {
        Node* newNode = new Node(data, nullptr);

        if(isEmpty()) {
            head = newNode;
            length++;
            return;
        }
        newNode->next = head;
        head = newNode;
        length++;
    }

template <typename E>
    E Stack<E>::pop() {
        if (isEmpty())
            throw std::invalid_argument("Stack is empty. Cannot delete element.");

        Node* toRemove = head;
        E saveData = head->data;
        head = toRemove->next;
        delete toRemove;
        length--;
        return saveData;
    }

template <typename E>
    bool Stack<E>::isEmpty() const {
        return head == nullptr;
    }

template <typename E>
std::pair<int,int> Stack<E>::peek() {
    std::pair<int,int> peek = std::make_pair(head->data.first, head->data.second);
    return peek;
}

template <typename E>
    void Stack<E>::print () {
        Node* tmp = head;
        std::cout << "Stack: ";
        while(tmp != nullptr) {
            std::cout << "[" << tmp->data.first << "," << tmp->data.second << "]" << " ";
            tmp = tmp->next;
        }
        std::cout << "\n";
    }

#endif
