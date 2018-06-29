/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommunicantTest.cpp
 * Author: kaets
 *
 * Created on May 24, 2018, 10:08:52 AM
 */

#include "CommunicantTest.h"
#include "CommDummy.h"
#include "DataObject.h"
#include "Logger.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

CPPUNIT_TEST_SUITE_REGISTRATION(CommunicantTest);

// Generates `amt` random integers from the seeded prng
vector<int> genRandInt(int amt) {
    vector<int> vals;
    
    for(int ii = 0; ii < amt; ii++)
        vals.push_back(rand());
    
    return vals;
}

// Generates `amt` random strings with length chosen random s.t. `lower` <= length <= `upper`
vector<string> genRandString(int amt, int lower, int upper) {
    vector <string> vals;
    
    for(int ii = 0; ii < amt; ii++) {
        stringstream str;
        
        // pick a length in between lower and upper, inclusive
        int length = (rand() % (upper + 1));
        if(length < lower) length = lower;
        
        for(int jj = 0; jj < length; jj++)
            str << (char) (rand() % (int) ((pow(2, CHAR_BIT)-1))); // generate a random character and add to stringstream
        
        vals.push_back(str.str());
    }
    
    return vals;
}

CommunicantTest::CommunicantTest() {
}

CommunicantTest::~CommunicantTest() {
}

void CommunicantTest::setUp() {
    const int MY_SEED = 123456; // a preset seed for pseudorandom number generation
    srand(MY_SEED); // seed the prng predictably so that the random numbers generated are predictable and reproducible
}

void CommunicantTest::tearDown() {
}

void CommunicantTest::testConstruct() {
    try {
        queue<char> qq;
        CommDummy c(&qq); // since every constructor calls their ancestor's empty constructors, we effectively test Communicant's empty constructor
    } catch(...) {
        CPPUNIT_FAIL("Expected no exceptions.");
    }
    
    // no exceptions thrown
    CPPUNIT_ASSERT(true);
}

