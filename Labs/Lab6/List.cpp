#include "List.h"
#include <iostream>

List::Node::Node(int data) : data(data), next(nullptr){};

List::List() : head(nullptr){};

/*Initializes the list as a copy of rhs, by deep-copying every Node.*/
List::List(const List &rhs)
{
    head = new Node(rhs.head->data);
    Node *target_node;
    head->next = target_node;
    for (this_node = rhs.head->next; this_node != nullptr; this_node = this_node->next)
    {
        Node
    }
    // TODO
};

/*Deletes all Nodes in the list.*/
List::~List()
{
    for (Node *this_node = head, *next_node; this_node != nullptr; this_node = next_node)
    {
        next_node = this_node->next;
        delete this_node;
    }
};

/*Copy the content of rhs by deep-copying every Node. 、
 *Delete the existing array / nodes. At the end, return the current object as a reference.*/
List &List::assign(const List &rhs)
{
    /*Delete the existing array / nodes.*/
    for (Node *this_node = head, *next_node; this_node != nullptr; this_node = next_node)
    {
        next_node = this_node->next;
        delete this_node;
    }
    // perform deep copy

    /*return the current object as a reference.*/
    return *this;
}

/*Returns whether the list is empty.*/
bool List::empty() const
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

/*Return the no. of nodes in the list.*/
int List::size() const
{
    int node_size = 0;
    for (Node *this_node = head; this_node != nullptr; this_node = this_node->next)
    {
        node_size++;
    }
    return node_size;
}

void List::print() const
{
    std::cout << "Linked List | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | ";
    for (Node *ptr = head; ptr != nullptr; ptr = ptr->next)
    {
        std::cout << ptr->data << " -> ";
    }
    std::cout << "x" << std::endl;
}

void List::insertAt(int data, int index)
{
    // TODO
    // insert the new Node such that it is at position = index
}

void List::removeAt(int index)
{
    // TODO
}

/*Returns the value of the index-th node.*/
int List::get(int index) const
{
    int node_num = 0;
    Node *this_node = head;
    for (; node_num < index && this_node != nullptr; node_num++)
    {
        this_node = this_node->next;
    }
    return this_node->data;
}

void List::set(int index, int data)
{
    // TODO
}
