#ifndef SIZECONTROL_H_
#define SIZECONTROL_H_

#include <omnetpp.h>
#include <Packet_m.h>
#include "AdmControl.h"

class SizeControl : public AdmControl {

    protected:
        uint32_t minSize;
        uint32_t maxSize;

        cOutVector sizeVector;

        virtual void initialize();
        virtual bool packetAccept(Packet* packet);

};

#endif
