/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   LoggerTest.cpp
 * Author: kaets
 *
 * Created on May 17, 2018, 1:49:25 PM
 */

#include "LoggerTest.h"
#include "Logger.h"


CPPUNIT_TEST_SUITE_REGISTRATION(LoggerTest);

LoggerTest::LoggerTest() {
}

LoggerTest::~LoggerTest() {
}

void LoggerTest::setUp() {
}

void LoggerTest::tearDown() {
}

void LoggerTest::testError() {
    string message = "Error! You messed up.";
    Logger::error(message);
    CPPUNIT_ASSERT_EQUAL(errno, EINVAL);
}

void LoggerTest::testErrorQuit() {
    // not sure how to test exiting methods with cppunit
}

