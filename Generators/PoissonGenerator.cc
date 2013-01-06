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

class PoissonGenerator : public cSimpleModule
{
    private:
        double lambda;
        int rnb;
        double delay;
    protected:
        cDoubleHistogram delaysHistogram;
        virtual cMessage *generatePacket();
        virtual void sendMessage();
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

Define_Module(PoissonGenerator);

void PoissonGenerator::initialize(){
    lambda = par("lambda").doubleValue();
    rnb = par("rnb").longValue();

    delaysHistogram.setName("delays");

    WATCH(delay);

    sendMessage();
}

void PoissonGenerator::handleMessage(cMessage *msg){
    delete msg;
    sendMessage();
}

void PoissonGenerator::sendMessage(){

    std::stringstream ss;

    simtime_t delay = poisson(lambda,rnb);
    ss << "Self "<< delay;

    std::string s = ss.str();
    cMessage *sel = new cMessage(s.c_str());
    cMessage *packet = generatePacket();
    sendDelayed(packet, delay, "out");
    scheduleAt(simTime()+delay, sel);
    delaysHistogram.collect(delay);

}

cMessage *PoissonGenerator::generatePacket(){

    char msgname[30];
    int src = 1;
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

