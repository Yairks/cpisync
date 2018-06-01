/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommStringTest.cpp
 * Author: kaets
 *
 * Created on May 18, 2018, 10:52:33 AM
 */

#include "CommStringTest.h"
#include "CommString.h"
#include "Auxiliary.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CommStringTest);

CommStringTest::CommStringTest() {
}

CommStringTest::~CommStringTest() {
}

void CommStringTest::setUp() {
}

void CommStringTest::tearDown() {
}

void CommStringTest::testCommStringAndGetString() {
    const string initial = "AA";
    const string initial_b64 = "?EJ=";
    
    // true case
    bool base64 = true;
    CommString cs(initial_b64, base64);

    CPPUNIT_ASSERT_EQUAL(initial, cs.getString());
    
    // false case
    
    base64 = false;
    CommString ds(initial, base64);
    
    CPPUNIT_ASSERT_EQUAL(initial, ds.getString());
    
    
}

void CommStringTest::testGetName() {
    CommString cs;
    const string name = "CommString";
    CPPUNIT_ASSERT_EQUAL(name, cs.getName());
}

void CommStringTest::testComm(){
    const string toSend = "Test String";
    CommString cs;
    
    cs.commConnect(); // doesn't need to be tested since it does nothing and is really trivial
    cs.commListen(); // " "
    
    const long int sendLen = 4;
    cs.commSend(toSend.data(), sendLen);
    
    CPPUNIT_ASSERT_EQUAL_MESSAGE("XmitBytes has been set correctly...", sendLen, cs.getXmitBytes());
    
    string expected = "Tes";
    string expected2 = "t";
    
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Send and receive worked correctly pt 1...", expected, cs.commRecv(sendLen - 1));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Send and receive worked correctly pt 2...", expected2, cs.commRecv(sendLen - 3));
    
    cs.commClose(); // " " but only because the stringstream buffer is constantly synchronized with its ostream
    
}