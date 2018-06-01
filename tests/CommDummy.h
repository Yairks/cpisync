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

class CommDummy : public Communicant {
public:
    enum OUTPUTS {
        AA = 1,
        SIZE_AA = 2,
        PRIORITY_OBJECT_REPISINT_FALSE = 3,
        PRIORITY_OBJECT_REPISINT_TRUE = 4,
        LONG = 5,
        DOPRIORITY = 6
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
protected:
    string recv;
};

#endif /* COMMDUMMY_H */

