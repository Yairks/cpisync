/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommunicantTest.h
 * Author: kaets
 *
 * Created on May 24, 2018, 10:08:52 AM
 */

#ifndef COMMUNICANTTEST_H
#define COMMUNICANTTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CommunicantTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CommunicantTest);
    
    CPPUNIT_TEST(testInitAndTotalTime);
    CPPUNIT_TEST(testBytesAndResetTimeAndResetCommCounters);
    CPPUNIT_TEST(testCommSendAndRecv);
    CPPUNIT_TEST(testEstablishModSendAndSendZZ_p);
    CPPUNIT_TEST(testCommSendUstringBytes);
    CPPUNIT_TEST(testCommSendString);
    CPPUNIT_TEST(testCommSendLong);
    CPPUNIT_TEST(testCommSendUstringNoBytes);
    CPPUNIT_TEST(testCommSendDataObject);
    CPPUNIT_TEST(testCommSendDataObjectPriority);
    CPPUNIT_TEST(testCommSendDataObjectList);
    CPPUNIT_TEST(testCommSendDouble);
    CPPUNIT_TEST(testCommSendByte);
    CPPUNIT_TEST(testCommSendInt);
    CPPUNIT_TEST(testCommRecv_vec_ZZ_p);
    CPPUNIT_TEST(testCommSendVec_ZZ_p);
    CPPUNIT_TEST(testCommRecv_ustring);
    CPPUNIT_TEST(testCommRecv_string);
    CPPUNIT_TEST(testCommRecv_ustring2);
    CPPUNIT_TEST(testCommRecv_DataObject);
    CPPUNIT_TEST(testCommRecv_DataObject_Priority);
    CPPUNIT_TEST(testCommRecv_DoList);
    CPPUNIT_TEST(testCommRecv_double);
    CPPUNIT_TEST(testCommRecv_long);
    CPPUNIT_TEST(testCommRecv_int);
    CPPUNIT_TEST(testCommRecv_byte);
    CPPUNIT_TEST(testCommRecv_ZZ_pAndEstablishModRecv);
    CPPUNIT_TEST(testCommRecv_ZZ);
    CPPUNIT_TEST(testCommRecv_ZZNoArgs);
    
    CPPUNIT_TEST_SUITE_END();

public:
    CommunicantTest();
    virtual ~CommunicantTest();
    void setUp();
    void tearDown();

private:
    // If this fails, there is a problem with the CommDummy class. This test
    // especially shouldn't fail, as the majority of tests depend on these
    // functions.
    void testCommSendAndRecv();
    
    // Requires bytes-communicated and reset-time getters to work as well.
    // If this test fails in conjunction with testBytesAndResetCommCounters,
    // check the getter functions for bytes-communicated and reset-time.
    void testInitAndTotalTime();
    
    // Tests bytes-communicated getters, reset-time getters, and
    // resetCommCounters.
    void testBytesAndResetTimeAndResetCommCounters();
    
    // Tests that establishModSend and commSend(ZZ_p) work correctly.
    void testEstablishModSendAndSendZZ_p();
    void testCommSendUstringBytes();
    void testCommSendString();
    void testCommSendLong();
    void testCommSendUstringNoBytes();
    void testCommSendDataObject();
    void testCommSendDataObjectPriority();
    void testCommSendDataObjectList();
    void testCommSendDouble();
    void testCommSendByte();
    void testCommSendInt();
    void testCommRecv_vec_ZZ_p();
    void testCommSendVec_ZZ_p();
    void testCommRecv_ustring();
    void testCommRecv_string();
    void testCommRecv_ustring2();
    void testCommRecv_DataObject();
    void testCommRecv_DataObject_Priority();
    void testCommRecv_DoList();
    void testCommRecv_double();
    void testCommRecv_long();
    void testCommRecv_int();
    void testCommRecv_byte();
    void testCommRecv_ZZ_pAndEstablishModRecv();
    void testCommRecv_ZZ();
    void testCommRecv_ZZNoArgs();

    

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CommunicantTest, CommunicantTest );


#endif /* COMMUNICANTTEST_H */

