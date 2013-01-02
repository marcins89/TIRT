#include <omnetpp.h>

class LeakyBucket: public cSimpleModule
{
protected:
    cMessage *msgServiceTime;
    cMessage *msgServiced;
    cQueue queue;
    simtime_t serviceTime;
public:
    LeakyBucket();
    ~LeakyBucket();

protected:
    void initialize();
    void handleMessage(cMessage *msg);

    int getBuffer();
};

