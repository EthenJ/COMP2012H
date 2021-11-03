#include "DynamicArray.h"
#include <iostream>

DynamicArray::DynamicArray(int array[], int size) {
    // TODO
}

int DynamicArray::get(int index) const {
    // TODO
}

void DynamicArray::set(int index, int data) {
    // TODO
}

void DynamicArray::push_back(int data) {
    // TODO
}

void DynamicArray::print() const {
    std::cout << "Dynamic Array | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | {";
    
    for (int i = 0; i < size(); i++) {
        std::cout << this->get(i);
        if( i != size() - 1) {
            std::cout << ", ";
        }
    }    
    std::cout << "}" << std::endl;    
}
