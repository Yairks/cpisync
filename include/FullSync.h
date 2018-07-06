/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

/* 
 * File:   FullSync.h
 * Author: kaets
 *
 * Created on June 27, 2018, 9:37 AM
 */

#ifndef FULLSYNC_H
#define FULLSYNC_H

#include <NTL/RR.h>
#include <NTL/ZZ_pX.h>
#include <NTL/vec_ZZ_p.h>
#include <NTL/ZZ_pXFactoring.h>
#include <algorithm>
#include "Auxiliary.h"
#include "SyncMethod.h"
#include "Exceptions.h"

// namespaces
using namespace NTL;

/**
 * A class that stores and reconciles multi-sets of data. Unlike CPISync, which
 * efficiently reconciles multi-sets, FullSync simply exchanges entire multi-sets
 * from one peer to another for reconciliation.
 */
class FullSync : public SyncMethod {
public:
    
    // General class constructor
    FullSync();
    
    // General class destructor
    ~FullSync();
  
   /** 
    * Add an element.
    * @param newDatum A pointer to the DataObject to be added
    * @return true iff the element has been successfully added
    */
  bool addElem(DataObject* newDatum);

  /**
   * Remove an element.
   * @require newDatum must point to a DataObject that has been added using addElem and has not been deleted using delElem
   * @param newDatum A pointer to DataObject
   * @return true iff the element is in the set and has been successfully removed
   */
  bool delElem(DataObject* newDatum);

  /**
   * @return A string detailing this object.
   */
  inline string getName() { return "I am a FullSync object."; }

  /**
   * @return A string representing the elements stored in the FullSync object.
   */
  string printElem();
protected:
  // helper functions
  
  /**
   * Returns a representation of the FullSync set as a DataObject* list.
   */
  list<DataObject *> repDOList();
  
  /**
   * Prints out a string representing all DataObjects from begin until end
   * @param begin An iterator representing the beginning of a DataObject collection
   * @param end An iterator representing the end of the same collection as begin
   * @require there must be some finite integer n s.t. begin + n = end
   */
  template <typename Iterator>
  string printElem(const Iterator begin, const Iterator end);
};

#endif /* FULLSYNC_H */

