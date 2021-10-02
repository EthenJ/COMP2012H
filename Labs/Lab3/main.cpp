#include <iostream>
#include <sstream>
#include <iomanip>

#include "Queue.h"
#include "EthernetFrame.h"

EthernetFrame *generateFrame(int seed) {
    std::stringstream src, dst;
    src << std::hex << std::setfill('0') << std::setw(2);
    dst << std::hex << std::setfill('0') << std::setw(2);
    for (int i = 1; i <= 6; ++i) {
        src << (((seed + 7) * 17 * i) & 255);
        dst << (((seed + 29) * 13 * i) & 255);
        if (i < 6) {
            src << ":";
            dst << ":";
        }
    }
    return createFrame(src.str(), dst.str(), to_string(seed), static_cast<EtherType>(seed % 3));
}

void printFrame(const EthernetFrame *frame) {
    if (frame == nullptr) {
        std::cout << "nullptr" << std::endl;
        return;
    }

    switch (frame->type) {
        case IPV4:
            std::cout << "IPv4, ";
            break;
        case IPV6:
            std::cout << "IPv6, ";
            break;
        case ARP:
            std::cout << "ARP, ";
            break;
    }
    std::cout << frame->source << " > " << frame->destination << ": ";
    std::cout << frame->payload << std::endl;
}

void printQueue(const Queue &queue) {
    if (!queueIsEmpty(queue)) {
        std::cout << "front: ";
        printFrame(queueFront(queue));
        std::cout << "back: ";
        printFrame(queueBack(queue));
    } else {
        std::cout << "empty" << std::endl;
    }
}

void task1Tests() {
    EthernetFrame frame1, frame2;

    std::cout << "Testing task 1..." << std::endl;

    initFrame(frame1, "ec:98:57:12:34:56", "ff:ff:ff:ff:ff:ff", "Request who-has 10.0.0.1 tell 10.0.2.1", ARP);
    printFrame(&frame1);

    initFrame(&frame2, "12:c4:87:d1:ca:39", "ff:ff:ff:ff:ff:ff", "Reply 10.0.0.1 is-at 12:c4:87:d1:ca:39", ARP);
    printFrame(&frame2);

    initFrame(nullptr, "00:00:00:00:00:00", "ff:ff:ff:ff:ff:ff", "Testing nullptr", IPV4);

    swapFrames(frame1, frame2);
    printFrame(&frame1);
    printFrame(&frame2);

    swapFrames(&frame1, &frame2);
    printFrame(&frame1);
    printFrame(&frame2);

    swapFrames(nullptr, &frame2);
    printFrame(&frame2);

    swapFrames(&frame1, nullptr);
    printFrame(&frame1);

    std::cout << "Task 1 tests complete." << std::endl;
}

void task2Tests() {
    std::cout << "Testing task 2..." << std::endl;

    EthernetFrame *frame = createFrame("cc:12:92:34:de:2f", "12:34:56:78:90:ab", "Dynamically allocated", IPV4);

    printFrame(frame);

    freeFrame(frame);
    freeFrame(nullptr);

    std::cout << "Task 2 tests complete." << std::endl;
}

void task3Tests() {
    std::cout << "Testing task 3..." << std::endl;

    Queue queue;
    std::cout << std::boolalpha;
    printQueue(queue);

    for (int i = 0; i < 16; i += 2) {
        enqueue(queue, generateFrame(i));
        enqueue(queue, generateFrame(i + 1));
        dequeue(queue);
        printQueue(queue);
    }

    for (int i = 0; i < 8; ++i) {
        dequeue(queue);
        printQueue(queue);
    }

    for (int i = 0; i < 16; ++i) {
        enqueue(queue, generateFrame(i + 100));
        printQueue(queue);
    }

    enqueue(queue, nullptr);
    enqueue(queue, nullptr);

    for (int i = 0; i < 16; ++i) {
        dequeue(queue);
        dequeue(queue);
        enqueue(queue, generateFrame(i + 200));
        printQueue(queue);
    }

    while (!queueIsEmpty(queue)) {
        dequeue(queue);
        printQueue(queue);
    }

    for (int i = 0; i < 64; ++i) {
        enqueue(queue, generateFrame(i + 300));
    }

    freeQueue(queue);

    std::cout << "Task 3 tests complete." << std::endl;
}

int main() {
    task1Tests();
    task2Tests();
    task3Tests();
    return 0;
}
