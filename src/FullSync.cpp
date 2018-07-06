/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

/* 
 * File:   FullSync.cpp
 * Author: kaets
 * 
 * Created on June 27, 2018, 9:37 AM
 */

#include "FullSync.h"

FullSync::FullSync() {
}

FullSync::~FullSync() {
}

string FullSync::printElem() {
    vector<DataObject *>::const_iterator iter = SyncMethod::beginElements();

    stringstream ss;
    ss << '[';
    
    for(;  iter != SyncMethod::endElements(); iter++)
        ss << **iter << (iter == prev(SyncMethod::endElements()) ? "]" : " ");
    
    return ss.str();

}

bool FullSync::SyncClient(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    try{
        Logger::gLog(Logger::METHOD, "Entering FullSync::SyncClient");

        // call parent method for bookkeeping
        SyncMethod::SyncClient(commSync, selfMinusOther, otherMinusSelf);
        
        // connect to the other party
        commSync->commConnect();

        // send my set
        
        // first send the amount of DataObjects...
        commSync->commSend(SyncMethod::getNumElem());
        
        // then send each DataObject.
        vector<DataObject *>::const_iterator iter = SyncMethod::beginElements();
        for(; iter != SyncMethod::endElements(); iter++)
            commSync->commSend(**iter);

        // receive response from server with differences
        selfMinusOther = commSync->commRecv_DoList();
        otherMinusSelf = commSync->commRecv_DoList();

        stringstream msg;
        msg << "FullSync succeeded." << endl;
        msg << "self - other = " << printListOfPtrs(selfMinusOther) << endl;
        msg << "other - self = " << printListOfPtrs(otherMinusSelf) << endl;
        Logger::gLog(Logger::METHOD, msg.str());
        
        return true;
    } catch(SyncFailureException s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw (s);
    }
    
}
bool FullSync::SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    try {
        Logger::gLog(Logger::METHOD, "Entering FullSync::SyncServer");

        // call parent method for bookkeeping
        SyncMethod::SyncServer(commSync, selfMinusOther, otherMinusSelf);
        
        // listen for other party
        commSync->commListen();

        // receive client list once it is sent
        
        // first, receive how many DataObjects have been sent...
        const long SIZE = commSync->commRecv_long();
        
        // then receive each DataObject and store to a list
        multiset<DataObject *> clientSet;
        for(int ii = 0; ii < SIZE; ii++)
            clientSet.insert(commSync->commRecv_DataObject());
            
        // Calculate differences between two lists
        calcDiff(clientSet, selfMinusOther, otherMinusSelf);
        
        // send back differences. keep in mind that our otherMinusSelf is their selfMinusOther and v.v.
        commSync->commSend(otherMinusSelf);
        commSync->commSend(selfMinusOther);
        
        stringstream msg;
        msg << "FullSync succeeded." << endl;
        msg << "self - other = " << printListOfPtrs(selfMinusOther) << endl;
        msg << "other - self = " << printListOfPtrs(otherMinusSelf) << endl;
        Logger::gLog(Logger::METHOD, msg.str());
        
        return true;
    } catch (SyncFailureException s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw (s);
    }
    
}

bool FullSync::addElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD,"Entering FullSync::addElem");
    
    bool success = SyncMethod::addElem(newDatum);
    if(success) Logger::gLog(Logger::METHOD, "Successfully added DataObject* {" + newDatum->print() + "}");
    return success;
    
}

bool FullSync::delElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD, "Entering FullSync::delElem");
    
    bool success = SyncMethod::delElem(newDatum);
    if(success) Logger::gLog(Logger::METHOD, "Successfully removed DataObject* {" + newDatum->print() + "}");
    return success;
}

// Helper function for comparing DataObject pointers. Simply dereferences b and compares them normally
bool cmp(const DataObject* a, const DataObject* b) {
    return (a->operator <(*b));
}

void FullSync::calcDiff(multiset<DataObject*> clientSet, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    Logger::gLog(Logger::METHOD,"Entering CPISync::calcDiff");
    
    set_difference(clientSet.begin(), clientSet.end(), SyncMethod::beginElements(), SyncMethod::endElements(), back_inserter(otherMinusSelf), cmp);
    set_difference(SyncMethod::beginElements(), SyncMethod::endElements(), clientSet.begin(), clientSet.end(), back_inserter(selfMinusOther), cmp);
}