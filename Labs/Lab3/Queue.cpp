//
// Queue.cpp
//

#include "Queue.h"
#include "EthernetFrame.h"

// TODO: task 3: queue operations

void queueResizeRing(Queue &queue, unsigned int newCapacity) // Resize the internal array of the given queue to a given new capacity.
{
    // Dynamically allocate a new array of given size and copy the pointers in the old array to it. Remember to correctly maintain head, size and capacity.
    EthernetFrame **temp = new EthernetFrame *[queue.size];
    for (int i = 0; i < queue.size; i++)
    {
        temp[i] = queue.ring[(queue.head + i) % queue.capacity];
    }
    // If the new capacity is smaller than the current size, truncate the elements towards the back of the queue. Say, you are resizing a queue with capacity 10 and size 8 to a new capacity of 5. Then the three elements at the back of the queue should be freed.
    if (newCapacity < queue.size)
    {
        for (int i = newCapacity; i < queue.size; i++)
        {
            freeFrame(temp[i]);
        }
        queue.size = newCapacity;
    }
    queue.capacity = newCapacity;
    delete queue.ring;
    queue.ring = temp;
    queue.head = 0;
}

void enqueue(Queue &queue, EthernetFrame *frame)
{
    if (queue.size >= queue.capacity)
    {
        // Change the capacity of the internal array to (current queue size + 1) * 2 when necessary. Remember the queue is circular.
        queueResizeRing(queue, (queue.size + 1) * 2);
    }
    else
    {
        queueResizeRing(queue, queue.size);
    }
    queue.ring[(queue.head + queue.size + 1) % queue.capacity] = frame;
    // Add a frame to the back of the queue. No need to check whether the pointer to frame is null.
    queue.size++;
}

void dequeue(Queue &queue) // Remove an frame from the queue. If the queue is empty, do nothing and return. Also free the frame.
{
    if (queueIsEmpty(queue))
    {
        return;
    }
    freeFrame(queue.ring[(queue.head + queue.size + 1) % queue.capacity]);
    queue.size--;
}

const EthernetFrame *queueFront(const Queue &queue) // Return a pointer to the front or back of the queue.
{
    if (queueIsEmpty(queue))
    {
        return nullptr;
    }
    return queue.ring[queue.head];
}

const EthernetFrame *queueBack(const Queue &queue)
{
    if (queueIsEmpty(queue))
    {
        return nullptr;
    }
    return queue.ring[(queue.head + queue.size) % queue.capacity];
}

bool queueIsEmpty(const Queue &queue) // Check whether the given queue is empty. If so, return true. Otherwise, return false.
{
    if (queue.size == 0)
    {
        return true;
    }
    return false;
}

void freeQueue(Queue &queue) // free all the frames it contains (if any)
{
    if(queueIsEmpty(queue)){
        return;
    }
    queueResizeRing(queue,0);
}
