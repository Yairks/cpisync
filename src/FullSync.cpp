/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

/* 
 * File:   FullSync.cpp
 * Author: kaets
 * 
 * Created on June 27, 2018, 9:37 AM
 */

#include "FullSync.h"
#include "Exceptions.h"

#include <algorithm>
FullSync::FullSync() {
}

FullSync::~FullSync() {

}

bool FullSync::SyncClient(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    try{
        Logger::gLog(Logger::METHOD, "Entering FullSync::SyncClient");
        // local variables

        // connect to the other party
        commSync->commConnect();

        // send all dataObjects

        commSync->commSend(setToDOList(mySet));

        // receive response from server with delta
        selfMinusOther = commSync->commRecv_DoList();
        otherMinusSelf = commSync->commRecv_DoList();

        Logger::gLog(Logger::METHOD, string("CPISync succeeded.\n"));
        return true;
    } catch(SyncFailureException s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw (s);
    }
    
}
bool FullSync::SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf){
    try {
        Logger::gLog(Logger::METHOD, "Entering FullSync::SyncServer");

        // listen for other party
        commSync->commListen();

        // receive client list once it is sent
        list<DataObject *> clientList = commSync->commRecv_DoList();

        // Calculate differences between two lists
        calcDiff(clientList, selfMinusOther, otherMinusSelf);

        // send back differences. keep in mind that our otherMinusSelf is their selfMinusOther and v.v.
        commSync->commSend(otherMinusSelf);
        commSync->commSend(selfMinusOther);

        Logger::gLog(Logger::METHOD, string("CPISync succeeded.\n"));
        return true;
    } catch (SyncFailureException s) {
        Logger::gLog(Logger::METHOD_DETAILS, s.what());
        throw (s);
    }
    
}

bool FullSync::addElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD,"Entering FullSync::addElem");
    mySet.insert(newDatum);
    return true;
}

template <typename T>
bool FullSync::addElem(T* newDatum){
    Logger::gLog(Logger::METHOD, "Entering FullSync::addElem");
    DataObject* d = new DataObject(newDatum);
    mySet.insert(d);
    return true;
}

bool FullSync::delElem(DataObject* newDatum){
    Logger::gLog(Logger::METHOD, "Entering FullSync::delElem");
    std::set<DataObject*>::iterator locErase = mySet.find(newDatum);
    if(locErase == mySet.end()) return false; // couldn't find element in set
    mySet.erase(locErase);
    return true; // successfully found and erased element in set
    
}
string FullSync::getName(){
    Logger::gLog(Logger::METHOD,"Entering FullSync::getName");
    return "I am a FullSync object.";
}
string FullSync::printElem(){
    stringstream ss;
    ss << "[";
            
    // use an iterator so we can detect the last element in the list and add commas correctly
    std::set<DataObject*>::iterator iter = mySet.begin();
    for(; iter != mySet.end(); iter++)
        ss << **iter << (iter != --mySet.end() ? ", " : "]");
    return ss.str();
}

// Helper function for comparing DataObject pointers. Simply dereferences them and compares them normally
bool cmp(DataObject* a, DataObject* b) {
    return (*a < *b);
}

void FullSync::calcDiff(list<DataObject*> clientList, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    selfMinusOther.clear();
    otherMinusSelf.clear();
    
    clientList.sort(cmp);
    
    set_difference(clientList.begin(), clientList.end(), mySet.begin(), mySet.end(), std::inserter(otherMinusSelf, otherMinusSelf.end()), cmp);
    set_difference(mySet.begin(), mySet.end(), clientList.begin(), clientList.end(), std::inserter(selfMinusOther, selfMinusOther.end()), cmp);

}

list<DataObject*> FullSync::setToDOList(std::set<DataObject *> dataSet) {
    list<DataObject*> dataList;
    
    std::set<DataObject*>::iterator ii = dataSet.begin();
    for(; ii != dataSet.end(); ii++)
        dataList.push_back(*ii);
    
    return dataList;
}