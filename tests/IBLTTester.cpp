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

#include <cassert>
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
std::vector<int> fillIBLT(IBLT* iblt);
std::vector<int> fillIBLT(IBLT* iblt, int insertsNum, int max);
std::vector<int> fillIBLT(IBLTSync* ibltSync, int insertsNum, int max);

void test1() {
    std::cout << "\nTest 1 checks that serializeEntries() and the deserializing constructor are\n working properly.\n" << std::endl;
    std::srand(time(0));
    
    IBLTSync origin(30, sizeof(50));
    
    //Fills the IBLT and stores the keys in the vector.
    std::vector<int> fillers(fillIBLT(&origin.iblt, 30, 50));
    
    //Serialize then deserialize the IBLT
    std::string str = origin.iblt.serializeEntries();    

    IBLT dest(str);    
    
    //Check that the new IBLT equals the old one.
    std::vector<uint8_t> result;
    std::vector<int>::iterator it = fillers.begin();
    for(; it < fillers.end(); it++) {
        if(dest.get(*it.base(), result)) {
            assert(ToVec(*it.base()) == result);
        }
        
        //Sometimes the get method fails (because of how IBLTs work).
        else {
            std::cout << "Unusual behavior: Could not figure out if the iblt contains an element." << std::endl;
            std::cout << "See code of IBLT.get() to see when method can fail." << std::endl;
        }
    }
    
    //Now compare them.
    IBLT compare(origin.iblt - dest);

    std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValues;
    std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValues;

    assert(compare.listEntries(positiveValues, negativeValues));
    
    assert(positiveValues.size() == negativeValues.size() && negativeValues.size() == 0);
    
    std::cout << "\nFinished test 1 successfully. Party it up!\n" << std::endl;
}

void test2() {
    std::cout << "\nTest2 checks that IBLTSync's methods are functioning properly\n" << std::endl;
    
    //Create an IBLTSync object and fill it.
    IBLTSync origin(30, sizeof(50));
    std::vector<int> fillersA(fillIBLT(&origin, 30, 50));

    //Create a received IBLT.
    IBLTSync received(30, sizeof(50));
    std::vector<int> fillersB(fillIBLT(&received, 30, 50));
    
    CommString comm(received.iblt.serializeEntries());
    
    //Check their differences
    std::list<DataObject*> positives;
    std::list<DataObject*> negatives;
    
    //Make sure the syncing went happily
    assert(origin.SyncServer(&comm, positives, negatives));
    
    //They should have an equal number of differences.
    assert(positives.size() == negatives.size());
    
    //Manually check that each difference is in fact a difference.
    std::list<DataObject*>::iterator entry = positives.begin();
    for(; entry != positives.end(); entry++) {
        //Make sure it's not in fillersA but is in fillersB
        assert(std::find(fillersB.begin(), fillersB.end(),
                std::stoull((*entry)->to_string())) == fillersB.end());
        
        assert(std::find(fillersA.begin(), fillersA.end(), 
                std::stoull((*entry)->to_string())) != fillersA.end());
    }

    for(entry = negatives.begin(); entry != negatives.end(); entry++) {
        //Make sure it's not in fillersA but is in fillersB
        assert(std::find(fillersA.begin(), fillersA.end(),
                std::stoull((*entry)->to_string())) == fillersA.end());
        
        assert(std::find(fillersB.begin(), fillersB.end(), 
                std::stoull((*entry)->to_string())) != fillersB.end());
    }
    
    std::cout << "Test 2 passed. Whew." << std::endl;
}

std::vector<int> fillIBLT(IBLT* iblt) {
    return fillIBLT(iblt, 1000, std::numeric_limits<int>::max());
}

std::vector<int> fillIBLT(IBLT* iblt, int insertsNum, int max) {
    uint32_t k = 1;
    std::vector<int> usedNums;
    std::vector<uint8_t> vec;
    
    for(int i = 0; i < insertsNum; i++) {
        //Make sure that the key is unique.
        do {
            k = std::rand() % max;
        } while(std::find(usedNums.begin(), usedNums.end(), k) != usedNums.end());
        
        vec = ToVec((int) k);
        usedNums.push_back(k);
        
        while(sizeof(max) > vec.size()) {
            vec.push_back('0');
        }
        
        iblt->insert(k, vec);
    }
    
    return usedNums;
}

std::vector<int> fillIBLT(IBLTSync* ibltSync, int insertsNum, int max) {
    uint32_t k = 1;
    std::vector<int> usedNums;
    std::vector<uint8_t> vec;
    
    for(int i = 0; i < insertsNum; i++) {
        //Make sure that the key is unique.
        do {
            k = std::rand() % max;
        } while(std::find(usedNums.begin(), usedNums.end(), k) != usedNums.end());
        
        usedNums.push_back(k);
        
        DataObject datum(std::to_string(k));
        
        ibltSync->addElem(&datum);
    }
    
    return usedNums;
}

int main(int argc, char** argv) {
    std::cout << "Let's run some tests:" << std::endl;
    
    test1();
    
    test2();
    
    std::cout << "We did it! Yay!" << std::endl;

    return (EXIT_SUCCESS);
}