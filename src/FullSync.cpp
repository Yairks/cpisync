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

template <typename Iterator> 
string FullSync::printElem(const Iterator begin, const Iterator end) {
    Iterator iter = Iterator(begin);
    
    stringstream ss;
    ss << '[';
    
    for(;  iter != end; iter++)
        ss << **iter << (iter == prev(end) ? "]" : ", ");
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
        commSync->commSend(repDOList());

        // receive response from server with differences
        selfMinusOther = commSync->commRecv_DoList();
        otherMinusSelf = commSync->commRecv_DoList();

        stringstream msg;
        msg << "FullSync succeeded." << endl;
        msg << "self - other = " << printElem(selfMinusOther.begin(), selfMinusOther.end()) << endl;
        msg << "other - self = " << printElem(otherMinusSelf.begin(), otherMinusSelf.end()) << endl;
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
        list<DataObject *> clientList = commSync->commRecv_DoList();

        // Calculate differences between two lists
        calcDiff(clientList, selfMinusOther, otherMinusSelf);

        // send back differences. keep in mind that our otherMinusSelf is their selfMinusOther and v.v.
        commSync->commSend(otherMinusSelf);
        commSync->commSend(selfMinusOther);
        
        stringstream msg;
        msg << "FullSync succeeded." << endl;
        msg << "self - other = " << printElem(selfMinusOther.begin(), selfMinusOther.end()) << endl;
        msg << "other - self = " << printElem(otherMinusSelf.begin(), otherMinusSelf.end()) << endl;
        Logger::gLog(Logger::METHOD, msg.str());
        
        return true;
    } catch (SyncFailureException s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw (s);
    }
    
}

bool FullSync::addElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD,"Entering FullSync::addElem");
    
    /* first, check that the vector in SyncMethod doesn't contain the element being inserted.
     * if it does, return false and don't add the element */
    vector<DataObject*>::const_iterator iter = SyncMethod::beginElements();
    for(; iter != SyncMethod::endElements(); iter++)
        if(!(**iter < *newDatum || *newDatum < **iter)) return false;
    
    /* since adding this element to our vector wouldn't invalidate its set invariant,
     * call the parent addElem method */
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

string FullSync::printElem(){
    Logger::gLog(Logger::METHOD,"Entering CPISync::printElem");
    return printElem(SyncMethod::beginElements(), SyncMethod::endElements());
}

// Helper function for comparing DataObject pointers. Simply dereferences them and compares them normally
bool cmp(const DataObject* a, const DataObject* b) {
    return (*a < *b);
}

void FullSync::calcDiff(list<DataObject*> clientList, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    Logger::gLog(Logger::METHOD,"Entering CPISync::calcDiff");
    selfMinusOther.clear();
    otherMinusSelf.clear();
    
    clientList.sort(cmp);
    
    std::set_difference(clientList.begin(), clientList.end(), SyncMethod::beginElements(), SyncMethod::endElements(), std::inserter(otherMinusSelf, otherMinusSelf.end()), cmp);
    std::set_difference(SyncMethod::beginElements(), SyncMethod::endElements(), clientList.begin(), clientList.end(), std::inserter(selfMinusOther, selfMinusOther.end()), cmp);

}

list<DataObject*> FullSync::repDOList() {
    Logger::gLog(Logger::METHOD,"Entering CPISync::repDOList");
    list<DataObject*> dataList;
    
    vector<DataObject*>::const_iterator iter = SyncMethod::beginElements();
    for(; iter != SyncMethod::endElements(); iter++)
        dataList.push_back(*iter);
    
    return dataList;
}