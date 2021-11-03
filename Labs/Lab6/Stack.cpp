#include "Stack.h"
#include <iostream>

void Stack::push(int data) {
    // TODO
}

void Stack::pop() {
    // TODO
}

int Stack::top() const {
    // TODO
}

void Stack::print() const {
    std::cout << "Stack | Empty: " << (empty()?"Y":"N") << " | Size: " << size() << " | ";
    for(int i = 0; i < size(); i++) {
        std::cout << "<" << get(i) << "]";
    }
    std::cout << std::endl;
}
