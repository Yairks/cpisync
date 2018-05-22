/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommunicantTest.h
 * Author: kaets
 *
 * This object tests the Communicant-implemented functions by testing them
 * implemented as a CommString. This precludes that all of Communicant's
 * virtual functions are correctly implemented in CommString, i.e. that the
 * CommString-specific test suite passes.
 * 
 * Created on May 22, 2018, 2:43:39 PM
 */

#ifndef COMMUNICANTTEST_H
#define COMMUNICANTTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "CommString.h"
class CommunicantTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CommunicantTest);

    CPPUNIT_TEST(testCommunicantInitAndTotGettersAndCommSendZZpAndGetTotalTime);
    CPPUNIT_TEST(testResetCommCountersAndByteGettersAndGetResetTime);
    CPPUNIT_TEST(testCommunicantGetName);
    CPPUNIT_TEST(testEstablishModRecv);
    CPPUNIT_TEST(testEstablishModSend);
    CPPUNIT_TEST(testCommSendUstring);
    CPPUNIT_TEST(testCommSendDataObject);
    CPPUNIT_TEST(testCommSendDataObjectPriority);
    CPPUNIT_TEST_SUITE_END();

public:
    CommunicantTest();
    virtual ~CommunicantTest();
    void setUp();
    void tearDown();

private:
    void testCommunicantInitAndTotGettersAndCommSendZZpAndGetTotalTime();
    void testResetCommCountersAndByteGettersAndGetResetTime();
    void testCommunicantGetName();
    void testEstablishModRecv();
    void testEstablishModSend();
    void testCommSendUstring();
    void testCommSendDataObject();
    void testCommSendDataObjectPriority();

};

#endif /* COMMUNICANTTEST_H */

