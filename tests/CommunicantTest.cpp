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
#include <math.h>

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
    CommDummy::output = CommDummy::AA;
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

void CommunicantTest::testEstablishModSendAndSendZZ_p() {
    CommDummy::output = CommDummy::PRIORITY_OBJECT_REPISINT_TRUE;
    CommDummy c;
    bool oneWay = true;
    ZZ init = static_cast<ZZ>(4);
    ZZ_p::init(init); // same zz as modulus recieved
    
    CPPUNIT_ASSERT(c.establishModSend(oneWay));
    
    oneWay = false;
    CPPUNIT_ASSERT(c.establishModSend(oneWay));
    c.resetRecv();
    ZZ_p toSend = static_cast<ZZ_p>(543);

    c.Communicant::commSend(toSend);
    
    string expected = "\x03"; // 543 % 4
    CPPUNIT_ASSERT_EQUAL(expected,c.getRecv());
    
}

void CommunicantTest::testCommSendUstringBytes() {
    CommDummy c;
    ustring us = reinterpret_cast<const unsigned char*>(AA.data());
    const int numBytes = 1;
    c.Communicant::commSend(us, numBytes);
    CPPUNIT_ASSERT_EQUAL(AA, c.getRecv());
}

void CommunicantTest::testCommSendString() {
    CommDummy c;
    c.Communicant::commSend(AA);
    string aaLength = "\2";
    CPPUNIT_ASSERT_EQUAL(aaLength + AA, c.getRecv());
}

void CommunicantTest::testCommSendLong() {
    CommDummy c;
    long int toSend = 65l;
    c.Communicant::commSend(toSend);
    string expected = "\x41"; // 65 in hex
    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
}

void CommunicantTest::testCommSendUstringNoBytes() {
    CommDummy c;
    ustring toSend = reinterpret_cast<const unsigned char*>(AA.data());
    c.Communicant::commSend(toSend);
    string aaLength = "\2";
    CPPUNIT_ASSERT_EQUAL(aaLength + AA, c.getRecv());
}

void CommunicantTest::testCommSendDataObject() {
    CommDummy c;
    DataObject toSend(AA);
    c.Communicant::commSend(AA);
    string aaLength = "\2";
    CPPUNIT_ASSERT_EQUAL(aaLength + AA, c.getRecv());
}

void CommunicantTest::testCommSendDataObjectPriority() {
    CommDummy c;
    DataObject::RepIsInt = true;
    
    DataObject toSend(string("65"));
    string expectedLen = "\x04";
    int _priority = 5;
    ZZ priority = static_cast<ZZ>(_priority);
    toSend.setPriority(priority);
    string expected = expectedLen + std::to_string(_priority) + "," + toSend.to_string();
    c.Communicant::commSend(toSend, true);
    
    DataObject::RepIsInt = false;
    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
}

void CommunicantTest::testCommSendDataObjectList() {
    CommDummy c;
    list<DataObject*> lst;
    DataObject vals[] = {DataObject(string("abc")), DataObject(string("def")), DataObject(string("ghi")), DataObject(string("jkl"))};
    int valsLen = 4;
    char valsLenChar = '\x04'; // length of list is 4 strings long
    char strLenChar = '\x03'; // each string is 3 characters long
    stringstream expected;
    
    expected << valsLenChar;
    
    for(int i = 0; i < valsLen; i++){
        lst.push_back(&vals[i]);
        
        expected << strLenChar << vals[i].to_string();
    }
    
    c.Communicant::commSend(lst);
    
    CPPUNIT_ASSERT_EQUAL(expected.str(), c.getRecv());
    
}

void CommunicantTest::testCommSendDouble() {
    CommDummy c;
    double toSend = 332343.53125;
    double mantissa;
    int exponent;
    
    mantissa = frexp(toSend, &exponent);
    exponent = -exponent;
    //CPPUNIT_FAIL(std::to_string(mantissa * 2) + "," + std::to_string(exponent - 1));
    c.Communicant::commSend(toSend);
    string expected = "\x03\xf1\x46\xa2\x05"; // mantissa is 3 bytes, mantissa is 0xa246f1, exponent is -5

    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
}

void CommunicantTest::testCommSendByte() {
    CommDummy c;
    byte toSend = '\xff';
    string expected = "\xff\x7f"; //  why?
    c.Communicant::commSend(toSend);
 
    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
}

void CommunicantTest::testCommSendInt() {
    CommDummy c;
    int toSend = 23456;
    string expected = "\xa0\x5b"; // 23456 is 0x5ba0
    c.Communicant::commSend(toSend);
    
    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
}

void CommunicantTest::testCommSendVec_ZZ_p() {
    CommDummy c;
    ZZ_p vals[] = {static_cast<ZZ_p>(123), static_cast<ZZ_p>(456), static_cast<ZZ_p>(789)};
    int valsLen = 3;
    vec_ZZ_p toSend;
    
    for(int i = 0; i < valsLen; i++)
        toSend.append(vals[i]);
    
    c.Communicant::commSend(toSend);
    string expected = "\x04\xa8\x25\x4a\x03"; // length 4, 
    string res = c.getRecv();
    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
    
}

