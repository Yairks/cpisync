/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommSocketTest.h
 * Author: kaets
 *
 * Created on May 22, 2018, 11:00:24 AM
 */

#ifndef COMMSOCKETTEST_H
#define COMMSOCKETTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CommSocketTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CommSocketTest);

    CPPUNIT_TEST(testCommSocket);
    CPPUNIT_TEST(testCommListenAndConnect);
    CPPUNIT_TEST(testCommSendAndRecv);
    CPPUNIT_TEST(testCommClose);

    CPPUNIT_TEST_SUITE_END();

public:
    CommSocketTest();
    virtual ~CommSocketTest();
    void setUp();
    void tearDown();

private:
    void testCommSocket();
    void testCommListenAndConnect();
    void testCommSendAndRecv();
    void testCommClose();

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( CommSocketTest, CommSocketTest );

#endif /* COMMSOCKETTEST_H */

