#include "Deque.h"
#include <iostream>

/*Inserts data at the front.*/
void Deque::push_front(int data)
{
    if (empty())
    {
        List::insertAt(-1, 0);
    }
    else
    {
        List::insertAt(List::get(0), 0);
    }
    List::set(0, data);
}

/*Inserts data at the back.*/
void Deque::push_back(int data)
{
    List::insertAt(data, List::size() - 1);
}

/*Removes the first item at the front.*/
void Deque::pop_front()
{
    List::removeAt(0);
}

/*Removes the last item at the back.*/
void Deque::pop_back()
{
    List::removeAt(List::size() - 1);
}

/*Returns the first item, without changing the queue. If the queue is empty already, prints Empty! and return 0.*/
int Deque::peek_front() const
{
    if (List::empty())
    {
        std::cout << "Empty!" << std::endl;
        return 0;
    }

    return List::get(0);
}

/*Returns the last item, without changing the queue. If the queue is empty already, prints Empty! and return 0.*/
int Deque::peek_back() const
{
    if (List::empty())
    {
        std::cout << "Empty!" << std::endl;
        return 0;
    }

    return List::get(List::size() - 1);
}

void Deque::print() const
{
    std::cout << "Deque | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | ";
    for (int i = 0; i < size(); i++)
    {
        std::cout << "<" << get(i) << ">";
    }
    std::cout << std::endl;
}