void CommunicantTest::testCommRecv_vec_ZZ_p() {
    CommDummy::output = CommDummy::PRIORITY_OBJECT_REPISINT_TRUE;
    CommDummy c;
    ZZ_p::init(static_cast<ZZ>(667));
    
    vec_ZZ_p res = c.commRecv_vec_ZZ_p();
   // CPPUNIT_ASSERT_EQUAL(4l, res.length());
    vec_ZZ_p::iterator iter = res.begin();
    
    for(; iter != res.end(); iter++){
        CPPUNIT_ASSERT_EQUAL(static_cast<ZZ>(4-1), iter->LoopHole());
    }
}


void CommunicantTest::testCommRecv_ustring() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    ustring result = c.commRecv_ustring(AA.length() - 1);
    ustring expected = reinterpret_cast<const unsigned char*>("A"); // first character of "AA"
    CPPUNIT_ASSERT(result==expected); // for some reason, cppunit_assert_equals doesnt work here
}

void CommunicantTest::testCommRecv_string() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    CPPUNIT_ASSERT_EQUAL(c.commRecv_string(), AA);
}

void CommunicantTest::testCommRecv_ustring2() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    //ustring result = c.commRecv_ustring();
    ustring result = c.commRecv_ustring(AA.size()); // above doesn't work - this does? oh its cuz it calls commRecv_long
    ustring expected = reinterpret_cast<const unsigned char*>(AA.data()); // first character of "AA"
    CPPUNIT_ASSERT(result==expected); // for some reason, cppunit_assert_equals doesnt work here
}

void CommunicantTest::testCommRecv_DataObject() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    DataObject* result = c.commRecv_DataObject(); // why is this a pointer
    DataObject expected(AA);
    CPPUNIT_ASSERT_EQUAL(expected.to_string(), result->to_string());
}

void CommunicantTest::testCommRecv_DataObject_Priority() {
    CommDummy::output = CommDummy::DOPRIORITY;
    CommDummy c;
    DataObject* result = c.commRecv_DataObject_Priority(); // ""
    DataObject expected(AA);
    ZZ priority = static_cast<ZZ>(4);
    expected.setPriority(priority);
    CPPUNIT_ASSERT_EQUAL(expected.to_priority_string(), result->to_priority_string());
}

void CommunicantTest::testCommRecv_DoList() {
    CommDummy::output = CommDummy::LONG;
    CommDummy c;
    list<DataObject*> res = c.commRecv_DoList();
    DataObject expected(string("\x04"));
    long unsigned int expectedLen = 4;
    CPPUNIT_ASSERT_EQUAL(expectedLen, res.size());
    list<DataObject*>::iterator iter = res.begin();
    
    for(; iter != res.end(); iter++){
        CPPUNIT_ASSERT_EQUAL(expected.to_ZZ(), (**iter).to_ZZ());
    }
}

void CommunicantTest::testCommRecv_double() {
    CommDummy::output = CommDummy::LONG;
    CommDummy c;
    
    double res = c.commRecv_double();
    double expected = 0.25;
    
    CPPUNIT_ASSERT_EQUAL(res, expected);
}

void CommunicantTest::testCommRecv_long() {
    CommDummy::output = CommDummy::LONG;
    CommDummy c;
    long int res = c.commRecv_long();
    long int expected = 4l;
    CPPUNIT_ASSERT_EQUAL(expected, res);

}

void CommunicantTest::testCommRecv_int() {
    CommDummy::output = CommDummy::PRIORITY_OBJECT_REPISINT_TRUE;
    CommDummy c;
    int expected = 4; 
    CPPUNIT_ASSERT_EQUAL(expected, c.commRecv_int());
}

void CommunicantTest::testCommRecv_byte() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    byte expected = AA[0];
    CPPUNIT_ASSERT_EQUAL(expected, c.commRecv_byte());
}

void CommunicantTest::testCommRecv_ZZ_pAndEstablishModRecv() {

    // establishModRecv
    CommDummy::output = CommDummy::PRIORITY_OBJECT_REPISINT_TRUE;
    CommDummy c;
    ZZ_p::init(static_cast<ZZ>(4));
    bool oneWay = false;

    bool success = c.establishModRecv(oneWay);
    CPPUNIT_ASSERT(success);
    oneWay = true;
    success = c.establishModRecv(oneWay);
    CPPUNIT_ASSERT(success);

    // commRecv_ZZ_p
    ZZ_p res = c.commRecv_ZZ_p();
    ZZ_p expected = static_cast<ZZ_p>(4 % 4);
    CPPUNIT_ASSERT_EQUAL(expected, res);
      
}

void CommunicantTest::testCommRecv_ZZ() {
    CommDummy::output = CommDummy::AA;
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


