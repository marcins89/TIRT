#include <omnetpp.h>

class HierarchicalTokenBucket: public cSimpleModule
{
protected:
    cMessage *msgServiced;
    cMessage *endServiceMsg;
    cMessage *token1;
    cMessage *token2;
    cMessage *token3;
    cMessage *token4;

    int tokenCount1;
    int tokenCount2;
    int tokenCount3;
    int tokenCount4;

    int tokenMax;
    simtime_t tokenArrivalInterval1;
    simtime_t tokenArrivalInterval2;
    simtime_t tokenArrivalInterval3;
    simtime_t tokenArrivalInterval4;

public:
    HierarchicalTokenBucket();
    ~HierarchicalTokenBucket();

protected:
    void initialize();
    void handleMessage(cMessage *msg);

    void arrival(cMessage *msg) {}
    int getTokenArrivalInterval();
    void generatePriority(cMessage *msg);
    void sendAccordingToPriority(cMessage *msg);
};


