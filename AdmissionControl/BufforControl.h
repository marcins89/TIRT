#ifndef BUFFORCONTROL_H_
#define BUFFORCONTROL_H_

#include <omnetpp.h>
#include <Packet_m.h>
#include "AdmControl.h"

class BufforControl : public AdmControl {

    int bufforSize;

    cOutVector sizeVector;

    virtual void initialize();
    virtual bool packetAccept(Packet* packet);

};

#endif
