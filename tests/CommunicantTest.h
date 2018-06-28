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
    
    CPPUNIT_TEST(testConstruct);
    CPPUNIT_TEST(testBytesAndResetCommCounters);
    CPPUNIT_TEST(testEstablishModAndCommZZ_p);
    CPPUNIT_TEST(testCommUstringBytes);
    CPPUNIT_TEST(testCommString);
    CPPUNIT_TEST(testCommLong);
    CPPUNIT_TEST(testCommUstringNoBytes);
    CPPUNIT_TEST(testCommDataObject);
    CPPUNIT_TEST(testCommDataObjectPriority);
    CPPUNIT_TEST(testCommDataObjectList);
    CPPUNIT_TEST(testCommDouble);
    CPPUNIT_TEST(testCommByte);
    CPPUNIT_TEST(testCommInt);
    CPPUNIT_TEST(testCommVec_ZZ_p);
    CPPUNIT_TEST(testCommZZ);
    CPPUNIT_TEST(testCommZZNoArgs);
    
    CPPUNIT_TEST_SUITE_END();

public:
    CommunicantTest();
    virtual ~CommunicantTest();
    void setUp();
    void tearDown();

private:
    // Tests argument-free construction.
    void testConstruct();
    
    // Tests bytes-communicated-counter getters and resetCommCounters.
    void testBytesAndResetCommCounters();
    
    // Tests that establishMod functions, commSend for ZZ_p, and commRecv for ZZ_p work correctly.
    void testEstablishModAndCommZZ_p();
    void testCommUstringBytes();
    void testCommString();
    void testCommLong();
    void testCommUstringNoBytes();
    void testCommDataObject();
    void testCommDataObjectPriority();
    void testCommDataObjectList();
    void testCommDouble();
    void testCommByte();
    void testCommInt();
    void testCommVec_ZZ_p();
    void testCommZZ_p();
    void testCommZZ();
    void testCommZZNoArgs();

    

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CommunicantTest, CommunicantTest );


#endif /* COMMUNICANTTEST_H */

