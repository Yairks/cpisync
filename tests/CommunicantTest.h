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
    
    CPPUNIT_TEST(testInit);
    CPPUNIT_TEST(testXmitBytesAndResetCommCounters);
    CPPUNIT_TEST(testCommSendAndRecv);
    CPPUNIT_TEST(testEstablishModSend);
    CPPUNIT_TEST(testCommSendUstringBytes);
    CPPUNIT_TEST(testCommSendString);
    CPPUNIT_TEST(testCommSend3);
    CPPUNIT_TEST(testCommSend4);
    CPPUNIT_TEST(testCommSend5);
    CPPUNIT_TEST(testCommSend6);
    CPPUNIT_TEST(testCommSend7);
    CPPUNIT_TEST(testCommSend8);
    CPPUNIT_TEST(testCommSend9);
    CPPUNIT_TEST(testCommSend10);
    CPPUNIT_TEST(testCommRecv_vec_ZZ_p);
    CPPUNIT_TEST(testCommSend11);
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
    void testInit();
    void testCommSendAndRecv();
    void testXmitBytesAndResetCommCounters();
    void testEstablishModSend();
    void testCommSendUstringBytes();
    void testCommSendString();
    void testCommSend3();
    void testCommSend4();
    void testCommSend5();
    void testCommSend6();
    void testCommSend7();
    void testCommSend8();
    void testCommSend9();
    void testCommSend10();
    void testCommRecv_vec_ZZ_p();
    void testCommSend11();
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