void CommunicantTest::testBytesAndResetCommCounters() {
    queue<char> qq;
    
    // set up two communicants to either send or receive
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    const long int NONE = 0;
    const string STR = "hello world";
    const long int STR_LENGTH = STR.length();
    
    CPPUNIT_ASSERT_EQUAL(NONE, cSend.getXmitBytesTot());
    CPPUNIT_ASSERT_EQUAL(NONE, cRecv.getRecvBytesTot());
    
    cSend.resetCommCounters();
    cRecv.resetCommCounters();
    
    CPPUNIT_ASSERT_EQUAL(NONE, cSend.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(NONE, cRecv.getRecvBytes());
            
    cSend.commSend(STR.data(), STR_LENGTH);
    
    CPPUNIT_ASSERT_EQUAL(STR_LENGTH, cSend.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(STR_LENGTH, cSend.getXmitBytesTot());
    
    cRecv.commRecv(STR.length());
    
    CPPUNIT_ASSERT_EQUAL(STR_LENGTH, cRecv.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(STR_LENGTH, cRecv.getRecvBytesTot());
    
    cSend.resetCommCounters();
    cRecv.resetCommCounters();
    
    CPPUNIT_ASSERT_EQUAL(NONE, cRecv.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(NONE, cSend.getXmitBytes());
}

void CommunicantTest::testEstablishModAndCommZZ_p() {
    queue<char> qq;
    
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    // Generate two sets of 100 random mods and ZZ_p values
    const int SIZE = 100;
    const vector<int> TEST_VALUES = genRandInt(SIZE);
    const vector<int> TEST_MODS = genRandInt(SIZE);
    
    for(int ii = 0; ii < SIZE; ii++) {
        const ZZ MOD(TEST_MODS[ii]);
        ZZ_p::init(MOD);
    
        // Tests that establishMod works with oneWay set to true.
        const bool ONE_WAY = true;
        CPPUNIT_ASSERT(cSend.establishModSend(ONE_WAY)); 
        CPPUNIT_ASSERT(cRecv.establishModRecv(ONE_WAY));
        
        const ZZ_p EXP(TEST_VALUES[ii]);
        cSend.Communicant::commSend(EXP);
        const ZZ_p RES = cRecv.commRecv_ZZ_p();
        
        CPPUNIT_ASSERT_EQUAL(EXP, RES);
    }
}

void CommunicantTest::testCommUstringBytes() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const int SIZE = 100;
    const int LOWER_BOUND = 1;
    const int UPPER_BOUND = 250; // arbitrary upper bound
    
    const vector<string> TEST_VALUES = genRandString(SIZE, LOWER_BOUND, UPPER_BOUND);
    
    for(int ii = 0; ii < SIZE; ii++) {
        const ustring EXP = (const unsigned char *) (TEST_VALUES[ii].data());
        const int EXP_LEN = EXP.size();

        // check that transmitted bytes are successfully incremented 
        const long int BEFORE = cSend.getXmitBytes();
        cSend.Communicant::commSend(EXP, EXP_LEN);
        const long int AFTER = cSend.getXmitBytes();

        const ustring RES = cRecv.commRecv_ustring(EXP_LEN);

        CPPUNIT_ASSERT_EQUAL(EXP.compare(RES), 0);
        CPPUNIT_ASSERT_EQUAL(BEFORE + EXP_LEN, AFTER);
    }
}

void CommunicantTest::testCommUstringNoBytes() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const int SIZE = 100;
    const int LOWER_BOUND = 1;
    const int UPPER_BOUND = 25; // arbitrary upper bound
    
    const vector<string> TEST_VALUES = genRandString(SIZE, LOWER_BOUND, UPPER_BOUND);
    
    for(int ii = 0; ii < SIZE; ii++) {
        const ustring EXP = (const unsigned char *) (TEST_VALUES[ii].data());
        cSend.Communicant::commSend(EXP);
        const ustring RES = cRecv.commRecv_ustring();
    
        CPPUNIT_ASSERT_EQUAL(EXP.compare(RES), 0);
    }
}

void CommunicantTest::testCommString() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const string EXP = "ghijk";
    
    cSend.Communicant::commSend(EXP);
    const string RES = cSend.commRecv_string();
    
    CPPUNIT_ASSERT_EQUAL(EXP, RES);
}

void CommunicantTest::testCommLong() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const long int EXP = 1234567890;
    cSend.Communicant::commSend(EXP);
   
    const long int RES = cRecv.commRecv_long();

    CPPUNIT_ASSERT_EQUAL(EXP, RES);
}

void CommunicantTest::testCommDataObject() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);

    DataObject exp(string("abcdef"));
    cSend.Communicant::commSend(exp);
    DataObject* res = cRecv.commRecv_DataObject();

    // same as testing for equality.
    CPPUNIT_ASSERT(!(exp < *res || *res < exp));
    CPPUNIT_ASSERT_EQUAL(exp.getPriority(), res->getPriority());
}

void CommunicantTest::testCommDataObjectPriority() { // fix this test so that the repisint doesnt need to be changed
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);

    const bool SEND_PRIORITY = true;
    const string INIT = "65";
    // Test case where RepIsInt is true
    DataObject::RepIsInt = true;

    DataObject expA(INIT);
    const ZZ PRIORITY(5l);
    expA.setPriority(PRIORITY);
   
    cSend.Communicant::commSend(expA, SEND_PRIORITY);
    DataObject* resA = cRecv.commRecv_DataObject_Priority();

    // same as testing for equality.
    CPPUNIT_ASSERT(!(expA < *resA || *resA < expA));
    CPPUNIT_ASSERT_EQUAL(expA.getPriority(), resA->getPriority());
            
    // Test case where RepIsInt is false
    DataObject::RepIsInt = false;
    DataObject expB(INIT);
    expB.setPriority(PRIORITY);
    cSend.Communicant::commSend(expB, SEND_PRIORITY);

    DataObject* resB = cRecv.commRecv_DataObject_Priority();

    CPPUNIT_ASSERT(!(expB < *resB || *resB < expB));
    CPPUNIT_ASSERT_EQUAL(expB.getPriority(), resB->getPriority());
}

