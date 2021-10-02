//
// EthernetFrame.cpp
//

#include "EthernetFrame.h"

// TODO: task 1: initialize & swap EthernetFrame

void initFrame(EthernetFrame &frame, const string &source, const string &destination,
               const string &payload, EtherType type) // Initialize a given reference or pointer to EthernetFrame with given contents.
{
    frame.type = type;
    frame.source = source;
    frame.destination = destination;
    frame.payload = payload;
}

void initFrame(EthernetFrame *frame, const string &source, const string &destination,
               const string &payload, EtherType type) // Initialize a given reference or pointer to EthernetFrame with given contents.
{
    if (frame == nullptr) // If the given pointer is null in the second function, do nothing and return.
    {
        return;
    }
    (*frame).type = type;
    (*frame).source = source;
    (*frame).destination = destination;
    (*frame).payload = payload;
}

void swapFrames(EthernetFrame &frame1, EthernetFrame &frame2) // Swap the contents of two EthernetFrame.
{
    EthernetFrame temp;
    temp = frame1;
    frame1 = frame2;
    frame2 = temp;
}

void swapFrames(EthernetFrame *frame1, EthernetFrame *frame2) // Swap the contents of two EthernetFrame.
{
    if (frame1 == nullptr || frame2 == nullptr || frame1 == frame2) // do nothing and return if (1) one of the given pointers is null or (2) two pointers are identical.
    {
        return;
    }
    EthernetFrame temp;
    temp = *frame1;
    *frame1 = *frame2;
    *frame2 = temp;
}

// TODO: task 2: create & free EthernetFrame

EthernetFrame *createFrame(const string &source, const string &destination, const string &payload, EtherType type) // Dynamically allocate an EthernetFrame with given contents and return a pointer to it.
{
    EthernetFrame *frame = new EthernetFrame;
    initFrame(*frame, source, destination, payload, type);
    return frame;
}

void freeFrame(EthernetFrame *frame) // Delete the dynamically allocated EthernetFrame.
{
    delete frame;
    frame = nullptr;
}
