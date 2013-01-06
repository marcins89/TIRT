/*
 * Node_s.h
 *
 *      Author: Wilku
 */

#ifndef ONOFFGENERATOR_H_
#define ONOFFGENERATOR_H_

#include <omnetpp.h>
#include <Packet_m.h>

class OnOffGenerator : public cSimpleModule
{

  private:
    Packet *msgGL;
    int sessionCnt;
    cDoubleHistogram isChangesHistogram;
    cOutVector isChangesVector;
    simtime_t lastGeneration;
    int OnOrOff;

  public:
    OnOffGenerator();
    virtual ~OnOffGenerator();

  protected:
    virtual Packet *generateMessage();
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

#endif /* NODE_S_H_ */
