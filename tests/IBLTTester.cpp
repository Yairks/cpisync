/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IBLTTester.cpp
 * Author: regular
 *
 * Created on July 10, 2018, 2:59 PM
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include "IBLTSync.h"
#include "DataObject.h"
#include "iblt.h"

/*
 * Simple C++ Test Suite
 */

void test1() {
    IBLTSync trial(1000, sizeof(1000));
    cout << trial.getName() << endl;
    
    for(int i = 0; i < 20; i++) {
        DataObject datum(std::string("fa1afe1fa1afe1fa1afe1"));

        trial.addElem(&datum);
    }

    
    vector<DataObject*>::const_iterator elem = trial.beginElements();
    for(; elem != trial.endElements(); elem++) {
        trial.delElem(*elem);
    }
}

void test2() {
    std::cout << "IBLTTester test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (IBLTTester) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% IBLTTester" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (IBLTTester)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (IBLTTester)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (IBLTTester)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (IBLTTester)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

