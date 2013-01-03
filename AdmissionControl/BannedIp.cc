#include <omnetpp.h>
#include <Packet_m.h>
#include "BannedIp.h"

using namespace std;

Define_Module(BannedIp);

void BannedIp::initialize()
{
        AdmControl::initialize();

        const char* ids = par("restrictedAcces");
        vector<int> j = cStringTokenizer(ids).asIntVector();

        for(int i = 0; i < j.size(); i++)
            restrictedAcces.insert(j[i]);
}

bool BannedIp::packetAccept(Packet* pck)
{
        if (restrictedAcces.find(pck->getSrc()) == restrictedAcces.end())
            return true;
        else
            return false;
}
