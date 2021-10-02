//
// Queue.h
//

#ifndef LAB3_SKELETON_QUEUE_H
#define LAB3_SKELETON_QUEUE_H

struct EthernetFrame;

struct Queue {
    EthernetFrame * *ring = nullptr;
    unsigned int head = 0;
    unsigned int size = 0;
    unsigned int capacity = 0;
};

// TODO: task 3: queue operations

void queueResizeRing(Queue &queue, unsigned int newCapacity);

void enqueue(Queue &queue, EthernetFrame *frame);

void dequeue(Queue &queue);

const EthernetFrame *queueFront(const Queue &queue);

const EthernetFrame *queueBack(const Queue &queue);

bool queueIsEmpty(const Queue &queue);

void freeQueue(Queue &queue);

#endif //LAB3_SKELETON_QUEUE_H
