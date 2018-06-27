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

// A constant used frequently throughout the testing suite
const string AA = "AA";

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
    CommDummy c;
    CommDummy::OUTPUTS options[] = {CommDummy::AA,
                                    CommDummy::INT_FOUR,
                                    CommDummy::INT_FIVE,
                                    CommDummy::LONG_FOUR,
                                    CommDummy::DOPRIORITY_FOUR_AA,
                                    CommDummy::SYNC_OK,
                                    CommDummy::SYNC_FAIL};
    
    for(CommDummy::OUTPUTS o : options) {
        CommDummy::output = o;
        string expected;
        
        switch(o) {
            case CommDummy::AA:
                expected = string(2, '\x41');
                break;
            case CommDummy::INT_FOUR:
                expected = string(1, '\x04') + string(sizeof(int) - 1, '\0');
                break;
            case CommDummy::INT_FIVE:
                expected = string(1, '\x05') + string(sizeof(int) - 1, '\0');
                break;
            case CommDummy::LONG_FOUR:
                expected = string(1, '\x04') + string(sizeof(long) - 1, '\0');
                break;
            case CommDummy::DOPRIORITY_FOUR_AA:
                expected = "4," + string(2, '\x41');
                break;
            case CommDummy::SYNC_OK:
                expected = string(1, (char) SYNC_OK_FLAG);
                break;
            case CommDummy::SYNC_FAIL:
                expected = string(1, (char) SYNC_FAIL_FLAG);
                break;
        }
                
        // For this particular communicant, commRecv(int numBytes) always
        // returns a fixed string, regardless of what numBytes is set to.
        // This is arguably the simplest way of implementing a communicant.
        // Nevertheless, recvBytes is still incremented by numBytes, which
        // is the expected behavior for a communicant. The below tests
        // acknowledge these behaviors.
        string result = c.commRecv(0);
        CPPUNIT_ASSERT_EQUAL(expected, result);
    }
    
    string str = "hello world";
    
    // Similar to commRecv, commSend is designed to be as simple as possible.
    // commSend simply appends str to a stringstream, which can be retrieved
    // using getRecv. getRecv simply returns the stringstream.str(). It is
    // impossible to just set a string to the most recent commSend, since many
    // other commSend functions are expected to call the standard commSend
    // function multiple times, so the next simplest way to implement the
    // standard commSend is with a stringstream.
    c.commSend(str.data(), 0);
    
    string result = c.getRecv();
    CPPUNIT_ASSERT_EQUAL(str, result);
}

