/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   DataObjectTest.h
 * Author: kaets
 *
 * Created on May 15, 2018, 10:33:51 AM
 */

#ifndef DATAOBJECTTEST_H
#define DATAOBJECTTEST_H

#include <cppunit/extensions/HelperMacros.h>

class DataObjectTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(DataObjectTest);

    CPPUNIT_TEST(testToZZAndInitZZ);
    CPPUNIT_TEST(testToStringAndInitString);
    CPPUNIT_TEST(testToStringAndInitEmpty);
    CPPUNIT_TEST(testToPriorityStringAndInitStringableAndSetPriority);
    CPPUNIT_TEST(testToCharArray);
    CPPUNIT_TEST(testPrint);
    CPPUNIT_TEST(testStreamInsertion);
    CPPUNIT_TEST(testLessThan);
    CPPUNIT_TEST(testPriority);
    CPPUNIT_TEST(testTimeStamp);

    CPPUNIT_TEST_SUITE_END();

public:
    DataObjectTest();
    virtual ~DataObjectTest();
    void setUp();
    void tearDown();

private:
    void testToZZAndInitZZ();
    void testToStringAndInitString();
    void testToStringAndInitEmpty();
    void testToPriorityStringAndInitStringableAndSetPriority();
    void testToCharArray();
    void testPrint();
    void testStreamInsertion();
    void testLessThan();
    void testPriority();
    void testTimeStamp();
};

#endif /* DATAOBJECTTEST_H */

