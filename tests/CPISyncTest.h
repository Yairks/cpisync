/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/* 
 * File:   probCPISyncTest.h
 * Author: kaets
 *
 * Created on June 1, 2018, 3:41 PM
 */

#ifndef CPISYNCTEST_H
#define CPISYNCTEST_H

#include <cppunit/extensions/HelperMacros.h>

class CPISyncTest : public CPPUNIT_NS::TestFixture {

    
    CPPUNIT_TEST_SUITE(CPISyncTest);
    
    CPPUNIT_TEST(testEgg);
    
    CPPUNIT_TEST_SUITE_END();
    
public:
    CPISyncTest();
    virtual ~CPISyncTest();
    void setUp();
    void tearDown();
    void testEgg();
private:

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CPISyncTest, CPISyncTest);

#endif /* PROBCPISYNCTEST_H */

