/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   LoggerTest.h
 * Author: kaets
 *
 * Created on May 17, 2018, 1:49:25 PM
 */

#ifndef LOGGERTEST_H
#define LOGGERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class LoggerTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(LoggerTest);

    CPPUNIT_TEST(testError);
    CPPUNIT_TEST(testErrorQuit);
    CPPUNIT_TEST(testGLog);

    CPPUNIT_TEST_SUITE_END();

public:
    LoggerTest();
    virtual ~LoggerTest();
    void setUp();
    void tearDown();

private:
    void testError();
    void testErrorQuit();
    void testGLog();
    
};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( LoggerTest, LoggerTest );

#endif /* LOGGERTEST_H */
