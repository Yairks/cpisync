/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   CommStringTest.h
 * Author: kaets
 *
 * Created on May 18, 2018, 10:52:33 AM
 */

#ifndef COMMSTRINGTEST_H
#define COMMSTRINGTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CommStringTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CommStringTest);

    CPPUNIT_TEST(testCommStringAndGetString);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testComm);

    CPPUNIT_TEST_SUITE_END();

public:
    CommStringTest();
    virtual ~CommStringTest();
    void setUp();
    void tearDown();

private:
    void testCommStringAndGetString();
    void testGetName();
    void testComm();

};

#endif /* COMMSTRINGTEST_H */

