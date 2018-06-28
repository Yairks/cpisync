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
    commSync->commSend(hashes);
    
    if(!oneWay) {
        // receive response from server with delta
        delta_other = commSync->commRecv_vec_ZZ_p();
        delta_self = commSync->commRecv_vec_ZZ_p();

        Logger::gLog(Logger::METHOD, string("CPISync succeeded.\n")
                + "   self - other =  " + toStr<vec_ZZ_p > (delta_self) + "\n"
                + "   other - self =  " + toStr<vec_ZZ_p > (delta_other) + "\n"
                + "\n");
        string results= string("... results:\n")
                    + "   self - other =  " + toStr<vec_ZZ_p > (delta_self) + "\n"
                    + "   other - self =  " + toStr<vec_ZZ_p > (delta_other) + "\n"
                    + "\n";
        
        selfMinusOther = delta_other;
        otherMinusSelf = delta_self;
    }
    
    
    // TODO: report the results of reconciliation; handle exceptions
    return true;
    
}
bool FullSync::SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    
}
bool FullSync::addElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD,"Entering FullSync::addElem");

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

