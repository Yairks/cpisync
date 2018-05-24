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
//// Stores the first numBytes characters of toSend as a string,
//// overwriting any previous data
void CommDummy::commSend(const char* toSend, const int numBytes){
//    char tmp[numBytes];
//    strncpy(tmp, toSend, numBytes);
//    recv = tmp;
    addXmitBytes(numBytes);
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
        default:
            return "E";
            break;
    }
   // return "AA";
}
