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

#include "WRRScheduler.h"

Define_Module(WRRScheduler)

void WRRScheduler::initialize(){
    Scheduler::initialize();

    queueOutHistogram.setName("queuesOut");
    queueInHistogram.setName("queuesIn");

    queueSize = par("queueSize");
    queuesNums = par("queuesNums");

    currentQueue = 0;

    queues = new cPacketQueue*[queuesNums];

    weights = new double[queuesNums];

    for(int32_t i=0; i<queuesNums;i++){
        cPacketQueue* queue = new cPacketQueue();

        queue->setTakeOwnership(true);

        queues[i] = queue;
        weights[i] = i;
    }
}

void WRRScheduler::finish(){
    queueOutHistogram.recordAs("out hist");
    queueInHistogram.recordAs("in hist");
}

bool WRRScheduler::receivePacket(Packet* packet){
    int32_t pr = min(max(packet->getPriority(),0),queuesNums-1);
    bool res = false;

    if(canReceive(pr)){
        queues[pr]->insert(packet);
        res = true;
        queueInHistogram.collect(pr);
    }



    return res;
}

bool WRRScheduler::hasWaitingPacket(){
    bool res = false;

    for(int32_t i = 0; i < queuesNums;i++ ){
        if(!queues[i]->empty()){
            res = true;
            break;
        }
    }

    return res;
}

Packet* WRRScheduler::getPacketToSend(){
    while(queues[currentQueue]->empty() || weights[currentQueue] < 1){
        weights[currentQueue] = currentQueue;
        nextQueue();
    }

    weights[currentQueue] -= 1.0;

    queueOutHistogram.collect(currentQueue);

    return check_and_cast<Packet*>(queues[currentQueue]->pop());
}

bool WRRScheduler::canReceive(int32_t queueIndex){
    return queues[queueIndex]->getLength() < queueSize;
}

void WRRScheduler::nextQueue(){
    if(++currentQueue==queuesNums){
        currentQueue = 0;

        for(int32_t i = 0; i < queuesNums; i++){
            weights[i] = i;
        }
    }
}

