/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/* 
 * File:   probCPISyncTest.h
 * Author: kaets
 *
 * Created on June 1, 2018, 3:41 PM
 */

#ifndef PROBCPISYNCTEST_H
#define PROBCPISYNCTEST_H

#include <cppunit/extensions/HelperMacros.h>

class probCPISyncTest : public CPPUNIT_NS::TestFixture {

    
    CPPUNIT_TEST_SUITE(probCPISyncTest);
    
    //CPPUNIT_TEST();
    
    CPPUNIT_TEST_SUITE_END();
    
public:
    probCPISyncTest();
    probCPISyncTest(const probCPISyncTest& orig);
    virtual ~probCPISyncTest();
    void setUp();
    void tearDown();
private:

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(probCPISyncTest, probCPISyncTest);

#endif /* PROBCPISYNCTEST_H */

