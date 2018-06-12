/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/* 
 * File:   probCPISyncTest.cpp
 * Author: kaets
 * 
 * Created on June 1, 2018, 3:41 PM
 */

#include "CPISyncTest.h"
#include "CPISync.h"
#include "CommDummy.h"
#include "Logger.h"
#include <pthread.h>

CPPUNIT_TEST_SUITE_REGISTRATION(CPISyncTest);

CPISyncTest::CPISyncTest() {
}

CPISyncTest::~CPISyncTest() {
}

void CPISyncTest::setUp(){

}

void CPISyncTest::tearDown(){ 
}

void *server(void *ptr){
    CommDummy server;
    Logger::gLog(Logger::COMM, string((char*) ptr));
    
}

void CPISyncTest::testEgg(){
    pthread_t servThread;
    const char *message = "Server Thread";
    int iret;
    
    iret = pthread_create(&servThread, NULL, server, (void*) message);
    
    CPISync c(256, 8, 16); // make this correct
    CommDummy client;
    list<DataObject*> selfMinusOther;
    list<DataObject*> otherMinusSelf;
    pthread_join(servThread, NULL);
}