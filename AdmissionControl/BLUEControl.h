/*
 * BLUEControl.h
 *
 *  Created on: 03-12-2012
 *      Author: Wilku
 */

#ifndef BLUECONTROL_H_
#define BLUECONTROL_H_

#include <omnetpp.h>
#include <Packet_m.h>
#include "AdmControl.h"

class BLUEControl : public AdmControl {

    protected:
        double propability;
        double propDiff;
        int bufforSize;
        double chance;

        cOutVector propabilityVector;

        virtual void initialize();
        virtual bool packetAccept(Packet* packet);

};

#endif /* BLUECONTROL_H_ */
