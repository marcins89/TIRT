#include <ctime>
#include <cstdlib>
#include "HierarchicalTokenBucket.h"

Define_Module(HierarchicalTokenBucket);

HierarchicalTokenBucket::HierarchicalTokenBucket() {
    msgServiced = endServiceMsg = NULL;
}

HierarchicalTokenBucket::~HierarchicalTokenBucket() {
    delete msgServiced;
    cancelAndDelete(endServiceMsg);
}

void HierarchicalTokenBucket::initialize() {
    endServiceMsg = new cMessage("end-service");

    token1 = new cMessage("token1");
    token2 = new cMessage("token2");
    token3 = new cMessage("token3");
    token4 = new cMessage("token4");

    srand(time(0));

    tokenMax = par("tokenCount");
    tokenCount1 = tokenCount2 = tokenCount3 = tokenCount4 = tokenMax;
    tokenArrivalInterval1 = par("tokenArrivalInterval1");
    tokenArrivalInterval2 = par("tokenArrivalInterval2");
    tokenArrivalInterval3 = par("tokenArrivalInterval3");
    tokenArrivalInterval4 = par("tokenArrivalInterval4");

    scheduleAt(simTime(), token1);
    scheduleAt(simTime(), token2);
    scheduleAt(simTime(), token3);
    scheduleAt(simTime(), token4);
}

void HierarchicalTokenBucket::handleMessage(cMessage *msg) {
    if (msg == token1) {
        if (tokenCount1 < tokenMax) {
            tokenCount1++;
        }
        scheduleAt(simTime() + tokenArrivalInterval1, token1);
    } else if (msg == token2) {
        if (tokenCount2 < tokenMax) {
            tokenCount2++;
        }
        scheduleAt(simTime() + tokenArrivalInterval2, token2);
    } else if (msg == token3) {
        if (tokenCount3 < tokenMax) {
            tokenCount3++;
        }
        scheduleAt(simTime() + tokenArrivalInterval3, token3);
    } else if (msg == token4) {
        if (tokenCount4 < tokenMax) {
            tokenCount4++;
        }
        scheduleAt(simTime() + tokenArrivalInterval4, token4);
    } else if (msg->getSchedulingPriority() == 0) {
        generatePriority(msg);
    } else {
        sendAccordingToPriority(msg);
    }

//    else  {
//        if (tokenCount > 0) {
//            EV << "Completed service of " << msg->getName() << endl;
//            send(msg, "out");
//            tokenCount--;
//        } else {
//            bubble("No available tokens!");
//        }
//    }
}

void HierarchicalTokenBucket::generatePriority(cMessage *msg) {
    int r = (rand() % 12) + 1; // losuje liczbe z przedzialu [1, 12]
    msg->setSchedulingPriority(r);
    scheduleAt(simTime(), msg);
}

void HierarchicalTokenBucket::sendAccordingToPriority(cMessage *msg) {
    int priority = msg->getSchedulingPriority();
    if (priority < 4) {
        if (tokenCount1 > 0) {
            EV << "Completed service of " << msg->getName() << " with prio: "
                      << priority << endl;
            send(msg, "out");
            tokenCount1--;
        } else {
            bubble("No available tokens for class 1");
        }
    } else if (priority >= 4 && priority < 7) {
        if (tokenCount2 > 0) {
            EV << "Completed service of " << msg->getName() << " with prio: "
                      << priority << endl;
            send(msg, "out");
            tokenCount2--;
        } else {
            bubble("No available tokens for class 2");
        }
    } else if (priority >= 7 && priority < 10) {
        if (tokenCount3 > 0) {
            EV << "Completed service of " << msg->getName() << " with prio: "
                      << priority << endl;
            send(msg, "out");
            tokenCount3--;
        } else {
            bubble("No available tokens for class 3");
        }
    } else if (priority >= 10) {
        if (tokenCount4 > 0) {
            EV << "Completed service of " << msg->getName() << " with prio: "
                      << priority << endl;
            send(msg, "out");
            tokenCount4--;
        } else {
            bubble("No available tokens for class 4");
        }
    }
}
