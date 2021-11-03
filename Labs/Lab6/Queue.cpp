#include "Queue.h"
#include <iostream>

void Queue::push(int data) {
    // TODO
}

void Queue::pop() {
    // TODO
}

int Queue::peek() const {
    // TODO
}

void Queue::print() const {
    std::cout << "Queue | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() <<" | ";
    for(int i = 0; i < size(); i++) {
        std::cout << "<" << get(i) << "]";
    }    
    std::cout << std::endl;    
}
