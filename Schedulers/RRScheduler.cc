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

#include "RRScheduler.h"

Define_Module(RRScheduler)

void RRScheduler::initialize(){
    Scheduler::initialize();
    queueOutHistogram.setName("queuesOut");
    queueInHistogram.setName("queuesIn");
}

bool RRScheduler::receivePacket(Packet* packet){
    int source = packet->getSrc();

        bool find = false;
        int num = -1;
        for(list<int>::iterator iter = address.begin(); !find && iter != address.end(); ++iter){
            num++;
            find = (*iter) == source;
        }
        queueInHistogram.collect(source);

        if(find){
            list<list<Packet*>* >::iterator iter = queues.begin();
            while(num-- > 0){
                iter++;
            }

            (*iter)->push_back(packet);
            queuesCount++;
        }else{
            address.push_back(source);
            queues.push_back(new list<Packet*>());
            queues.back()->push_back(packet);
            queuesCount++;
        }

        return true;
}

bool RRScheduler::hasWaitingPacket(){
    return false;
}

Packet* RRScheduler::getPacketToSend(){
    Packet* packet;

    if(queuesCount > 0){
        list<list<Packet*>*>::iterator iter = queues.begin();
        ++currentQueue;

        if(currentQueue >= queues.size()){
            currentQueue = 0;
        }

        advance(iter,currentQueue);

        if((*iter)->empty()){
            iter = queues.begin();

            while((*iter) ->empty()){
                iter++;
                currentQueue++;
            }
        }

        packet = (*iter)->front();
        (*iter)->pop_front();
        queuesCount--;

    }

    queueOutHistogram.collect(currentQueue);

    return packet;
}