void CommunicantTest::testInitAndTotalTime() {
    const long int none = 0;
        
    // We expect that the createTime variable is set to the time of the object's
    // creation. Since we cannot record the exact time we expect the object to
    // be created, we do the next best thing: record the time immediately before
    // and after the communicant's creation and assert that the creation time
    // reported by the communicant is in between these two values.
    clock_t before = clock();
    CommDummy c;
    clock_t after = clock();
    clock_t actualInit = c.getTotalTime();
    
    CPPUNIT_ASSERT(before <= actualInit && actualInit <= after);
    
    // We expect the initialization to call resetCommCounters, so we check to
    // make sure that resetTime, xferBytes, and recvBytes are set appropriately.
    clock_t actualReset = c.getResetTime();

    CPPUNIT_ASSERT_EQUAL(none, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(none, c.getXmitBytes());
    CPPUNIT_ASSERT(before <= actualReset && actualReset <= after);
    
    // We also expect the initialization to set xferBytesTot and recvBytesTot
    // to zero as well.
    CPPUNIT_ASSERT_EQUAL(none, c.getRecvBytesTot());
    CPPUNIT_ASSERT_EQUAL(none, c.getXmitBytesTot());
}

void CommunicantTest::testBytesAndResetTimeAndResetCommCounters() {
    CommDummy c;
    string str = "hello world";
    int strLength = str.size();
    const long int none = 0;
    
    // Record original bytes-communicated values. While these should be set to
    // zero, this requirement is to be tested with the init test. We are just
    // checking that the getter methods correctly report the changes in
    // transmitted bytes.
    long int totXmit = c.getXmitBytesTot();
    long int totRecv = c.getRecvBytesTot();
    long int xmit = c.getXmitBytes();
    long int recv = c.getRecvBytes();
    
    c.commSend(str.data(), strLength);
    
    // Check that the send values incremented correctly.
    CPPUNIT_ASSERT_EQUAL(xmit + strLength, c.getXmitBytes());
    CPPUNIT_ASSERT_EQUAL(totXmit + strLength, c.getXmitBytesTot());
    
    c.commRecv(strLength);
    
    // Check that the receive values incremented correctly.
    CPPUNIT_ASSERT_EQUAL(recv + strLength, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(totRecv + strLength, c.getRecvBytesTot());
    
    // Check that the reset worked accordingly.
    clock_t before = clock();
    c.resetCommCounters();
    clock_t after = clock();
    clock_t resetTime = c.getResetTime();
    
    CPPUNIT_ASSERT(before <= resetTime && resetTime <= after);
    
    CPPUNIT_ASSERT_EQUAL(none, c.getRecvBytes());
    CPPUNIT_ASSERT_EQUAL(none, c.getXmitBytes());
}

void CommunicantTest::testEstablishModSendAndSendZZ_p() {
    CommDummy c;
    
    // Set the ZZ_p modulus to 4;
    int mod = 4;
    ZZ init = static_cast<ZZ>(mod);
    ZZ_p::init(init);
    
    // Tests that everything works with oneWay set to true.
    bool oneWay = true;
    bool succ = c.establishModSend(oneWay);
    CPPUNIT_ASSERT(succ);
    string res = c.getRecv();
    string expected = string(1, '\x01') + string(1, '\x04');
    CPPUNIT_ASSERT_EQUAL(expected, res);
    
    // Resets the recv stringstream.
    c.resetRecv();
    
    // Tests that everything works with oneWay set to false.
    oneWay = false;
    // When oneWay is false, succ should be true iff commRecv_byte() != SYNC_FAIL_FLAG
    CommDummy::output = CommDummy::SYNC_OK;
    succ = c.establishModSend(oneWay);
    res = c.getRecv();
    
    CPPUNIT_ASSERT(succ);
    CPPUNIT_ASSERT_EQUAL(expected, res);
    
    c.resetRecv();
    
    CommDummy::output = CommDummy::SYNC_FAIL;
    succ = c.establishModSend(oneWay);
    res = c.getRecv();
    
    CPPUNIT_ASSERT(!succ);
    CPPUNIT_ASSERT_EQUAL(expected, res);
    
    c.resetRecv();
    
    // With a modulus set, we can now test sending a ZZ_p object.
    ZZ_p toSend = static_cast<ZZ_p>(543);
    
    // Ensure that the modulus size is also transmitted.
    int before = c.getXmitBytes();
    c.Communicant::commSend(toSend);
    int after = c.getXmitBytes();
    int expectedInc = ZZ_p::ModulusSize();
    
    // 543 mod 4 is 3.
    expected = "\3";
    res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
    CPPUNIT_ASSERT_EQUAL(before + expectedInc, after);
    
}

void CommunicantTest::testCommSendUstringBytes() {
    CommDummy c;
    ustring us = reinterpret_cast<const unsigned char*>(AA.data());
    int usLen = us.size();
    
    // Check that sending a ustring correctly invokes commSend(const char *, numBytes)
    long int before = c.getXmitBytes();
    c.Communicant::commSend(us, usLen);
    long int after = c.getXmitBytes();
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(AA, res);
    CPPUNIT_ASSERT_EQUAL(before + usLen, after);   
}

void CommunicantTest::testCommSendString() {
    CommDummy c;
    c.Communicant::commSend(AA);
    string aaLength = "\2";
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(aaLength + AA, res);
}

void CommunicantTest::testCommSendLong() {
    CommDummy c;
    long int toSend = 65;
    
    // Ensure that commSend(ustring, int) is called by checking the delta in
    // transmitted bytes.
    int before = c.getXmitBytes();
    c.Communicant::commSend(toSend);
    int after = c.getXmitBytes();
    int expectedInc = sizeof(long);
    
    string expected = "\x41"; // 65 in hex
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
    CPPUNIT_ASSERT_EQUAL(before + expectedInc, after);
}

void CommunicantTest::testCommSendUstringNoBytes() {
    CommDummy c;
    ustring toSend = reinterpret_cast<const unsigned char*>(AA.data());
    c.Communicant::commSend(toSend);
    string aaLength = "\2";
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(aaLength + AA, res);
}

void CommunicantTest::testCommSendDataObject() { 
    CommDummy c;
    DataObject toSend(AA);
    c.Communicant::commSend(AA);
    string aaLength = "\2";
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(aaLength + AA, res);
}

void CommunicantTest::testCommSendDataObjectPriority() { // fix this test so that the repisint doesnt need to be changed
    CommDummy c;
    const bool sendPriority = true;
    
    // Test case where RepIsInt is true
    DataObject::RepIsInt = true;
    DataObject toSend(string("65"));
    string expectedLen = "\x04"; //"5,65" has length 4
    int _priority = 5;
    ZZ priority = static_cast<ZZ>(_priority);
    toSend.setPriority(priority);
    string expected = expectedLen + toSend.to_priority_string();
    c.Communicant::commSend(toSend, sendPriority);
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
    
    c.resetRecv();
    
    // Test case where RepIsInt is false
    DataObject::RepIsInt = false;
    c.Communicant::commSend(toSend, sendPriority);
    expectedLen = "\1";
    expected = expectedLen + toSend.to_string();
    res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
}

void CommunicantTest::testCommSendDataObjectList() {
    DataObject::RepIsInt = false;
    CommDummy c;
    list<DataObject*> lst;
    DataObject vals[] = {DataObject(string("abc")), DataObject(string("def")), DataObject(string("ghi")), DataObject(string("jkl"))};
    char valsLenChar = '\x04'; // length of list is 4 DataObjects long
    char strLenChar = '\x03'; // each string is 3 characters long
    stringstream expected;
    
    expected << valsLenChar;
    
    for(DataObject& d : vals) {
        lst.push_back(&d);
        
        expected << strLenChar << d.to_string();
    }
    
    c.Communicant::commSend(lst);
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(expected.str(), res);
    
}

void CommunicantTest::testCommSendDouble() {
    CommDummy c;
    double toSend = 332343.53125; // an arbitrary test s
    c.Communicant::commSend(toSend);
    
    // The mantissa is 3 bytes, as represented by the first character.
    // The mantissa is 0xA246F1, which is stored in little-endian format
    // regardless of the platform. The exponent is -5, as represented by the
    // last character. Surely enough, (0xA246F1 = 10,634,993) * 2^-5 = 332,343.53125
    string expected = "\x03\xf1\x46\xa2\x05";
    string res = c.getRecv();
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
}

void CommunicantTest::testCommSendByte() {
    CommDummy c;
    byte toSend = '\xff';
    
    // Each byte seems to end in the character \x7f. Not sure why. Shouldn't
    // the expected behavior here be to return just \xff? I would add this as
    // the expected behavior, but I don't want to have a failing test yet, as I
    // am not sure if this actually is the intended behavior.
    //
    // In fact, I think the current behavior is unexpected. commRecv_byte merely
    // receives a string of 1 byte in length. With the current behavior, this
    // leaves the byte \x7f still present and unreceived, which could mess up
    // the reception of other datatypes. For example, consider sending a byte,
    // \xff, and an double, 0.25. Currently, sending this byte results in
    // "\xff\x7f". Sending the double 0.25 would append "\x01\x01\x02" (mantissa
    // has length 1, mantissa is just 1, exp is -2). Calling commRecv_byte will
    // get the first byte, resulting in \x7f\x01\x01\x02 as unreceived. Calling
    // commRecv_double will now result in a segfault or garbage values, as it
    // will interpret \x7f as the length of the mantissa, thus requesting access
    // to 127 bytes, rather than 1 byte. For now, I am leaving the test as
    // passing.
    string expected = "\xff";//\x7f";
    c.Communicant::commSend(toSend);
    string res = c.getRecv();
 
    CPPUNIT_ASSERT_EQUAL(expected, res);
}

void CommunicantTest::testCommSendInt() {
    CommDummy c;
    int toSend = 23456;
    
    // 23456 is 0x5ba0.
    string expected = "\xa0\x5b";
    
    // Ensure that commSend(ustring, int) is called by checking the change in
    // transmitted bytes.
    int before = c.getXmitBytes();
    c.Communicant::commSend(toSend);
    int after = c.getXmitBytes();
    
    string res = c.getRecv();
    int expectedInc = sizeof(int);
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
    CPPUNIT_ASSERT_EQUAL(before + expectedInc, after);
}

void CommunicantTest::testCommSendVec_ZZ_p() {
    CommDummy c;
    
    // Set modulus
    int _modulus = 667;
    ZZ modulus = static_cast<ZZ>(_modulus);
    ZZ_p::init(modulus);
    
    ZZ_p vals[] = {static_cast<ZZ_p>(123), static_cast<ZZ_p>(456), static_cast<ZZ_p>(789)};
    vec_ZZ_p toSend;
    
    for(ZZ_p val : vals)
        toSend.append(val);
    
    c.Communicant::commSend(toSend);
    
    // Should send a ZZ encoding the information in toSend. Expected way of
    // doing this is to reverse iterate through toSend, taking each ZZ_p,
    // accessing its representation as a ZZ, adding 1, and adding that to the
    // product of the ZZ so far and the modulus plus one. result is updated with
    // this value, and reverse iteration continues. The final ZZ is then sent.
    //
    // byte1 = ZZ has length of 4 bytes, byte2-5 is the ZZ described above in
    // little endian.
    string expected = "\x04\xa8\x25\x4a\x03";
    string res = c.getRecv();
    CPPUNIT_ASSERT_EQUAL(expected, c.getRecv());
    
}

void CommunicantTest::testCommRecv_vec_ZZ_p() {
    CommDummy::output = CommDummy::INT_FOUR;
    CommDummy c;
    
    int _modulus = 667;
    ZZ modulus = static_cast<ZZ>(_modulus);
    ZZ_p::init(modulus);
    
    // Should recieve "\x04\x04\x04\x04\x04" and unpack this into
    // 4 objects of (4 % 667) - 1 = 4 objects of 3
    
    vec_ZZ_p res = c.commRecv_vec_ZZ_p();
    vec_ZZ_p::iterator iter = res.begin();
    
    // 4 minus the one that is expected to have been added in the encoding
    // process.
    int expected = 3;
    for(; iter != res.end(); iter++){
        CPPUNIT_ASSERT_EQUAL(static_cast<ZZ>(4-1), rep(*iter));
    }
}


void CommunicantTest::testCommRecv_ustring() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    
    // Check that commRecv_ustring receives "AA", and then removes all but the
    // first one character of that string (leaving just the string "A").
    ustring result = c.commRecv_ustring(AA.length() - 1);
    ustring expected = reinterpret_cast<const unsigned char*>("A");
    
    CPPUNIT_ASSERT(result.compare(expected) == 0); // for some reason, cppunit_assert_equals doesnt work here
}

void CommunicantTest::testCommRecv_string() {
    CommDummy::output = CommDummy::LONG_FOUR;
    CommDummy c;
    int before = c.getRecvBytes();
    string res = c.commRecv_string();
    int after = c.getRecvBytes();
    string expected = string(1, '\x04') + string(sizeof(long) - 1, '\0');
    
    // We expect the received bytes to have gone up by four, plus the size of the long received.
    int expectedInc = 4 + sizeof(long);
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
    CPPUNIT_ASSERT_EQUAL(before + expectedInc, after);
}

void CommunicantTest::testCommRecv_ustring2() { // * might be dependent on long storing >= 4 bytes
    CommDummy::output = CommDummy::LONG_FOUR;
    CommDummy c;
    ustring result = c.commRecv_ustring();
    
    // First, commRecv_ustring() should get a long representing the length of
    // the ustring. In this case, the long returned is 4. Next, a ustring is
    // received and truncated to keep only the first four characters. The first
    // four characters of the long stored are \x04\0\0\0.
    int numBytes = 4;
    ustring expected((const unsigned char *) ("\x04\0\0\0"), numBytes);
    
    CPPUNIT_ASSERT(result.compare(expected) == 0);
}

void CommunicantTest::testCommRecv_DataObject() {
    CommDummy::output = CommDummy::LONG_FOUR;
    CommDummy c;
    DataObject* result = c.commRecv_DataObject();
    DataObject expected(string("\x04"));
    CPPUNIT_ASSERT_EQUAL(expected.to_string(), result->to_string());
}

void CommunicantTest::testCommRecv_DataObject_Priority() { // might have to be tested in conjunction with commRecv_string
    CommDummy::output = CommDummy::DOPRIORITY_FOUR_AA;
    CommDummy c;
    DataObject* result = c.commRecv_DataObject_Priority();
    DataObject expected(AA);
    ZZ priority = static_cast<ZZ>(4);
    expected.setPriority(priority);
    CPPUNIT_ASSERT_EQUAL(expected.to_priority_string(), result->to_priority_string());
}

void CommunicantTest::testCommRecv_DoList() {
    CommDummy::output = CommDummy::LONG_FOUR;
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
    CommDummy::output = CommDummy::LONG_FOUR;
    CommDummy c;
    
    double res = c.commRecv_double();
    
    // We anticipate that we get a mantissa of 4 and exponent of 4.
    // 4 * 2^-4 = 0.25
    double expected = 0.25;
    
    CPPUNIT_ASSERT_EQUAL(expected, res);
}

void CommunicantTest::testCommRecv_long() {
    CommDummy::output = CommDummy::LONG_FOUR;
    CommDummy c;
    long int res = c.commRecv_long();
    long int expected = 4;
    CPPUNIT_ASSERT_EQUAL(expected, res);
}

void CommunicantTest::testCommRecv_int() {
    CommDummy::output = CommDummy::INT_FOUR;
    CommDummy c;
    int expected = 4; 
    int res = c.commRecv_int();
    CPPUNIT_ASSERT_EQUAL(expected, res);
}

void CommunicantTest::testCommRecv_byte() {
    CommDummy::output = CommDummy::AA;
    CommDummy c;
    byte expected = AA[0];
    byte res = c.commRecv_byte();
    CPPUNIT_ASSERT_EQUAL(expected, c.commRecv_byte());
}

void CommunicantTest::testCommRecv_ZZ_pAndEstablishModRecv() {

    // establishModRecv 
    CommDummy c;
        
    bool oneWay = false;
    
    // purposely use different modulus to test failure
    int _modulus = 4;
    ZZ modulus = static_cast<ZZ>(_modulus);
    ZZ_p::init(modulus);
    CommDummy::output = CommDummy::INT_FIVE;

    bool success = c.establishModRecv(oneWay);
    CPPUNIT_ASSERT(!success);
    string expected = string(1, (char) SYNC_FAIL_FLAG);// + string(1, (char) '\x7f'); // " "
    string res = c.getRecv();

    CPPUNIT_ASSERT_EQUAL(expected, res);

    c.resetRecv();

    // use actual modulus to test success
    CommDummy::output = CommDummy::INT_FOUR;

    success = c.establishModRecv(oneWay);
    CPPUNIT_ASSERT(success);
    expected = string(1, (char) SYNC_OK_FLAG);// + string(1, (char) '\x7f'); // unexpected behavior as mentioned above
    res = c.getRecv();
    CPPUNIT_ASSERT_EQUAL(expected, res);
    
    // try with oneWay = true
    
    oneWay = true;
    success = c.establishModRecv(oneWay);
    CPPUNIT_ASSERT(success);
    
    // commRecv_ZZ_p will work iff establishModRecv
    // was successful
    ZZ_p resZZ = c.commRecv_ZZ_p();
    ZZ_p expectedZZ = static_cast<ZZ_p>(4 % 4);
    CPPUNIT_ASSERT_EQUAL(expectedZZ, resZZ);
      
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
    CommDummy::output = CommDummy::INT_FOUR;
    ZZ result = c.commRecv_ZZ();
    int aaAsInt = 4;
    ZZ expected = static_cast<ZZ>(aaAsInt);
    
    CPPUNIT_ASSERT_EQUAL(expected, result);
}


