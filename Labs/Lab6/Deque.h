#ifndef _DEQUE
#define _DEQUE

#include "List.h"

class Deque : public List {
public:
    void push_front(int data);
    void push_back(int data);
    void pop_front();
    void pop_back();
    int peek_front() const;
    int peek_back() const;
    void print() const;
};

#endif