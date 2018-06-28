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

CPPUNIT_TEST_SUITE_REGISTRATION(CommunicantTest);

CommunicantTest::CommunicantTest() {
}

CommunicantTest::~CommunicantTest() {
}

void CommunicantTest::setUp() {
}

void CommunicantTest::tearDown() {
}

void CommunicantTest::testConstruct() {
    try {
        queue<char> q;
        CommDummy c(&q); // since every constructor calls their ancestor's empty constructors, we effectively test Communicant's empty constructor
    } catch(...) {
        CPPUNIT_FAIL("Expected no exceptions.");
    }
    
    // no exceptions thrown
    CPPUNIT_ASSERT(true);
}

void CommunicantTest::testBytesAndResetCommCounters() {
    queue<char> q;
    
    // set up two communicants to either send or receive
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    long int none = 0;
    string str = "hello world";
    long int strLength = str.length();
    
    CPPUNIT_ASSERT_EQUAL(none, cSend.getXmitBytesTot());
    CPPUNIT_ASSERT_EQUAL(none, cRecv.getRecvBytesTot());
    
    cSend.resetCommCounters();
    cRecv.resetCommCounters();
    
    CPPUNIT_ASSERT_EQUAL(none, cSend.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(none, cRecv.getRecvBytes());
            
    cSend.commSend(str.data(), strLength);
    
    CPPUNIT_ASSERT_EQUAL(strLength, cSend.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(strLength, cSend.getXmitBytesTot());
    
    cRecv.commRecv(str.length());
    
    CPPUNIT_ASSERT_EQUAL(strLength, cRecv.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(strLength, cRecv.getRecvBytesTot());
    
    cSend.resetCommCounters();
    cRecv.resetCommCounters();
    
    CPPUNIT_ASSERT_EQUAL(none, cRecv.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(none, cSend.getXmitBytes());
}

void CommunicantTest::testEstablishModAndCommZZ_p() {
    queue<char> q;
    
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    int _mod = 4;
    ZZ mod = static_cast<ZZ>(_mod);
    ZZ_p::init(mod);
    
    // Tests that everything works with oneWay set to true.
    bool oneWay = true;
    bool succ = cSend.establishModSend(oneWay);
    CPPUNIT_ASSERT(succ);
    succ = cRecv.establishModRecv(oneWay);
    CPPUNIT_ASSERT(succ);
    
    int n = 9;
    ZZ_p exp = static_cast<ZZ_p>(n % _mod);
    cSend.Communicant::commSend(exp);
    ZZ_p res = cRecv.commRecv_ZZ_p();
    
    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommUstringBytes() {
    queue<char> p;
    CommDummy cSend(&p);
    CommDummy cRecv(&p);
    
    ustring exp = reinterpret_cast<const unsigned char*>("abcdef");
    int expLen = exp.size();
    
    int before = cSend.getXmitBytes();
    cSend.Communicant::commSend(exp, expLen);
    int after = cSend.getXmitBytes();
    
    ustring res = cRecv.commRecv_ustring(expLen);

    CPPUNIT_ASSERT_EQUAL(exp.compare(res), 0);
    CPPUNIT_ASSERT_EQUAL(before + expLen, after);
}

void CommunicantTest::testCommUstringNoBytes() {
    queue<char> p;
    CommDummy cSend(&p);
    CommDummy cRecv(&p);
    
    ustring exp = reinterpret_cast<const unsigned char*>("abcdef");
    
    cSend.Communicant::commSend(exp);
    ustring res = cRecv.commRecv_ustring();
    
    CPPUNIT_ASSERT_EQUAL(exp.compare(res), 0);
   
}

void CommunicantTest::testCommString() {
    queue<char> p;
    CommDummy cSend(&p);
    CommDummy cRecv(&p);
    
    string exp = "ghijk";
    
    cSend.Communicant::commSend(exp);
    string res = cSend.commRecv_string();
    
    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommLong() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    long int exp = 1234567890;
    cSend.Communicant::commSend(exp);
   
    long int res = cRecv.commRecv_long();

    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommDataObject() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);

    DataObject exp(string("abcdef"));
    cSend.Communicant::commSend(exp);
    DataObject* res = cRecv.commRecv_DataObject();

    // same as testing for equality.
    CPPUNIT_ASSERT(!(exp < *res || *res < exp));
    CPPUNIT_ASSERT_EQUAL(exp.getPriority(), res->getPriority());
}

void CommunicantTest::testCommDataObjectPriority() { // fix this test so that the repisint doesnt need to be changed
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);

    const bool sendPriority = true;

    // Test case where RepIsInt is true
    DataObject::RepIsInt = true;
    DataObject expA(string("65"));
    int _priority = 5;
    ZZ priority = static_cast<ZZ>(_priority);

    expA.setPriority(priority);
    cSend.Communicant::commSend(expA, sendPriority);
    DataObject* resA = cRecv.commRecv_DataObject_Priority();

    // same as testing for equality.
    CPPUNIT_ASSERT(!(expA < *resA || *resA < expA));
    CPPUNIT_ASSERT_EQUAL(expA.getPriority(), resA->getPriority());
            
    // Test case where RepIsInt is false
    DataObject::RepIsInt = false;
    DataObject expB(string("65"));
    cSend.Communicant::commSend(expB, sendPriority);

    DataObject* resB = cRecv.commRecv_DataObject_Priority();

    CPPUNIT_ASSERT(!(expB < *resB || *resB < expB));
    CPPUNIT_ASSERT_EQUAL(expB.getPriority(), resB->getPriority());
}

void CommunicantTest::testCommDataObjectList() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    DataObject::RepIsInt = false;
    list<DataObject*> exp;
    DataObject vals[] = {
        DataObject(string("abc")),
        DataObject(string("def")),
        DataObject(string("ghi")),
        DataObject(string("jkl"))
    };
    
    for(DataObject& d : vals)
        exp.push_back(&d);
    
    cSend.Communicant::commSend(exp);
    list<DataObject*> res = cRecv.commRecv_DoList();

    // assert same length before iterating to check their equality
    CPPUNIT_ASSERT_EQUAL(exp.size(), res.size());
    
    list<DataObject*>::iterator expI = exp.begin();
    list<DataObject*>::iterator resI = res.begin();
    
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
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    double exp = 332343.53125;
    cSend.Communicant::commSend(exp);
    
    double res = cRecv.commRecv_double();
   
    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommByte() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    byte exp = '\xFF';

    cSend.Communicant::commSend(exp);
    byte res = cRecv.commRecv_byte();

    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommInt() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    int exp = 23456;

    cSend.Communicant::commSend(exp);
    
    int res = cRecv.commRecv_int();

    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommVec_ZZ_p() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);
    
    // Set moduli
    bool oneWay = true;
    int _modulus = 667;
    ZZ modulus = static_cast<ZZ>(_modulus);
    ZZ_p::init(modulus);
    cSend.establishModSend(oneWay);
    cRecv.establishModRecv(oneWay);
    
    ZZ_p vals[] = {
        static_cast<ZZ_p>(123),
        static_cast<ZZ_p>(456),
        static_cast<ZZ_p>(789)
    };
    vec_ZZ_p exp;
    
    for(ZZ_p val : vals)
        exp.append(val);
   
    cSend.Communicant::commSend(exp);

    vec_ZZ_p res = cRecv.commRecv_vec_ZZ_p();
    CPPUNIT_ASSERT_EQUAL(exp, res);
    
}

void CommunicantTest::testCommZZ() {
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);

    int _exp = 123456;
    ZZ exp = static_cast<ZZ>(_exp);
    cSend.Communicant::commSend(exp, sizeof(exp));
    ZZ res = cRecv.commRecv_ZZ(sizeof(exp));

    CPPUNIT_ASSERT_EQUAL(exp, res);
}

void CommunicantTest::testCommZZNoArgs(){
    queue<char> q;
    CommDummy cSend(&q);
    CommDummy cRecv(&q);

    int _exp = 123456;
    ZZ exp = static_cast<ZZ>(_exp);
    cSend.Communicant::commSend(exp);
    ZZ res = cRecv.commRecv_ZZ();

    CPPUNIT_ASSERT_EQUAL(exp, res);
}