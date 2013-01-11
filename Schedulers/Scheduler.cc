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

#include "Scheduler.h"

void Scheduler::initialize(){
    event = new cMessage("event");
    isArrivalsHistogram.setName("Sources from which packets arrived");
}

void Scheduler::finish(){
    isArrivalsHistogram.recordAs("Arrivals sources out");
}

void Scheduler::handleMessage(cMessage* msg){
    EV << "Handle message";
    simtime_t delay = par("delay");

    if(msg!=event){
        Packet* packet = check_and_cast<Packet*>(msg);
        isArrivalsHistogram.collect(packet->getSrc());

        bool que = receivePacket(packet);

        if(que){
            if(!event->isScheduled()){
                scheduleAt(simTime() + delay, event);
            }
        }else{
            delete packet;
        }
    }else{
        EV << "else\n";
        Packet* packet = getPacketToSend();

        if(packet!=NULL){
            send(packet, "out");
        }

        if(hasWaitingPacket()){
            EV << "hasWaitingPacket nie\n";
            scheduleAt(simTime() + delay, event);
            EV << "schedule\n";
        }

    }
}
