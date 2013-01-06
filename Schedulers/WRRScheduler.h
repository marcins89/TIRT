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

#ifndef WRRSCHEDULER_H_
#define WRRSCHEDULER_H_

using namespace std;
#include "Scheduler.h"

class WRRScheduler: public Scheduler {
protected:
    int32_t queueSize;
    int32_t queuesNums;
    int32_t currentQueue;

    cDoubleHistogram queueOutHistogram;
    cDoubleHistogram queueInHistogram;

    cPacketQueue** queues;
    double* weights;

    virtual void initialize();
    virtual void finish();
    virtual bool receivePacket(Packet* packet);
    virtual bool  hasWaitingPacket();
    virtual Packet* getPacketToSend();

    bool canReceive(int32_t queueIndex);
    void nextQueue();
};

#endif /* WRRSCHEDULER_H_ */
