#include "List.h"
#include <iostream>

List::Node::Node(int data) : data(data), next(nullptr){};

List::List() : head(nullptr){};

/*Initializes the list as a copy of rhs, by deep-copying every Node.*/
List::List(const List &rhs) : head(nullptr)
{
    assign(rhs);
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
    if (!empty())
    {
        for (Node *this_node = head, *next_node; this_node != nullptr; this_node = next_node)
        {
            next_node = this_node->next;
            delete this_node;
        }
        head = nullptr;
    }

    if (rhs.empty())
    {
        return *this;
    }
    // perform deep copy
    for (int i = 0; i < rhs.size(); i++)
    {
        insertAt(rhs.get(i), i);
    }

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

/*Inserts a new node containing data such that it becomes the index-th node.*/
void List::insertAt(int data, int index)
{
    if (index < 0 && !empty())
    {
        return;
    }

    // insert the new Node such that it is at position = index
    Node *this_node = new Node(data);
    this_node->next = nullptr;
    if (empty())
    {
        head = this_node;
        return;
    }

    int node_num = 0;
    Node *previous_node = head;
    for (; node_num < index - 1 && previous_node != nullptr; node_num++)
    {
        previous_node = previous_node->next;
    }
    if (previous_node->next != nullptr)
    {
        this_node->next = previous_node->next;
    }
    if (previous_node != this_node)
    {
        previous_node->next = this_node;
    }
}

/*Removes the index-th node.*/
void List::removeAt(int index)
{
    if (!empty())
    {
        if (index == 0)
        {
            Node *head_next = head->next;
            delete head;
            head = head_next;
            return;
        }

        int node_num = 0;
        Node *previous_node = head;
        for (; node_num < index - 1 && previous_node != nullptr; node_num++)
        {
            previous_node = previous_node->next;
        }
        if (previous_node->next != nullptr)
        {
            Node *this_node = previous_node->next;
            previous_node->next = this_node->next;
            delete this_node;
            this_node = nullptr;
        }
    }
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

/*Sets the value of the index-th node to data*/
void List::set(int index, int data)
{
    int node_num = 0;
    Node *this_node = head;
    for (; node_num < index && this_node != nullptr; node_num++)
    {
        this_node = this_node->next;
    }
    if (this_node != nullptr)
    {
        this_node->data = data;
    }
}
