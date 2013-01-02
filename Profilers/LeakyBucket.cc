#include "LeakyBucket.h"

Define_Module(LeakyBucket);

LeakyBucket::LeakyBucket() {
    msgServiceTime = msgServiced = NULL;
}

LeakyBucket::~LeakyBucket() {
    delete msgServiceTime;
    cancelAndDelete(msgServiceTime);
}

void LeakyBucket::initialize() {
    queue.setName("queue");
    msgServiceTime = new cMessage("time interval");
    serviceTime = par("serviceTime");

    scheduleAt(simTime(), msgServiceTime);
}

int LeakyBucket::getBuffer() {
    return par("buffer");
}

void LeakyBucket::handleMessage(cMessage *msg) {
    if (msg == msgServiceTime) {
        if (queue.length() > 0) {
            msgServiced = (cMessage *) queue.pop();
            EV << "Sending msg" << endl;
            send(msgServiced, "out");
        } else {
            bubble("queue empty");
        }
        scheduleAt(simTime() + serviceTime, msg);
    } else if (queue.length() < getBuffer()) {
        EV << "Message queued" << endl;
        queue.insert(msg);
    } else {
        bubble("queue full - message leaked");
    }
}
