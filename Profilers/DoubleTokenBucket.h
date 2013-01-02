#include <omnetpp.h>

class DoubleTokenBucket: public cSimpleModule {
protected:
    cQueue queue;

    cMessage *token;
    cMessage *serviceTimeMsg;
    cMessage *msgServiced;

    int tokenCount;
    int tokenMax;
    simtime_t tokenArrivalInterval;
    simtime_t serviceTime;

public:
    DoubleTokenBucket();
    ~DoubleTokenBucket();

protected:
    void initialize();
    void handleMessage(cMessage *msg);

    int getBuffer();
};

