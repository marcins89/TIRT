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

#ifndef RRSCHEDULER_H_
#define RRSCHEDULER_H_

using namespace std;
#include "Scheduler.h"
#include "list"

class RRScheduler: public Scheduler {
    protected:
        list<int> address;
        list<list<Packet*>*> queues;

        cDoubleHistogram queueOutHistogram;
        cDoubleHistogram queueInHistogram;

        int queuesCount;
        int queueSize;

        int currentQueue;
        virtual void initialize();
        virtual bool receivePacket(Packet* packet);
        virtual bool  hasWaitingPacket();
        virtual Packet* getPacketToSend();
};

#endif /* RRSCHEDULER_H_ */
