/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/* 
 * File:   probCPISyncTest.cpp
 * Author: kaets
 * 
 * Created on June 1, 2018, 3:41 PM
 */

#include "CPISyncTest.h"
#include "CPISync.h"
#include "CPISync_HalfRound.h"
#include "CPISync_ExistingConnection.h"
#include "CommDummy.h"
#include "CommString.h"
#include "Logger.h"
#include <pthread.h>
#include "GenSync.h"
#include "Auxiliary.h"

CPPUNIT_TEST_SUITE_REGISTRATION(CPISyncTest);

template <typename T>
T &operator++(T& curr) {
    curr = (T)(((int) (curr) + 1));
    return curr;
}
CPISync* c = NULL;

CPISyncTest::CPISyncTest() {
}

CPISyncTest::~CPISyncTest() {
}

void CPISyncTest::setUp(){
}

void CPISyncTest::tearDown(){ 
}

void *server(void *ptr){
//    CommString servComm;
//    servComm.Communicant::establishModSend(true);
//    //servComm.Communicant::commSend(ZZ_p::modulus());
//    servComm.Communicant::commSend((byte) 1);
//    servComm.Communicant::commSend(5l);
//    servComm.Communicant::commSend(20l);
//    servComm.Communicant::commSend(16);
//    
//    servComm.Communicant::commSend(4l);
//    vec_ZZ_p vzzp;
//    
//    vzzp.append(static_cast<ZZ_p>(123));
//    vzzp.append(static_cast<ZZ_p>(456));
//    vzzp.append(static_cast<ZZ_p>(789));
//    vzzp.append(static_cast<ZZ_p>(606));
//    servComm.Communicant::commSend(vzzp);
//    
//    
//    Logger::gLog(Logger::COMM, string((char*) ptr));
//    
//    list<DataObject*> selfMinusOther;
//    list<DataObject*> otherMinusSelf;
//    c->SyncServer(&servComm, selfMinusOther, otherMinusSelf);
}

void CPISyncTest::testEgg(){
//    c = new CPISync(5, 8, 16); // make this correct
//    CPISync d(5, 8, 16);
////    pthread_t servThread;
////    const char *message = "Server Thread";
////    int iret;
////    
////    iret = pthread_create(&servThread, NULL, server, (void*) message);
////    
//////    CPISync c(256, 8, 16); // make this correct
////    CommDummy client;
//    list<DataObject*> selfMinusOther;
//    list<DataObject*> otherMinusSelf;
//////    pthread_join(servThread, NULL);
//    CommString servComm;
//    servComm.Communicant::establishModSend(true);
//    servComm.Communicant::commSend((byte) 1);
//    servComm.Communicant::commSend(5l);
//    servComm.Communicant::commSend(8l);
//    servComm.Communicant::commSend(16);
//    
//    servComm.Communicant::commSend(6l);
//    vec_ZZ_p vzzp;
//////    
//    vzzp.append(static_cast<ZZ_p>(123));
//    vzzp.append(static_cast<ZZ_p>('\x7a'));
//    vzzp.append(static_cast<ZZ_p>('\x79'));
//    vzzp.append(static_cast<ZZ_p>('\x78'));
//    vzzp.append(static_cast<ZZ_p>('\x77'));
//    vzzp.append(static_cast<ZZ_p>('\x76'));
//    vzzp.append(static_cast<ZZ_p>('\x75'));
//
////    vzzp.append(static_cast<ZZ_p>(1));
////    vzzp.append(static_cast<ZZ_p>(2));
////    vzzp.append(static_cast<ZZ_p>(3));
////    vzzp.append(static_cast<ZZ_p>(4));
////    vzzp.append(static_cast<ZZ_p>(5));
////    vzzp.append(static_cast<ZZ_p>(6));
////    
//    servComm.Communicant::commSend(vzzp);
//    DataObject e[] = {DataObject(string("\x6F")),
//                      DataObject(string("\x7A")),
//                      DataObject(string("\x79")),
//                      DataObject(string("\x78")),
//                      DataObject(string("\x77")),
//                      DataObject(string("\x76")),
//                      DataObject(string("\x75"))};
////    DataObject d[] = {DataObject(string("\x1")),
////                      DataObject(string("\x1")),
////                      DataObject(string("\x1")),
////                      DataObject(string("\x1")),
////                      DataObject(string("\x1")),
////                      DataObject(string("\x1"))};
//    int dLen = 6;
//    
//    for(int i = 0; i < dLen; i++){
//        c->addElem(&(e[i]));
//    }
//    
//    bool r = c->SyncServer(&servComm, selfMinusOther, otherMinusSelf);
//
//
//        
//    //c->SyncServer(&servComm, selfMinusOther, otherMinusSelf);

}

void CPISyncTest::testHalfRoundSimple(){
    CPISync_HalfRound client(5, 8, 16);
    CPISync_HalfRound server(5, 8, 16);
    
    CommString comm;
    
    list<DataObject*> selfMinusOther;
    list<DataObject*> otherMinusSelf;
    
    bool succ = client.SyncClient(&comm, selfMinusOther, otherMinusSelf);
    succ &= server.SyncServer(&comm, selfMinusOther, otherMinusSelf);
    
    CPPUNIT_ASSERT(succ);
}

