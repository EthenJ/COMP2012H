#ifndef _QUEUE
#define _QUEUE

#include "Deque.h"

class Queue : public Deque {
public:
    void push(int data);
    void pop();
    int peek() const;
    void print() const;
};

#endif