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

#include "LIFOScheduler.h"

Define_Module(LIFOScheduler)

void LIFOScheduler::initialize(){
    Scheduler::initialize();
    queueSize = par("queueSize");
}

bool LIFOScheduler::receivePacket(Packet* packet){
    bool res = false;

    if(canReceive()){
        queue.push_front(packet);
        res = true;
    }

    return res;
}

Packet* LIFOScheduler::getPacketToSend(){
    Packet* packet = queue.front();

    queue.pop_front();

    return packet;
}

bool LIFOScheduler::hasWaitingPacket(){
    return !queue.empty();
}

bool LIFOScheduler::canReceive(){
    return queue.size() < queueSize;
}
