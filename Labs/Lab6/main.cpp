#include <iostream>
#include "List.h"
#include "DynamicArray.h"
#include "Deque.h"
#include "Queue.h"
#include "Stack.h"

int main() {
    
    // DynamicArray test
    int arr[4] = {1, 2, 3, 4};
    DynamicArray array(arr, 4);
    array.print();
    std::cout << "Nodes: " << array.get(0) << " " << array.get(1) << " " << array.get(2) << " " << array.get(3) << "\n";
    DynamicArray array2(array);
    array2.print();
    DynamicArray array3 = array;
    array3.set(0, 7);
    array3.print();
    array3.set(1, 8);
    array3.print();
    array3.set(2, 9);
    array3.print();
    array3.set(3, 10);
    array3.print();
    array3.push_back(11);
    array3.print();
    array3.push_back(12);
    array3.print();

    // Deque
    Deque deque;
    deque.push_front(3);
    deque.push_front(2);
    deque.push_front(1);
    deque.push_back(4);
    deque.push_back(5);
    deque.push_back(6);
    deque.print();
    deque.pop_front();
    deque.print();
    deque.pop_back();
    deque.print();
    std::cout << "Peek front: " << deque.peek_front() << "\n";
    std::cout << "Peek back: " << deque.peek_back() << "\n";

    // Stack
    Stack stack;
    stack.print();
    stack.push(0);
    stack.print();
    stack.push(1);
    stack.print();
    stack.push(2);
    stack.print();
    stack.push(3);
    stack.print();
    stack.push(4);
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.print();
    stack.pop();
    stack.print();
    std::cout << "Peek: " << stack.top() << std::endl;

    // Queue
    Queue queue;
    queue.print();
    queue.push(0);
    queue.print();
    queue.push(1);
    queue.print();
    queue.push(2);
    queue.print();
    queue.push(3);
    queue.print();
    queue.push(4);
    queue.print();
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
    queue.pop();
    queue.print();
    std::cout << "Peek: " << queue.peek() << std::endl;
    std::cout << "End" << std::endl;
}
