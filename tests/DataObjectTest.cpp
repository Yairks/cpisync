/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */
/*
 * File:   DataObjectTest.cpp
 * Author: kaets
 *
 * Created on May 15, 2018, 10:33:52 AM
 */

#include "DataObjectTest.h"
#include "DataObject.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(DataObjectTest);

DataObjectTest::DataObjectTest() {
}

DataObjectTest::~DataObjectTest() {
}

void DataObjectTest::setUp(){
}

void DataObjectTest::tearDown(){ 
}

void DataObjectTest::testToZZAndInitZZ(){
    const short init = 64;
    const ZZ zz = static_cast<ZZ>(init);
    
    const DataObject d(zz);
    CPPUNIT_ASSERT(d.to_ZZ() == zz);
    
}

void DataObjectTest::testToStringAndInitString(){
    const string s = "AA";
    const string t = "16705";
    
    // the string 's' represents the bitsequence 010000101000001
    // this bitsequence represents 16705 in decimal, which is the string 't'
    
    DataObject d;
    
    // Two cases - either RepIsInt is true or false. 
    
    // False case
    DataObject::RepIsInt = false;
    d = DataObject(s);
    CPPUNIT_ASSERT(d.to_string() == s); 
    
    // True case
    DataObject::RepIsInt = true;
    d = DataObject(t);
    
    CPPUNIT_ASSERT(d.to_string() == t);
    
    // Case when string is initialized as a bitsequence (false)
    // and then becomes an integer representation of that bitsequence (true)
    DataObject::RepIsInt = false;
    d = DataObject(s);
    DataObject::RepIsInt = true;
    CPPUNIT_ASSERT(d.to_string() == t);
    
    // Case when string is initialized as integer representation (true)
    // and then converted to a bitsequence character representation (false)
    DataObject::RepIsInt = true;
    d = DataObject(t);
    DataObject::RepIsInt = false;
    CPPUNIT_ASSERT(d.to_string() == s);
}

void DataObjectTest::testToStringAndInitEmpty(){
    const string expected = "\0";
    const string expected_int = "0";
    DataObject d;
    
    // false
    DataObject::RepIsInt = false;
    CPPUNIT_ASSERT(d.to_string() == expected);
    
    // true
    DataObject::RepIsInt = true;
    CPPUNIT_ASSERT(d.to_string() == expected_int);
    
}

void DataObjectTest::testToPriorityStringAndInitStringableAndSetPriority(){
    const int init = 65;
    const int _priority = 54;
    const ZZ priority = static_cast<ZZ>(_priority);
    //DataObject d(init); // Shouldn't this work? Not sure what I'm doing wrong here. Integers are definitely "stringable"
    DataObject d(to_string(init));
    
    d.setPriority(priority);
    // false
    DataObject::RepIsInt = false;
    const string init_string = "A";
    CPPUNIT_ASSERT(d.to_priority_string() == init_string);
    
    // true
    DataObject::RepIsInt = true;
    stringstream expected;
    expected << priority << "," << init;
    CPPUNIT_ASSERT(d.to_priority_string() == expected.str());
    
    
}

void DataObjectTest::testToCharArray(){
    const string s = "AA";    
    const short expected_len = 2; // "AA" is 2 chars long
    const char *expected = s.data();
    
    DataObject::RepIsInt = false;  
    DataObject d(s);
    
    int result_len;
    const char *result = d.to_char_array(result_len);
    
    bool same = true;
    for(int i = 0; i < result_len; i++){
        if(result[i] != expected[i])
            same = false;
    }
    
    CPPUNIT_ASSERT(expected_len == result_len);
    CPPUNIT_ASSERT(same);
    
}

void DataObjectTest::testPrint(){
    const string s = "AA";
    const string s_int = "16705";
    // Doesn't use the standard B64 encoding.
    const string s_b64 = "?EJ=";
    DataObject d;

    // false
    DataObject::RepIsInt = false;
    d = DataObject(s);
    CPPUNIT_ASSERT(d.print() == s_b64);
    
    // true
    DataObject::RepIsInt = true;
    d = DataObject(s_int);
    CPPUNIT_ASSERT(d.print() == s_int);
}

void DataObjectTest::testStreamInsertion(){
    const string s = "AA";
    
    DataObject::RepIsInt = false; 
    DataObject d(s);
    
    stringstream expected;
    stringstream result;
    expected << s;
    result << d;
    
    CPPUNIT_ASSERT(expected.str() == result.str());
}

void DataObjectTest::testLessThan(){
    const string gt = "AAA";
    const string lt = "A";
    DataObject::RepIsInt = false; 
    
    DataObject big(gt);
    DataObject small(lt);
    
    CPPUNIT_ASSERT(small < big);
}

void DataObjectTest::testPriority(){
    const int _priority = 5;
    const ZZ priority = static_cast<ZZ>(_priority);
    DataObject d;
    d.setPriority(priority);
    CPPUNIT_ASSERT(d.getPriority() == priority);
    
}

void DataObjectTest::testTimeStamp(){
    const clock_t time = 12345;
    DataObject d;
    d.setTimeStamp(time);
    CPPUNIT_ASSERT(d.getTimeStamp() == time);
}