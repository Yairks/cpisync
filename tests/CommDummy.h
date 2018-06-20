/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/* 
 * File:   CommDummy.h
 * Author: kaets
 *
 * Created on May 24, 2018, 10:13 AM
 */

#ifndef COMMDUMMY_H
#define COMMDUMMY_H

#include "Communicant.h"
#include <sstream>
#include "ConstantsAndTypes.h"

class CommDummy : public Communicant {
public:
    enum OUTPUTS {
        AA = 1,
        INT_FOUR = 2,
        INT_FIVE = 3,
        LONG_FOUR = 4,
        DOPRIORITY_FOUR_AA = 5,
        SYNC_OK = 6,
        SYNC_FAIL = 7
    };
    
    static OUTPUTS output;
    
    CommDummy();
    ~CommDummy();
    
    // Inherited Communicant methods
    void commListen();
    void commConnect();
    void commClose();
    void commSend(const char* toSend, const int numBytes);
    string commRecv(long numBytes);
    string getName(){ return "dummy"; }
    string getRecv();
    void resetRecv();
protected:
    stringstream recv;
};

#endif /* COMMDUMMY_H */

