#ifndef _STACK
#define _STACK

#include "Deque.h"

class Stack : private Deque {
public:
    void push(int data);
    void pop();
    int top() const;
    void print() const;    
};

#endif