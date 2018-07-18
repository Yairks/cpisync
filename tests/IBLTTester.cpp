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
#include "CommString.h"
#include "testFunctions.h"
/*
 * Simple C++ Test Suite
 */
void fillIBLT(IBLT*);
void fillIBLT(IBLT*, int, int);
void notRandomFill(bool first, IBLT* iblt, int insertsNum, int max);

void test1() {
    std::srand(time(0));
    
    IBLTSync origin(30, sizeof(50));
    fillIBLT(&origin.iblt, 30, 50);

    std::cout << "Created and filled iblt \"origin\"" << std::endl;
    
    std::string str = origin.iblt.serializeEntries();    
    std::cout << "Serialized origin" << std::endl;

    IBLT dest(str);    
    std::cout << "Deserialized origin into dest" << std::endl;
    
    IBLT compare(origin.iblt - dest);
    std::cout << "Compared the two iblts" << std::endl;

    std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValues;
    std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValues;

    bool successful = compare.listEntries(positiveValues, negativeValues);
    
    if(true) {
        std::cout << "Successfully compared iblts. Let's list the differences (there should be none):" << std::endl;
        
        std::set<std::pair<uint64_t, std::vector<uint8_t> > >::iterator it;
        for (it = positiveValues.begin(); it != positiveValues.end(); it++)
        {
            uint64_t key = std::get<0>(*it);
            cout << "found: ";
            cout << key << endl;
            
        }
        
        std::cout << "\nand now for the other differences:" << std::endl;
        for (it = negativeValues.begin(); it != negativeValues.end(); it++)
        {
            uint64_t key = std::get<0>(*it);
            cout << "found: ";
            cout << key << endl;
        }
        cout << "\nThose were all the differences" << endl;
    }
    
    else {
        std::cout << "Couldn't successfully decode." << endl;
    }
}

void test2() {
    std::cout << "IBLTTester test 2" << std::endl;
    
    //Create an IBLTSync object (will receive an IBLT).
    IBLTSync origin(30, sizeof(50));
    fillIBLT(&origin.iblt, 30, 50);
    //notRandomFill(true, &origin.iblt, 50, 50);
    
    std::cout << "Created and filled IBLT" << std::endl;

    //Create a received IBLT.
    IBLT received(30, sizeof(50));
    fillIBLT(&received, 30, 50);
    //notRandomFill(false, &received, 50, 50);
    CommString comm(received.serializeEntries());
    std::cout << "Created and filled another IBLT and commstringed it" << std::endl;
    
    //Check their differences
    std::list<DataObject*> positives;
    std::list<DataObject*> negatives;
    bool successful = origin.SyncServer(&comm, positives, negatives);
    
    if(successful)
        std::cout << "Success!" << std::endl;
    else
        std::cout << "failure. :(" << std::endl;
    
    std::cout << "Size of self minus other: " << positives.size() << std::endl;
    std::cout << "Size of other minus self: " << negatives.size() << std::endl;
    
    cout << "Printing elements that second iblt had that the first didn't." << endl;
    std::list<DataObject*>::iterator entry = positives.begin();
    for(; entry != positives.end(); entry++) {
        cout << (*entry)->to_string() << endl;
    }
    
    cout << "Printing elements that first iblt had that the second didn't." << endl;
    for(entry = negatives.begin(); entry != negatives.end(); entry++) {
        cout << (*entry)->to_string() << endl;
    }
    
    std::cout << "%TEST_FAILED% time=0 testname=test2 (IBLTTester) message=error message sample" << std::endl;
}

void test3() {
    std::cout << "\n\nBEGIN TEST 3" << std::endl;
    
    IBLT origin(50, sizeof(50));
    notRandomFill(true, &origin, 50, 50);
    std::cout << "Created and filled IBLT" << std::endl;
    
    //Create a received IBLT.
    IBLT received(50, sizeof(50));
    notRandomFill(false, &received, 50, 50);
    
    IBLT diff(origin - received);
    
    std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValues;

    std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValues;

  //lists the entries from the new iblt
  bool successful = diff.listEntries(positiveValues, negativeValues);

  //checks if listing entries was successful
  if (successful) {
    cout << "Successful listing of entries out of IBLT C Made from A- B" << endl;
  }

  std::set<std::pair<uint64_t, std::vector<uint8_t> > >::iterator it;

  std::cout << "positive values:" << std::endl;
  for (it = positiveValues.begin(); it != positiveValues.end(); it++)
  {
    uint64_t key = std::get<0>(*it);

    cout << key << endl;
  }
  
  std::cout << "negative values:" << std::endl;
  for (it = negativeValues.begin(); it != negativeValues.end(); it++)
  {
    uint64_t key = std::get<0>(*it);

    cout << key << endl;
  }
}

void ultimateTest() {
    
}

void fillIBLT(IBLT* iblt) {
    return fillIBLT(iblt, 1000, std::numeric_limits<int>::max());
}

void fillIBLT(IBLT* iblt, int insertsNum, int max) {
    uint32_t k = 1;
    std::vector<int> usedNums;
    std::vector<uint8_t> vec;
    
    for(int i = 0; i < insertsNum; i++) {
        //Make sure that the key is unique.
        do {
            k = std::rand() % max;
        } while(std::find(usedNums.begin(), usedNums.end(), k) != usedNums.end());
        
        std::cout << k << " ";
        
        vec = ToVec((int) k);
        usedNums.push_back(k);
        
        while(sizeof(max) > vec.size()) {
            vec.push_back('0');
        }
        
        iblt->insert(k, vec);
    }
}

void notRandomFill(bool first, IBLT* iblt, int insertsNum, int max) {
    if(first) {
        for(int i = 0; i < insertsNum / 2; i++) {
            iblt->insert(i, ToVec(i));
            cout << i << " ";
        }
    }
    
    else {
        for(int i = 10; i < insertsNum / 2 + 10; i++) {
            iblt->insert(i, ToVec(i));
            std::cout << i << " ";
        }
        
    }
    std::cout << std::endl;
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
    
    test3();

    return (EXIT_SUCCESS);
}

