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

#include "OnOffGenerator.h"

Define_Module(OnOffGenerator);

OnOffGenerator::OnOffGenerator()
{
    msgGL = NULL;
    sessionCnt = 0;
}

OnOffGenerator::~OnOffGenerator()
{
    cancelAndDelete(msgGL);
}

void OnOffGenerator::initialize()
{
    OnOrOff = par("OnOff");
    lastGeneration = simTime();
    isChangesHistogram.setName("Time of generation");
    isChangesVector.setName("Changes vector");
    isChangesVector.setInterpolationMode(cOutVector::NONE);

    if(OnOrOff==1){
        msgGL = generateMessage();
        scheduleAt(simTime(), msgGL);
        isChangesHistogram.collect(lastGeneration);
    };
}

void OnOffGenerator::finish()
{
    isChangesHistogram.recordAs("Time of generation out");
}


void OnOffGenerator::handleMessage(cMessage *msg)
{

    simtime_t d = simTime() - lastGeneration;
    isChangesHistogram.collect(d);
    lastGeneration = simTime();

    //Zmieniamy wartosc po przekroczeniu okreslonego progu
   /* int OnOrOff = par("OnOff");*/
    int lowerB = par("lowerBound");
    int upperB = par("upperBound");
    int chgVal = par("changeValue");
    int result = intuniform(lowerB,upperB);

    if ((result >= chgVal) && OnOrOff == 0){
        OnOrOff = 1;
        isChangesVector.recordWithTimestamp(simTime(),0);
        isChangesVector.recordWithTimestamp(simTime(),1);
    }
    else if((result <= chgVal) && OnOrOff == 1){
        OnOrOff = 0;
        isChangesVector.recordWithTimestamp(simTime(),1);
        isChangesVector.recordWithTimestamp(simTime(),0);
        EV << "Blokada wysylki! Res: "<< result << endl;
    }
    else {
        isChangesVector.recordWithTimestamp(simTime(),OnOrOff);
    };
/*
    while (OnOrOff == 0){
        //Chcemy chwile poczekac przed nastepna proba wysylki
        //Sleep(500);
        result = intuniform(lowerB,upperB);
        EV << "Proba odblokowania wysylki! Res: "<< result << endl;
        if ((result >= chgVal) && OnOrOff == 0){
            OnOrOff = 1;
        };
    };
*/
    simtime_t delay = par("delayTime");

    if(OnOrOff == 1){

        ASSERT(msg==msgGL);

        Packet *ttmsg = generateMessage();

        send(ttmsg, "out");

        scheduleAt(simTime()+delay, msgGL);

        sessionCnt++;
    }

    else{
        EV << "Wysylka zablokowana!"<< result << endl;
        scheduleAt(simTime()+delay, msgGL);
    }
}

Packet *OnOffGenerator::generateMessage()
{

    char msgname[30];
    int src = 0;
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
