#include "AdmControl.h"

void AdmControl::initialize()
{
    wentIn = 0;
    wentOut = 0;
    processing = 0;
    lastArrival = SIMTIME_ZERO;
    delay = par("delay");

    WATCH(wentIn);
    WATCH(wentOut);
    WATCH(processing);

    iaTimeHistogram.setName("Time packets went through");
    arrivalsVector.setName("Arrivals AC");
    arrivalsVector.setInterpolationMode(cOutVector::NONE);

}

void AdmControl::handleMessage(cMessage* msg)
{

    wentIn++;
    lastArrival = std::max(lastArrival, simTime());
    EV << "Processing no. " << processing << endl;

    //odbieramy swoja opozniona wiadomosc i dopiero ja procesujemy
    if(msg->isSelfMessage()){

        EV << "Processing " << msg->getName() << endl;

        Packet* pck = check_and_cast<Packet*>(msg);

        //sprawdzenie akceptacji pakietu
        if(packetAccept(pck)){

            //zebranie danych
            simtime_t d = simTime() - lastArrival;
            iaTimeHistogram.collect(d);
            arrivalsVector.record(1);

            //pobranie bramy wyjsciowej i wyslanie przez nia pakietu
            cGate* out = gate("out");
            send(pck, out);

            EV << "Forwarded " << pck->getName() << endl;

            processing--;
            //zwiekszenie ilosci pakietow jakie wyszly
            wentOut++;

        }
        else {
            EV << "Blocked " << pck->getName() << endl;
            processing--;
            delete pck;
        }
    }
    else {
        //wysylamy sobie wiadomosc, bo w koncu przetworzenie zajmuje chwile
        EV << "Delayed " << msg->getName() << " to " << (simTime()+delay) << endl;
        //zwiekszamy ilosc obecnie przetwarzanych (na potrzeby bufora)
        processing++;
        scheduleAt(simTime()+delay, msg);
    }

}

void AdmControl::finish()
{

}
