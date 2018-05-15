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

    CPPUNIT_TEST(testInitNoArgs);
    CPPUNIT_TEST(testInitZZ);
    CPPUNIT_TEST(testInitString);
    CPPUNIT_TEST(testInitStringable);
    CPPUNIT_TEST(testToZZ);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testToPriorityString);
    CPPUNIT_TEST(testToCharArray);
    CPPUNIT_TEST(testPrint);
    CPPUNIT_TEST(testStreamInsertion);
    CPPUNIT_TEST(testLessThan);
    CPPUNIT_TEST(testSetPriority);
    CPPUNIT_TEST(testGetPriority);
    CPPUNIT_TEST(testSetTimeStamp);
    CPPUNIT_TEST(testGetTimeStamp);
    CPPUNIT_TEST(testPack);
    CPPUNIT_TEST(testUnpack);

    CPPUNIT_TEST_SUITE_END();

public:
    DataObjectTest();
    virtual ~DataObjectTest();
    void setUp();
    void tearDown();

private:
    void testInitNoArgs();
    void testInitZZ();
    void testInitString();
    void testInitStringable();
    void testToZZ();
    void testToString();
    void testToPriorityString();
    void testToCharArray();
    void testPrint();
    void testStreamInsertion();
    void testLessThan();
    void testSetPriority();
    void testGetPriority();
    void testSetTimeStamp();
    void testGetTimeStamp();
    void testPack();
    void testUnpack();
};

#endif /* DATAOBJECTTEST_H */

