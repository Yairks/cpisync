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
#include "Auxiliary.h"
#include "SyncMethod.h"

// namespaces
using namespace NTL;

/**
 * A data structure that stores multi-sets of data. Unlike CPISync, which
 * efficiently reconciles differences between multi-sets, this data structure
 * takes an anti-entropy way of reconciling the sets, i.e. by simply exchanging
 * entire multi-sets from one peer to another.
 */
class FullSync : public SyncMethod {
public:
    
    /**
     *  Specific class constructor.
     * 
     * @param hashes Should data be stored as is, or first reduced via a hash.
    */
    FullSync(bool hashes = false);
    
    // General class destructor
    ~FullSync();
    
   /**
   * Connect as a client to a specific communicant and computes differences between the two (without actually updating them).
   * All results are *added* to the selfMinusOther and otherMinusSelf parameters (passed by reference).
   * %R:  Sync_Server must have been called at that communicant.
   * 
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
  
  /*
   ** update metadata when an element is being added
   */
  bool addElem(DataObject* newDatum);

  template <typename T>
  bool addElem(T* newDatum);

  // update metadata when an element is being deleted (the element is supplied by index)
  bool delElem(DataObject* newDatum);

  /**
   * @return A string with some internal information about this object.
   */
  string getName();

  /**
   * @return A string representing the elements (with hashes) stored in the CPISync object.
   */
  string printElem();
protected:
  // internal data
  bool oneWay; /** Enables one-way FullSync when set to true.  Otherwise, both client and server are synced.*/
  bool hashQ; /** Typically CPISync syncs hashes of elements (hashQ == true), then exchange the differing elements.
                  * With hashQ == false, trivial hashes are used (that are in one-to-one correspondence with data)
                  * so that actual element differences are computed in CPISync, and
                  * one round of communication is saved.  Under this situation, all elements, must comfortably
                  *  fit within the prescribed bit-length for internal storage, and no element duplicates are permitted.
                  *
                  * With hashQ == true, element duplicates are permitted (handled through hashing) and, potentially,
                 * element  representations are smaller.
                 */
  bool keepAlive; /** If this is true, the CPISync does not setup or close the communicant connection - these
                     *  can be handled manually.
                     */

  long bitNum; /** Number of bits used to represent an element of the set that is being synchronized. */
  ZZ fieldSize; /** The size of the finite field used to represent set elements. */

  map< ZZ, DataObject * > fullHash; /** list of pairs, one for each element in the set (to be synchronized).
                                           *  The first item in the pair is a hash (a long integer) 
                                           *  of the second item, which is the set element.
                                           *  All operations are done on the hashes, and this look-up table can be used to retrieve
                                           *  the actual element once the hashes have been synchronized.
                                           */

  // helper functions
  /**
   * Sends all hashes through a Communicant.
   * @param commSync The Communicant to connect to.
   */
  void sendHashes(Communicant* commSync);
};

#endif /* FULLSYNC_H */

