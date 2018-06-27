/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

/* 
 * File:   FullSync.cpp
 * Author: kaets
 * 
 * Created on June 27, 2018, 9:37 AM
 */

#include "FullSync.h"

FullSync::FullSync(bool oneWay=false) {
}

FullSync::~FullSync() {
    fullHash.clear();
}

bool FullSync::SyncClient(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    Logger::gLog(Logger::METHOD, "Entering FullSync::SyncClient");
    // local variables
    vec_ZZ_p delta_self, /** items I have that the other does not, based on the last synchronization. */
            delta_other; /** items the other has that I do not, based on the last synchronization. */

    // 0. Initialization;
    try {
        SyncMethod::SyncClient(commSync, selfMinusOther, otherMinusSelf); // call the base method - sets some fields to 0
        clock_t commStart = clock();
        
        // 0.5  verify commonality initial parameters
        // ... connect to the other party
        if (!keepAlive) {
            commSync->commConnect();

            // ... check that the other side is doing the same synchronization
            SendSyncParam(commSync, oneWay);
        }
    }
    
    // 1. Send all hashes
    vec_ZZ_p hashes;
    map<ZZ, DataObject*>::const_iterator iter = fullHash.begin();
    for (; iter != fullHash.end(); iter++) {
        hashes.append(iter->first);
    }
    commSync->commSend(fullHash);
    
    
}
bool FullSync::SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    
}
bool FullSync::addElem(DataObject* newDatum){
    
}
template <typename T>
bool FullSync::addElem(T* newDatum){
    
}
bool FullSync::delElem(DataObject* newDatum){
    
}
string FullSync::getName(){
    Logger::gLog(Logger::METHOD,"Entering FullSync::getName");
    // TODO: Write this.
}
string FullSync::printElem(){
    
}

