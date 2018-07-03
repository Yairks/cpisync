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
   * Connect as a client to a specific communicant and computes differences between the two (without actually updating them).
   * All results are *added* to the selfMinusOther and otherMinusSelf parameters (passed by reference).
   * 
   * @require SyncServer must have been called at that communicant.
   * @param commSync The communicant to whom to connect.
   * @param selfMinusOther A result of reconciliation.  Elements that I have that the other Communicant does not.
   * @param otherMinusSelf A result of reconciliation.  Elements that the other Communicant has that I do not.
   * @return true iff the connection and subsequent synchronization appear to be successful.
   */
  bool SyncClient(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf);

  /**
   * Waits for a client to connect from a specific communicant and computes differences between the two (without actually updating them).
   * All results are *added* to the selfMinusOther and otherMinusSelf parameters (passed by reference).
   * 
   * @param commSync The Communicant to whom to connect.
   * @param selfMinusOther A result of reconciliation.  Elements that I have that the other Communicant does not.
   * @param otherMinusSelf A result of reconciliation.  Elements that the other Communicant has that I do not.
   * @return true iff the connection and subsequent synchronization appear to be successful.
   */
  bool SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf);
  
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
   * Calculates differences between myList and a given clientList, updating selfMinusOther and otherMinusSelf accordingly
   * @param clientList The list with which to reconcile differences
   * @param selfMinusOther Objects that I have that the other doesn't
   * @param otherMinusSelf Objects that the other has that I don't
   * @require clientList is a set, i.e. it has no duplicate elements
   */
  void calcDiff(list<DataObject *> clientList, list<DataObject *>& selfMinusOther, list<DataObject *>& otherMinusSelf);
  
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

