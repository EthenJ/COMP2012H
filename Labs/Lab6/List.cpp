#include "List.h"
#include <iostream>

List::Node::Node(int data): data(data), next(nullptr) {};

List::List(): head(nullptr) { };

List::List(const List& rhs) {
    // TODO
};

List::~List() {
    // TODO
};

List& List::assign(const List& rhs) {
    // TODO
    // perform deep copy
}

bool List::empty() const {
    // TODO
}

int List::size() const {
    // TODO
}

void List::print() const {
    std::cout << "Linked List | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | ";
    for(Node* ptr = head; ptr != nullptr; ptr = ptr->next) {
        std::cout << ptr->data << " -> ";
    }    
    std::cout << "x" << std::endl;
}

void List::insertAt(int data, int index) {
    // TODO
    // insert the new Node such that it is at position = index
}

void List::removeAt(int index) {
    // TODO
}

int List::get(int index) const {
    // TODO
}

void List::set(int index, int data) {
    // TODO
}