void CommunicantTest::testCommDataObjectList() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    DataObject::RepIsInt = false;
    list<DataObject*> exp;
    DataObject vals[] = {
        DataObject(string("abc")),
        DataObject(string("def")),
        DataObject(string("ghi")),
        DataObject(string("jkl"))
    };
    
    for(DataObject& dd : vals)
        exp.push_back(&dd);
    
    cSend.Communicant::commSend(exp);
    const list<DataObject*> RES = cRecv.commRecv_DoList();

    // assert same length before iterating to check their equality
    CPPUNIT_ASSERT_EQUAL(exp.size(), RES.size());
    
    list<DataObject*>::const_iterator expI = exp.begin();
    list<DataObject*>::const_iterator resI = RES.begin();
    
    for(int i = 0; i < exp.size(); i++) {
        DataObject currExp = **expI;
        DataObject currRes = **resI;
        CPPUNIT_ASSERT(!(currExp < currRes || currRes < currExp)); // equality test for each DataObject
        CPPUNIT_ASSERT_EQUAL(currExp.getPriority(), currRes.getPriority());
        // increment both iterators
        advance(expI, 1);
        advance(resI, 1);
    }
}

void CommunicantTest::testCommDouble() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const double EXP = 332343.53125;
    cSend.Communicant::commSend(EXP);
    
    const double RES = cRecv.commRecv_double();
   
    CPPUNIT_ASSERT_EQUAL(EXP, RES);
}

void CommunicantTest::testCommByte() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const byte EXP = '\xFF';

    cSend.Communicant::commSend(EXP);
    const byte RES = cRecv.commRecv_byte();

    CPPUNIT_ASSERT_EQUAL(EXP, RES);
}

void CommunicantTest::testCommInt() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    const int EXP = 23456;

    cSend.Communicant::commSend(EXP);
    
    const int RES = cRecv.commRecv_int();

    CPPUNIT_ASSERT_EQUAL(EXP, RES);
}

void CommunicantTest::testCommVec_ZZ_p() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);
    
    // Set moduli
    const bool ONE_WAY = true;
    const ZZ MODULUS(667l);
    ZZ_p::init(MODULUS);
    cSend.establishModSend(ONE_WAY);
    cRecv.establishModRecv(ONE_WAY);
    
    const ZZ_p VALS[] = {
        static_cast<ZZ_p>(123),
        static_cast<ZZ_p>(456),
        static_cast<ZZ_p>(789)
    };
    vec_ZZ_p exp;
    
    for(ZZ_p val : VALS)
        exp.append(val);
   
    cSend.Communicant::commSend(exp);

    const vec_ZZ_p RES = cRecv.commRecv_vec_ZZ_p();
    CPPUNIT_ASSERT_EQUAL(exp, RES);
}

void CommunicantTest::testCommZZ() {
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);

    const ZZ EXP(123456l);
    const int EXP_SIZE = sizeof(EXP);

    cSend.Communicant::commSend(EXP, EXP_SIZE);
    const ZZ RES = cRecv.commRecv_ZZ(EXP_SIZE);

    CPPUNIT_ASSERT_EQUAL(EXP, RES);
}

void CommunicantTest::testCommZZNoArgs(){
    queue<char> qq;
    CommDummy cSend(&qq);
    CommDummy cRecv(&qq);

    const ZZ EXP(123456l);
    cSend.Communicant::commSend(EXP);
    const ZZ RES = cRecv.commRecv_ZZ();

    CPPUNIT_ASSERT_EQUAL(EXP,RES);
}
