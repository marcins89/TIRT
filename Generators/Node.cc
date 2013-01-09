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

#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    lastArrival = simTime();
    iaTimeHistogram.setName("interarrival times");
    isArrivalsHistogram.setName("Sources from which packets arrived");
    arrivalsVector.setName("arrivals");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);
}

void Node::handleMessage(cMessage *msg)
{

    Packet* pck = check_and_cast<Packet*>(msg);
    isArrivalsHistogram.collect(pck->getSrc());

    simtime_t d = simTime() - lastArrival;
    EV << "Received " << msg->getName() << endl;
    delete msg;

    iaTimeHistogram.collect(d);
    arrivalsVector.record(1);

    lastArrival = simTime();
}

void Node::finish()
{
    //recordStatistic(&iaTimeHistogram);
    iaTimeHistogram.recordAs("interarrival times out");
    isArrivalsHistogram.recordAs("Sources from which packets arrived out");
}
