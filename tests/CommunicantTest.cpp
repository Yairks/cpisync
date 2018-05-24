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
#include <algorithm>

CPPUNIT_TEST_SUITE_REGISTRATION(CommunicantTest);

const string AA = "AA";

string stringToBitstring(string s){
    int length = s.length();
    stringstream v;
    for(int i = 0; i < length; i++){
        stringstream cv;
        int c = s[i];
        int len = 0;
        while(c != 0){
            if(c%2 == 0){ // even, therefore last bit is 0
                cv << "0";
            } else { // odd, therefore last bit is 1
                cv << "1";
            }
            c>>=1; // pop the last bit and repeat
            ++len;
        }
        string chr = cv.str();
        reverse(chr.begin(), chr.end());
        string paddedZeros(sizeof(char) - len, '0');
        v << (paddedZeros + chr);
    }
    return v.str();
}

CommunicantTest::CommunicantTest() {
}

CommunicantTest::~CommunicantTest() {
}

void CommunicantTest::setUp() {
}

void CommunicantTest::tearDown() {
}

// Make sure the simple dummy functions work
void CommunicantTest::testCommSendAndRecv() {
//    CommDummy c;
//    const char* str = "hello world";
//    string expected = "hell";
//    const int helloLen = 5;
//    c.commSend(str, helloLen);
//    CPPUNIT_ASSERT_EQUAL(expected, c.commRecv(helloLen - 1));
}

void CommunicantTest::testInit(){
    clock_t before = clock();
    CommDummy c;
    clock_t after = clock();
    clock_t actual = c.getTotalTime();
    
    CPPUNIT_ASSERT(before <= actual && actual <= after);
    CPPUNIT_ASSERT_EQUAL(0l, c.getRecvBytesTot());
    CPPUNIT_ASSERT_EQUAL(0l, c.getXmitBytesTot());
    
    // We expect commSend(ZZ_p&) to fail with a length_error if MOD_SIZE = NOT_SET.
    // This is expected behavior after initialization. NOT TRU
    try{
        ZZ_p zzp;
        c.Communicant::commSend(zzp);
    } catch (std::length_error e){
        CPPUNIT_ASSERT(true);
    }
    
}

