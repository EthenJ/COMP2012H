#include "Stack.h"
#include <iostream>

/*Inserts data at the front.*/
void Stack::push(int data)
{
    Deque::push_front(data);
}

/*Removes the first item at the front.*/
void Stack::pop()
{
    List::removeAt(0);
}

/*Returns the first item, without changing the queue. If the queue is empty already, prints Empty! and return 0.*/
int Stack::top() const
{
    return Deque::peek_front();
}

void Stack::print() const
{
    std::cout << "Stack | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | ";
    for (int i = 0; i < size(); i++)
    {
        std::cout << "<" << get(i) << "]";
    }
    std::cout << std::endl;
}
