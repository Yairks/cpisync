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
    const int _init = 64;
    const ZZ init = static_cast<ZZ>(_init);
    
    const DataObject d(init);
    CPPUNIT_ASSERT(d.to_ZZ() == init);
    
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
    CPPUNIT_ASSERT_EQUAL(s, d.to_string()); 
    
    // True case
    DataObject::RepIsInt = true;
    d = DataObject(t);
    
    CPPUNIT_ASSERT_EQUAL(t, d.to_string());
    
    // Case when string is initialized as a bitsequence (false)
    // and then becomes an integer representation of that bitsequence (true)
    DataObject::RepIsInt = false;
    d = DataObject(s);
    DataObject::RepIsInt = true;
    CPPUNIT_ASSERT_EQUAL(t, d.to_string());
    
    // Case when string is initialized as integer representation (true)
    // and then converted to a bitsequence character representation (false)
    DataObject::RepIsInt = true;
    d = DataObject(t);
    DataObject::RepIsInt = false;
    CPPUNIT_ASSERT_EQUAL(s, d.to_string());
}

void DataObjectTest::testToStringAndInitEmpty(){
    // We expect a default constructed DataObject 
    // to be represented as an empty string.
    const string expected = "";
    
    // An empty string if we assume that it represents an integer
    const string expected_int = "0";
    
    DataObject d;
    
    // false case
    DataObject::RepIsInt = false;
    CPPUNIT_ASSERT_EQUAL(expected, d.to_string());
    
    // true case
    DataObject::RepIsInt = true;
    CPPUNIT_ASSERT_EQUAL(expected_int, d.to_string());
    
}

void DataObjectTest::testToPriorityStringAndInitStringableAndSetPriority(){
    // Our initial value. Not a ZZ or a string, so the templated constructor
    // should be called.
    const int init = 65;
    
    // Our initial value as a string. This represents the expected return value
    // of DataObject::to_string(), since the templated constructor should
    // "simply [convert] the object to a string and then [do] the same as the
    // string constructor."
    const string init_string = to_string(init);
    
    // If DataObject::RepIsInt == true, the bitwise representation of the string
    // "65" will be considered as an integer (the equivalent of 
    // reinterpret_cast<int>(init_string) if you were actually permitted to do
    // this)
    const int init_string_as_int = 13622;
    
    // ZZ representing an arbitrary priority, 54.
    const int _priority = 54;
    const ZZ priority = static_cast<ZZ>(_priority);
    
    DataObject d(init);
    
    d.setPriority(priority);
    
    // false case
    DataObject::RepIsInt = false;
    CPPUNIT_ASSERT_EQUAL(init_string, d.to_priority_string());
    
    // true case
    DataObject::RepIsInt = true;
    stringstream expected;
    expected << priority << "," << init_string_as_int;
    CPPUNIT_ASSERT_EQUAL(expected.str(), d.to_priority_string());
    
    
}

void DataObjectTest::testToCharArray(){
    const string s = "AA";    
    int expected_len = s.length();
    const char *expected = s.data();
    
    DataObject::RepIsInt = false;  
    DataObject d(s);
    
    int result_len;
    const char *result = d.to_char_array(result_len);
    
    
    // assert equality of char* arrays by checking equality of
    // each corresponding element.
    bool same = true;
    for(int i = 0; i < result_len; i++){
        if(result[i] != expected[i])
            same = false;
    }
    
    CPPUNIT_ASSERT_EQUAL(expected_len, result_len);
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
    CPPUNIT_ASSERT_EQUAL(d.print(), s_b64);
    
    // true
    DataObject::RepIsInt = true;
    d = DataObject(s_int);
    CPPUNIT_ASSERT_EQUAL(d.print(), s_int);
}

void DataObjectTest::testStreamInsertion(){
    const string s = "AA";
    
    DataObject::RepIsInt = false; 
    DataObject d(s);
    
    stringstream expected;
    stringstream result;
    expected << s;
    result << d;
    
    CPPUNIT_ASSERT_EQUAL(expected.str(), result.str());
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
    CPPUNIT_ASSERT_EQUAL(d.getPriority(), priority);
    
}

void DataObjectTest::testTimeStamp(){
    const clock_t time = 12345;
    DataObject d;
    d.setTimeStamp(time);
    CPPUNIT_ASSERT_EQUAL(d.getTimeStamp(), time);
}