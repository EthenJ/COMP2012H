#include "Deque.h"
#include <iostream>

void Deque::push_front(int data) {
    // TODO
}

void Deque::push_back(int data) {
    // TODO
}

void Deque::pop_front() {
    // TODO
}

void Deque::pop_back() {
    // TODO
}

int Deque::peek_front() const {
    // TODO
}

int Deque::peek_back() const {
    // TODO
}

void Deque::print() const {
    std::cout << "Deque | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | ";
    for (int i = 0; i < size(); i++) {
        std::cout << "<" << get(i) << ">";
    }
    std::cout << std::endl;
}
