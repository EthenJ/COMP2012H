#include "Queue.h"
#include <iostream>

/*Inserts data at the back.*/
void Queue::push(int data)
{
    Deque::push_back(data);
}

/*Removes the first item at the front.*/
void Queue::pop()
{
    List::removeAt(0);
}

/*Returns the first item, without changing the queue. If the queue is empty already, prints Empty! and return 0.*/
int Queue::peek() const
{
    return Deque::peek_front();
}

void Queue::print() const
{
    std::cout << "Queue | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | ";
    for (int i = 0; i < size(); i++)
    {
        std::cout << "<" << get(i) << "]";
    }
    std::cout << std::endl;
}
