//
// EthernetFrame.h
//

#ifndef LAB3_SKELETON_ETHERNETFRAME_H
#define LAB3_SKELETON_ETHERNETFRAME_H

#include <string>

using namespace std;

enum EtherType {
    IPV4,
    IPV6,
    ARP
};

struct EthernetFrame {
    EtherType type;
    string source;
    string destination;
    string payload;
};

// TODO: task 1: initialize & swap EthernetFrame

void initFrame(EthernetFrame &frame, const string &source, const string &destination,
               const string &payload, EtherType type);

void initFrame(EthernetFrame *frame, const string &source, const string &destination,
               const string &payload, EtherType type);

void swapFrames(EthernetFrame &frame1, EthernetFrame &frame2);

void swapFrames(EthernetFrame *frame1, EthernetFrame *frame2);

// TODO: task 2: create & free EthernetFrame

EthernetFrame *createFrame(const string &source, const string &destination, const string &payload, EtherType type);

void freeFrame(EthernetFrame *frame);

#endif //LAB3_SKELETON_ETHERNETFRAME_H
