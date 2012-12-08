//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 


#include <string.h>
#include <omnetpp.h>
#include "Packet_m.h"

class MMPPGenerator : public cSimpleModule
{
    private:
        double lambda;
        int rnb;
        double delay;
        simtime_t delayDef;
    protected:
        virtual cMessage *generatePacket();
        virtual void sendMessage();
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

Define_Module(MMPPGenerator);

void MMPPGenerator::initialize(){
    lambda = par("lambda").doubleValue();
    rnb = par("rnb").longValue();
    delayDef = 0.5;

    WATCH(delay);

    sendMessage();
}

void MMPPGenerator::handleMessage(cMessage *msg){
    delete msg;
    sendMessage();
}

void MMPPGenerator::sendMessage(){

    std::stringstream ss;

    simtime_t delay = poisson(lambda,rnb);
    delay = std::max(delay,delayDef);
    lambda = delay.dbl();
    ss << "Self "<< delay;

    std::string s = ss.str();
    cMessage *sel = new cMessage(s.c_str());
    cMessage *packet = generatePacket();
    sendDelayed(packet, delay, "out");
    scheduleAt(simTime()+delay, sel);


}

cMessage *MMPPGenerator::generatePacket(){
    char msgname[30];
    int src = 2;
    int dest = rand()%5;
    int Class = rand()%6;
    int SessionId = 1;
    int PacketId = 1;
    int Payload = 1;
    int ByteLength = rand()%200000;
    sprintf(msgname, "packet-from-%d-to-%d", src, dest);

    Packet *packet = new Packet(msgname);

    packet->setSrc(src);
    packet->setDst(dest);
    packet->setSessionID(SessionId);
    packet->setPacketID(PacketId);
    packet->setPriority(Class);
    packet->setPayload(Payload);
    packet->setByteLength(ByteLength);
    return packet;
}

