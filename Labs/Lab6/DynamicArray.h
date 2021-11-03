#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#include "List.h"

class DynamicArray : public List {
public:
    DynamicArray(int array[], int size);
    
    int get(int index) const;
    void set(int index, int data);
    void push_back(int data);
    void print() const;
};

#endif