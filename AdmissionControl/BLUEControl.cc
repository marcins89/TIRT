#include <omnetpp.h>
#include <Packet_m.h>
#include "BLUEControl.h"

Define_Module(BLUEControl)

void BLUEControl::initialize()
{
        AdmControl::initialize();

        propability = par("propability");
        propDiff = par("propDiff");
        bufforSize = par("bufforSize");

        chance = 0;

        WATCH(propability);
        WATCH(chance);

}

bool BLUEControl::packetAccept(Packet* pck)
{

    chance = rand() / double(RAND_MAX);

    //losujemy szanse na odrzucenie pakietu.
    //sprawdzamy rowniez rozmiar bufora - jak nie jest zapelniony, to po prostu przepychamy pakiet
    if(processing > bufforSize) {
        //jak jest wieksza od zadanego P, to odrzucamy i zwiekszamy szanse na odrzucenie
        if(chance >= propability){
            if(propability-propDiff <= 1){
                propability = propability + propDiff;
                EV << "Increased propability to " << propability << endl;
            }
            return false;
        }
        //pakiet akceptujemy i zmniejszamy szanse na odrzucenie
        else{
            if(propability-propDiff > propDiff){
                propability = propability - propDiff;
                EV << "Decrased propability to " << propability << endl;
            }
            return true;
        }
    }
    //forwardujemy
    else {
        return true;
    }
}