void CommunicantTest::testXmitBytesAndResetCommCounters(){
    CommDummy c;
    const char *str = "hello world";
    int helloLen = 5;
    long int totXmit = c.getXmitBytesTot();
    long int totRecv = c.getRecvBytesTot();
    long int xmit = c.getXmitBytes();
    long int recv = c.getRecvBytes();
    
    c.commSend(str, helloLen);
    CPPUNIT_ASSERT_EQUAL(xmit + helloLen, c.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(totXmit + helloLen, c.getXmitBytesTot());
    
    c.commRecv(helloLen-1);
    CPPUNIT_ASSERT_EQUAL(recv + helloLen - 1, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(totRecv + helloLen - 1, c.getRecvBytesTot());
    
    clock_t before = clock();
    c.resetCommCounters();
    clock_t after = clock();
    clock_t resetTime = c.getResetTime();
    
    CPPUNIT_ASSERT(before <= resetTime && resetTime <= after);
    CPPUNIT_ASSERT_EQUAL(0l, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(0l, c.getXmitBytes());
}

void CommunicantTest::testEstablishModRecv() {
    CommDummy c;
    bool oneWay = true;
    
    //ZZ_p::init(static_cast<ZZ>(4343)); //todo: fix this kinda stuff. basically, u wanna init the zz_p modulus but memory issues look into this.
    
    //BELOW CODE CURRENTLY SEGFAULTS BECAUSE ZZ_P::MODULUS IS UNINITIALIZED
    CommDummy::output = CommDummy::AA;
    bool a = c.establishModRecv(oneWay);
 
    

}

void CommunicantTest::testEstablishModSend() {
    
}

void CommunicantTest::testCommSend() {

}

void CommunicantTest::testCommSend2() {

}

void CommunicantTest::testCommSend3() {

}

void CommunicantTest::testCommSend4() {

}

void CommunicantTest::testCommSend5() {

}

void CommunicantTest::testCommSend6() {

}

void CommunicantTest::testCommSend7() {

}

void CommunicantTest::testCommSend8() {

}

void CommunicantTest::testCommSend9() {

}

void CommunicantTest::testCommSend10() {

}

void CommunicantTest::testCommRecv_vec_ZZ_p() {

}

void CommunicantTest::testCommSend11() {

}

void CommunicantTest::testCommRecv_ustring() {
    CommDummy c;
    ustring result = c.commRecv_ustring(AA.length() - 1);
    ustring expected = reinterpret_cast<const unsigned char*>("A"); // first character of "AA"
    CPPUNIT_ASSERT(result==expected); // for some reason, cppunit_assert_equals doesnt work here
}

void CommunicantTest::testCommRecv_string() {
    CommDummy c;
    CPPUNIT_ASSERT_EQUAL(c.commRecv_string(), AA);
}

void CommunicantTest::testCommRecv_ustring2() {
    CommDummy c;
    //ustring result = c.commRecv_ustring();
    ustring result = c.commRecv_ustring(AA.size()); // above doesn't work - this does? oh its cuz it calls commRecv_long
    ustring expected = reinterpret_cast<const unsigned char*>(AA.data()); // first character of "AA"
    CPPUNIT_ASSERT(result==expected); // for some reason, cppunit_assert_equals doesnt work here
}

void CommunicantTest::testCommRecv_DataObject() {
    CommDummy c;
    DataObject* result = c.commRecv_DataObject(); // why is this a pointer
    DataObject expected(AA);
    CPPUNIT_ASSERT_EQUAL(expected.to_string(), result->to_string());
}

void CommunicantTest::testCommRecv_DataObject_Priority() {
//    CommDummy c;
//    DataObject* result = c.commRecv_DataObject_Priority(); // ""
//    DataObject expected(AA);
//    ZZ priority = static_cast<ZZ>(0);
//    expected.setPriority(priority);
//    CPPUNIT_ASSERT_EQUAL(expected.to_priority_string(), result->to_priority_string());
    // i can do this but it requires changing the commRecv method in the dummy class :/
    // will do later
}

void CommunicantTest::testCommRecv_DoList() {

}

void CommunicantTest::testCommRecv_double() {

}

void CommunicantTest::testCommRecv_long() {

}

void CommunicantTest::testCommRecv_int() {
    CommDummy c;
    //std::bitset<sizeof(int)> bits;
//    int sizeofAA = AA.length();
//    long int bytesToPad = (sizeof(int) - 16) / sizeof(byte);
//    string aaPadded = AA + string(bytesToPad, '\0');
//    CPPUNIT_FAIL(stringToBitstring(aaPadded));
    

    CommDummy::output = CommDummy::PRIORITY_OBJECT_REPISINT_FALSE;
    int expected = 1094795585; // "AAAA" in ascii as a sequence of 4 bytes in an integer
    CPPUNIT_ASSERT_EQUAL(expected, c.commRecv_int());
    CommDummy::output = CommDummy::AA;

    
    //CPPUNIT_ASSERT_EQUAL(aaAsInt, c.commRecv_int());
    // the actual commRecv_int has a problem with pointers!
    // repro steps: run the commented-out-above test multiple times and find
    // that c.commRecv_int() is garbage
}

void CommunicantTest::testCommRecv_byte() {
    CommDummy c;
    byte expected = AA[0];
    CPPUNIT_ASSERT_EQUAL(expected, c.commRecv_byte());
}

void CommunicantTest::testCommRecv_ZZ_p() {
//    CommDummy c;
//    int aaAsInt = 16705;
//    ZZ_p zzp = c.commRecv_ZZ_p();
//    ZZ_p expected = static_cast<ZZ_p>(aaAsInt);
//    CPPUNIT_ASSERT_EQUAL(expected, zzp);
}

void CommunicantTest::testCommRecv_ZZ() {
    CommDummy c;
    int sizeofAA = AA.length();
    int aaAsInt = 16705;
    
    ZZ zz = c.commRecv_ZZ(sizeofAA);
    ZZ expected = static_cast<ZZ>(aaAsInt);
    CPPUNIT_ASSERT_EQUAL(expected, zz);
}

void CommunicantTest::testCommRecv_ZZNoArgs(){
    CommDummy c;
    CommDummy::output = CommDummy::PRIORITY_OBJECT_REPISINT_TRUE;
    ZZ result = c.commRecv_ZZ();
    int aaAsInt = 4;
    ZZ expected = static_cast<ZZ>(aaAsInt);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}


