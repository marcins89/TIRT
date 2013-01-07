#ifndef ADMCONTROL_H_
#define ADMCONTROL_H_

#include <omnetpp.h>
#include <Packet_m.h>

class AdmControl : public cSimpleModule {

    private:
        // state
        simtime_t lastArrival;
        simtime_t delay;

        // statistics
        cDoubleHistogram iaTimeHistogram;
        cLongHistogram isArrivalsHistogram;
        cLongHistogram isOutputsHistogram;
        cLongHistogram isDiscardedHistogram;
        cOutVector arrivalsVector;

        //counts
        int wentIn;
        int wentOut;

    protected:

        virtual void initialize();
        virtual void handleMessage(cMessage* msg);
        virtual void finish();
        virtual bool packetAccept(Packet* packet) = 0;

        //counts
        int processing;

};

#endif /* ADMCONTROL_H_ */
