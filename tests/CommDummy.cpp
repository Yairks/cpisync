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
// init the string to an empty string
CommDummy::CommDummy() {
}

CommDummy::~CommDummy() {
}

// Does nothing
void CommDummy::commListen(){
}

// ""
void CommDummy::commConnect(){    
}

// ""
void CommDummy::commClose(){
}

// adds toSend to a stringstream. Note that the size of toSend is usually
// represented some way in some data structure for Communicants. To simplify
// things, we merely increment the amount of sent bytes. This behavior lets us
// test that commSend(const char*, int) is called by other functions.
void CommDummy::commSend(const char* toSend, const int numBytes){
    const int calcLen = 0;
    recv << toSend;
    
    addXmitBytes(numBytes == calcLen ? strlen(toSend) : numBytes);
}

void CommDummy::resetRecv(){
    recv.str("");
}

string CommDummy::getRecv(){
    return recv.str();
}

// returns a string specified by the state of output.
string CommDummy::commRecv(long numBytes){
    addRecvBytes(numBytes);
    switch(output){
        case AA:
            return string(2, '\x41'); // AA in hexadecimal
            break;
        case INT_FOUR:
            return string(1, '\x04') + string(sizeof(int)-1, '\0');
            break;
        case INT_FIVE:
            return string(1, '\x05') + string(sizeof(int)-1, '\0');
        case LONG_FOUR:
            return string(1, '\x04') + string(sizeof(long)-1, '\0');
            break;
        case DOPRIORITY_FOUR_AA:
            return "4," + string(2, '\x41');
            break;
        case SYNC_OK:
            return string(1, (char) SYNC_OK_FLAG);
            break;
        case SYNC_FAIL:
            return string(1, (char) SYNC_FAIL_FLAG);
            break;
    }
}
