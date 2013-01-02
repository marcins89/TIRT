#include "TokenBucket.h"

Define_Module(TokenBucket);

TokenBucket::TokenBucket() {
    msgServiced = endServiceMsg = NULL;
}

TokenBucket::~TokenBucket() {
    delete msgServiced;
    cancelAndDelete(endServiceMsg);
}

void TokenBucket::initialize() {
    endServiceMsg = new cMessage("end-service");

    token = new cMessage("token");

    queueingTimeSignal = registerSignal("queueingTime");

    tokenMax = par("tokenCount");
    tokenCount = tokenMax;
    tokenArrivalInterval = par("tokenArrivalInterval");

    scheduleAt(simTime(), token);
}

int TokenBucket::getTokenArrivalInterval() {
    return par("buffer");
}

void TokenBucket::handleMessage(cMessage *msg) {
    if (msg == token) {
        if ( tokenCount < tokenMax ) {
            tokenCount++;
        }
        scheduleAt(simTime() + tokenArrivalInterval, token);
    } else  {
        if (tokenCount > 0) {
            EV << "Completed service of " << msg->getName() << endl;
            send(msg, "out");
            tokenCount--;
        } else {
            bubble("No available tokens!");
        }
    }
}

simtime_t TokenBucket::startService(cMessage *msg) {
    EV << "Starting service of " << msg->getName() << endl;
    return par("serviceTime");
}
