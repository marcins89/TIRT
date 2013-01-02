#include "DoubleTokenBucket.h"

Define_Module(DoubleTokenBucket);

DoubleTokenBucket::DoubleTokenBucket() {
    token = serviceTimeMsg = NULL;
}

DoubleTokenBucket::~DoubleTokenBucket() {
    delete token;
    delete serviceTimeMsg;
    cancelAndDelete(token);
    cancelAndDelete(serviceTimeMsg);
}

void DoubleTokenBucket::initialize() {
    queue.setName("queue");

    token = new cMessage("token");
    serviceTimeMsg = new cMessage("service time");

    tokenMax = par("tokenCount");
    tokenCount = tokenMax;
    tokenArrivalInterval = par("tokenArrivalInterval");
    serviceTime = par("serviceTime");

    scheduleAt(simTime(), token);
    scheduleAt(simTime(), serviceTimeMsg);
}

void DoubleTokenBucket::handleMessage(cMessage *msg) {
    if (msg == token) {
        if (tokenCount < tokenMax) {
            tokenCount++;
        }
        scheduleAt(simTime() + tokenArrivalInterval, token);
    } else if (msg == serviceTimeMsg) {
        if (queue.length() > 0) {
            msgServiced = (cMessage *) queue.pop();
            EV << "Sending msg" << endl;
            send(msgServiced, "out");
        } else {
            bubble("queue empty");
        }
        scheduleAt(simTime() + serviceTime, serviceTimeMsg);
    } else if (tokenCount > 0) {
        if (queue.length() < getBuffer()) {
            EV << "Message queued" << endl;
            queue.insert(msg);
        } else {
            bubble("queue full - message leaked");
        }
        tokenCount--;
    } else {
        bubble("No available tokens!");
    }
}

int DoubleTokenBucket::getBuffer() {
    return par("buffer");
}
