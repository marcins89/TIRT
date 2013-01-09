#include <omnetpp.h>
#include <Packet_m.h>
#include "BufforControl.h"

Define_Module(BufforControl);

void BufforControl::initialize()
{
        AdmControl::initialize();

        bufforSize = par("bufforSize");

        sizeVector.setName("Buffor size vector");
        sizeVector.setInterpolationMode(cOutVector::NONE);

}

bool BufforControl::packetAccept(Packet* pck)
{
    sizeVector.recordWithTimestamp(simTime(),processing);

        if(processing > bufforSize)
            return false;
        else
            return true;
}
