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
    
    /*
    const int bufSize = 8192;
    const int amtB = 500;
    const int tooLongSize = bufSize + amtB;
    char tooLong[tooLongSize];
    const char fillA = 'a';
    const char fillB = 'b';
    
    for(int i = 0; i < tooLongSize; i++){
        if(i < bufSize - amtB){
            tooLong[i] = fillA;
        } else {
            tooLong[i] = fillB;
        }
    }
    
    cs.commSend(tooLong, tooLongSize);
    cs.commClose();
    string j = cs.commRecv(tooLongSize );
    */
    
    // not so sure how to test commClose()... above is how i'm currently approaching it
    // essentially, I am trying to send some text that's bigger than the buffer in commString.
    // this text is 8192 (the size of the buffer) 'a's and 500 'b's.
    // before cs.commClose() is called, doing cs.commRecv(tooLongSize) should return the entire buffer, which should
    // just be 'a's, because the 'b's would've exceeded the bounds of the buffer.
    // evidently, i'm going about this the wrong way because cs.commRecv(tooLongSize) returns the entire tooLong
    // string, both before and after cs.commClose().
    
}