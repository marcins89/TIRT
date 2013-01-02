#include <omnetpp.h>

class TokenBucket: public cSimpleModule
{
protected:
    cMessage *msgServiced;
    cMessage *endServiceMsg;
    cMessage *token;
    simsignal_t queueingTimeSignal;

    int tokenCount;
    int tokenMax;
    simtime_t tokenArrivalInterval;

public:
    TokenBucket();
    ~TokenBucket();

protected:
    void initialize();
    void handleMessage(cMessage *msg);

    void arrival(cMessage *msg) {}
    simtime_t startService(cMessage *msg);
    int getTokenArrivalInterval();
};

