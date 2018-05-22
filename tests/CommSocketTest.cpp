/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommSocketTest.cpp
 * Author: kaets
 *
 * Created on May 22, 2018, 11:00:24 AM
 */

#include "CommSocketTest.h"
#include "CommSocket.h"
#include <pthread.h>

CPPUNIT_TEST_SUITE_REGISTRATION(CommSocketTest);

CommSocket* listener;
CommSocket* connector;

CommSocketTest::CommSocketTest() {
    int port = 4567;
    string host = "localhost";
    listener = new CommSocket(port, host);
    connector = new CommSocket(port, host);
}

CommSocketTest::~CommSocketTest(){
    delete listener;
    delete connector;
}


void CommSocketTest::setUp() {
}

void CommSocketTest::tearDown() {
}

void* startListener(void* ){
    listener->commListen();
}

void CommSocketTest::testCommSocket() {
    int desiredPort = 4567;
    CPPUNIT_ASSERT_EQUAL(desiredPort, connector->getPort());
}
//
void CommSocketTest::testCommListenAndConnect() {
    // Start a thread that initializes a socket in localhost and has it listening
    // on port 4567
    pthread_t t1; 
    pthread_create(&t1, NULL, startListener, NULL);
    
    // Connect to the listener
    connector->commConnect();
    
    // join the listening thread to the main thread, so that when listener connects
    // and the thread continues executing, we know that both the connect and listen
    // functions worked.
    pthread_join(t1, NULL);
    CPPUNIT_ASSERT_MESSAGE("listen and connect completed successfully", true);
}

void CommSocketTest::testCommClose() {
//    CommSocket commSocket;
//    commSocket.commClose();
//    if (true /*check result*/) {
//        CPPUNIT_ASSERT(false);
//    }
}

void CommSocketTest::testCommSendAndRecv() {
//    const char* toSend;
//    const int numBytes;
//    CommSocket commSocket;
//    commSocket.commSend(toSend, numBytes);
//    if (true /*check result*/) {
//        CPPUNIT_ASSERT(false);
//    }
}
//
//void CommSocketTest::testCommRecv() {
//    long numBytes;
//    CommSocket commSocket;
//    string result = commSocket.commRecv(numBytes);
//    if (true /*check result*/) {
//        CPPUNIT_ASSERT(false);
//    }
//}
//
