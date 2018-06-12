/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/* 
 * File:   CommDummy.cpp
 * Author: kaets
 * 
 * Created on May 24, 2018, 10:13 AM
 */

#include "CommDummy.h"
#include <string.h>

CommDummy::OUTPUTS CommDummy::output = CommDummy::AA;
//// init the string to an empty string
CommDummy::CommDummy() {
//    recv = "";
}
//
CommDummy::~CommDummy() {
}
//// Does nothing
void CommDummy::commListen(){
//    
}
//// ""
void CommDummy::commConnect(){
//    
}
//// ""
void CommDummy::commClose(){
//    
}
//// adds toSend to a stringstream
void CommDummy::commSend(const char* toSend, const int numBytes){
    recv << toSend;
    
    addXmitBytes(numBytes);
}
void CommDummy::resetRecv(){
    recv.str("");
}
string CommDummy::getRecv(){
    return recv.str();
}
//
//// RETURNS AA
string CommDummy::commRecv(long numBytes){
    addRecvBytes(numBytes);
    switch(output){
        case AA:
            return "AA";
            break;
        case PRIORITY_OBJECT_REPISINT_FALSE: // change this lol or wait no maybe dont idk but come back to this s
            return "AAAA";
            break;
        case PRIORITY_OBJECT_REPISINT_TRUE:
            return string(1, '\x04') + string(sizeof(int)-1, '\0');
            break;
        case LONG:
            return string(1, '\x04') + string(sizeof(long)-1, '\0');
            break;
        case DOPRIORITY:
            return "4,AA";
            break;
    }
   // return "AA";
}