void CPISyncTest::testHalfRoundConnect(){
    CPISync_HalfRound client(5, 8, 16);
    CPISync_HalfRound server(5, 8, 16);
    
    CommString comm;
    
    list<DataObject*> selfMinusOther;
    list<DataObject*> otherMinusSelf;
    
    DataObject d(string("\x12"));
    
    // single element add and delete
    bool succ = client.addElem(&d);
    CPPUNIT_ASSERT(succ);
    CPPUNIT_ASSERT_EQUAL(string("\x12 [hash=18], "), client.printElem());
    CPPUNIT_ASSERT_EQUAL(1l, client.getNumElem());
    
 //   succ = client.delElem(&d);
 //   CPPUNIT_ASSERT(succ);
 //   CPPUNIT_ASSERT_EQUAL(string(""), client.printElem());
 //   CPPUNIT_ASSERT_EQUAL(0l, client.getNumElem());
    
 //   I don't think the above code should segfault
    
 //   Below code only works assuming that \x12 is still an element that hasn't 
 //   been deleted. Uncomment the below lines once the above code runs fine.
    DataObject clientItems[] = {/*DataObject(string("\x12")),*/
                                DataObject(string("\x34")),
                                DataObject(string("\x56")),
                                DataObject(string("\x78"))};
    int clientLength = /*4*/3;
    for(int i = 0; i < clientLength; i++)
        succ &= client.addElem(&(clientItems[i]));
    
    CPPUNIT_ASSERT(succ);
    //fix this CPPUNIT_ASSERT_EQUAL(string("\x12 [hash=18], \x34 [hash=52], \x56 [hash=86], \x78 [hash=120], "), client.printElem());
}
    //TODO: make a failure test for data


void CPISyncTest::testHalfRoundData() {
    CPISync_HalfRound client(5, 8, 16);
    CPISync_HalfRound server(5, 8, 16);
    
    CommString comm;
    
    list<DataObject*> selfMinusOtherC, selfMinusOtherS;
    list<DataObject*> otherMinusSelfC, otherMinusSelfS;
    
    int clientLength = 8;
    DataObject clientSet[] = {DataObject(string("\x92")),
                      DataObject(string("\x6F")),
                      DataObject(string("\x7A")),
                      DataObject(string("\x79")),
                      DataObject(string("\x78")),
                      DataObject(string("\x77")),
                      DataObject(string("\x76")),
                      DataObject(string("\x75"))};
    
    int serverLength = 6;
    DataObject serverSet[] = {DataObject(string("\x6F")),
                      DataObject(string("\x7A")),
                      DataObject(string("\x79")),
                      DataObject(string("\x22")),
                      DataObject(string("\x54")),
                      DataObject(string("\x75"))};
    
    list<DataObject*> expectedSelfMinusOtherC = {&clientSet[0], &clientSet[4], &clientSet[5], &clientSet[6]};
    list<DataObject*> expectedOtherMinusSelfS = expectedSelfMinusOtherC; // otherMinusSelf for server is the same as selfMinusOther for client
    list<DataObject*> expectedOtherMinusSelfC = {&serverSet[3], &serverSet[4]};
    list<DataObject*> expectedSelfMinusOtherS = expectedOtherMinusSelfC; // similar logic to that above
    
    for(int i = 0; i < clientLength; i++)
        client.addElem(&clientSet[i]);
    for(int j = 0; j < serverLength; j++)
        server.addElem(&serverSet[j]);
    
    bool succClient = client.SyncClient(&comm, selfMinusOtherC, otherMinusSelfC);
    bool succServer = server.SyncServer(&comm, selfMinusOtherS, otherMinusSelfS);
    
    CPPUNIT_ASSERT_MESSAGE("SyncClient is reported to have completed successfully...", succClient);
    
//    for(list<DataObject*>::iterator i = selfMinusOtherC.begin(); i == selfMinusOtherC.end(); i++){
//        Logger::gLog(Logger::COMM, );
//        CPPUNIT_FAIL("lamo");
//    }
    Logger::gLog(Logger::COMM, toStr(otherMinusSelfS.size()));
    
    //Logger::gLog(Logger::COMM, toStr(selfMinusOtherC) + ", " + toStr(expectedSelfMinusOtherC));
    //CPPUNIT_ASSERT_EQUAL_MESSAGE("selfMinusOther for the client is correct...", selfMinusOtherC, expectedSelfMinusOtherC);
    
}

void CPISyncTest::testSendAllElem() {
    CPISync client(5, 8, 16);
    CPISync server(5, 8, 16);
    
    CommString comm;
    
    list<DataObject*> selfMinusOther;

    DataObject clientSet[] = {DataObject(string("\x92")),
                  DataObject(string("\x6F")),
                  DataObject(string("\x7A")),
                  DataObject(string("\x79")),
                  DataObject(string("\x78")),
                  DataObject(string("\x77")),
                  DataObject(string("\x76")),
                  DataObject(string("\x75"))};
    
    for(DataObject d : clientSet)
        client.addElem(&d);
    
    client.sendAllElem(comm, selfMinusOther);
}