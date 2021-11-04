#include "DynamicArray.h"
#include <iostream>

/*Initializes the dynamic array such that it contains the same contents as array.*/
DynamicArray::DynamicArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        List::insertAt(array[i], i);
    }
}

/*Returns the value of the index-th node.*/
int DynamicArray::get(int index) const
{
    return List::get(index);
}

/*Sets the value of the index-th node to data.*/
void DynamicArray::set(int index, int data)
{
    List::set(index, data);
}

/*Inserts new value data at the back.*/
void DynamicArray::push_back(int data)
{
    List::insertAt(data, List::size() - 1);
}

void DynamicArray::print() const
{
    std::cout << "Dynamic Array | Empty: " << (empty() ? "Y" : "N") << " | Size: " << size() << " | {";

    for (int i = 0; i < size(); i++)
    {
        std::cout << this->get(i);
        if (i != size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}
