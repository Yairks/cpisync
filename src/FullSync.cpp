/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

/* 
 * File:   FullSync.cpp
 * Author: kaets
 * 
 * Created on June 27, 2018, 9:37 AM
 */

#include "FullSync.h"
#include <algorithm>
FullSync::FullSync() {
}

FullSync::~FullSync() {

}

bool FullSync::SyncClient(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    Logger::gLog(Logger::METHOD, "Entering FullSync::SyncClient");
    // local variables
    list<DataObject *> delta_self, /** items I have that the other does not, based on the last synchronization. */
            delta_other; /** items the other has that I do not, based on the last synchronization. */

    // 0. Initialization;

    SyncMethod::SyncClient(commSync, selfMinusOther, otherMinusSelf); // call the base method - sets some fields to 0
    clock_t commStart = clock();

    // 0.5  verify commonality initial parameters
    // ... connect to the other party
    commSync->commConnect();

    // ... check that the other side is doing the same synchronization
    SendSyncParam(commSync);

    
    // 1. Send all dataObjects

    commSync->commSend(myList);
    
    // receive response from server with delta
    selfMinusOther = commSync->commRecv_DoList();
    otherMinusSelf = commSync->commRecv_DoList();

    Logger::gLog(Logger::METHOD, string("CPISync succeeded.\n")
            + "   self - other =  " + toStr<list<DataObject *> > (delta_self) + "\n"
            + "   other - self =  " + toStr<list<DataObject *> > (delta_other) + "\n"
            + "\n");
    
    
    return true;
    
}
bool FullSync::SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    Logger::gLog(Logger::METHOD, "Entering FullSync::SyncServer");
    // local variables
    list<DataObject *> delta_self,
            delta_other;
    
    SyncMethod::SyncServer(commSync, selfMinusOther, otherMinusSelf);
    
    commSync->commConnect();
    SendSyncParam(commSync);
    
    // Wait for client's DataObject list to be sent.
    list<DataObject *> client_list = commSync->commRecv_DoList();
    
    // Calculate differences between two lists
    calcDiff(client_list, selfMinusOther, otherMinusSelf);
    
    // Send back differences
    commSync->commSend(selfMinusOther);
    commSync->commSend(otherMinusSelf);
    
    Logger::gLog(Logger::METHOD, string("CPISync succeeded.\n")
        + "   self - other =  " + toStr<list<DataObject *> > (delta_self) + "\n"
        + "   other - self =  " + toStr<list<DataObject *> > (delta_other) + "\n"
        + "\n");
    
    return true;
    
}
bool FullSync::addElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD,"Entering FullSync::addElem");
    // TODO: implement

}
template <typename T>
bool FullSync::addElem(T* newDatum){
    //TODO: implement
    
}
bool FullSync::delElem(DataObject* newDatum){
    //TODO: implement
    
}
string FullSync::getName(){
    Logger::gLog(Logger::METHOD,"Entering FullSync::getName");
    // TODO: implement
}
string FullSync::printElem(){
    
}
// could likely be improved since selfMinusOther and otherMinusSelf don't necessarily have to be cleared and maybe shouldn't
// rough draft atm
void FullSync::calcDiff(list<DataObject*> clientList, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    selfMinusOther.clear();
    otherMinusSelf.clear();
    
    set_difference(clientList.begin(), clientList.end(), myList.begin(), myList.end(), otherMinusSelf.begin());
    set_difference(myList.begin(), myList.end(), clientList.begin(), clientList.end(), selfMinusOther.begin());
}
