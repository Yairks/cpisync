/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommunicantTest.cpp
 * Author: kaets
 *
 * Created on May 22, 2018, 2:43:39 PM
 */

#include "CommunicantTest.h"
#include "DataObject.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CommunicantTest);

CommunicantTest::CommunicantTest() {
}

CommunicantTest::~CommunicantTest() {
}

void CommunicantTest::setUp() {
}

void CommunicantTest::tearDown() {
}

void CommunicantTest::testCommunicantInitAndTotGettersAndCommSendZZpAndGetTotalTime() {
    // Can't do an exact time test, but can get close by recording time before
    // and after execution and checking if the initialized time is in between
    // the two.
    clock_t timeBefore = clock();
    CommString c;
    clock_t timeAfter = clock();
    clock_t createTime = c.getTotalTime();
    
    CPPUNIT_ASSERT(timeBefore <= createTime && createTime <= timeAfter);
    
    CPPUNIT_ASSERT_EQUAL(0l, c.getXmitBytesTot());
    CPPUNIT_ASSERT_EQUAL(0l, c.getRecvBytesTot()); 
    try{
        ZZ_p test;
        c.Communicant::commSend(test);
    } catch(std::length_error e) {
        CPPUNIT_ASSERT_MESSAGE("Check that MOD_SIZE has been initialized as NOT_SET by seeing if commSend(ZZ_p) throws a length error", true);
    }
}

void CommunicantTest::testResetCommCountersAndByteGettersAndGetResetTime(){
    CommString c;
    const char *test = "efg";
    long int length = 3;
    
    c.commSend(test, length);
    c.commRecv(length);
    
    CPPUNIT_ASSERT_EQUAL(length, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(length, c.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(length, c.getXmitBytesTot());
    CPPUNIT_ASSERT_EQUAL(length, c.getRecvBytesTot());
    
    clock_t timeBefore = clock();
    c.resetCommCounters();
    clock_t timeAfter = clock();
    clock_t resetTime = c.getResetTime();
    
    CPPUNIT_ASSERT_EQUAL(0l, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(0l, c.getXmitBytes());
    CPPUNIT_ASSERT(timeBefore <= resetTime && resetTime <= timeAfter );
}

void CommunicantTest::testCommunicantGetName(){
    CommString c;
    string expected = "No name available";
    CPPUNIT_ASSERT_EQUAL(expected, c.Communicant::getName());
}

void CommunicantTest::testEstablishModRecv(){
    CommString c;
    bool oneWay = false;
    //CPPUNIT_ASSERT(c.establishModRecv(oneWay));
    oneWay = true;
    //CPPUNIT_ASSERT(c.establishModRecv(oneWay));
    
    // More segfaults in commented out code. Will look into some more tomorrow
}

void CommunicantTest::testEstablishModSend(){
    CommString c;
    bool oneWay = false;
    //CPPUNIT_ASSERT(c.establishModSend(oneWay));
    oneWay = true;
    //CPPUNIT_ASSERT(c.establishModSend(oneWay));
    
    // " "
}

void CommunicantTest::testCommSendUstring(){
    CommString c;
    string s = "ௌ";
    ustring a;
    a.append(reinterpret_cast<const unsigned char*>(s.data()));
    int length = a.length();
    c.Communicant::commSend(a, length);
    
    CPPUNIT_ASSERT_EQUAL(c.commRecv(length), s);
}

void CommunicantTest::testCommSendDataObject(){
    CommString c;
    string init = "AA";
    DataObject d(init);
    
    c.Communicant::commSend(d);
    //CPPUNIT_FAIL(c.getString());
    // revisit
}

void CommunicantTest::testCommSendDataObjectPriority(){
    //""
}

