/* 
 * File:   IBLTSync.h
 * Author: Yair Kosowsky-Sachs
 *
 * Created on July 10, 2018, 10:09 AM
 * 
 * It's kind of unclear how this is gonna play out. I'm pretty optimistic,
 * which likely means that only bad things will result from this.
 */

#ifndef IBLTSYNC_H
#define IBLTSYNC_H

#include <string>
#include "Auxiliary.h"
#include "SyncMethod.h"
#include "iblt.h"

class IBLTSync : public SyncMethod {
public:    
    // CONSTRUCTOR/DESTRUCTOR

    /**
     * Creates an IBLTSync object. Unclear what it might do at the moment.
     * I think that it will then create its own private IBLT object using these
     * values and add and delete elements as needed.
     * 
     * When the time comes to compare, call SyncClient() or SyncServer()
     * so that it can subtract them and return the stuff.
     * 
     * Whew. That sounds reasonable. Fingers crossed that it works.
     * 
     * @param _expectedNumEntries Expect number of values
     * @param _ValueSize Expected size of each value (use sizeof() to find out)
     */
    IBLTSync(size_t _expectedNumEntries, size_t _ValueSize);
    
    // destructor
    ~IBLTSync();

    // SYNC
    /**
     * Note: For an IBLT Sync that will be sent via Bitcoin Core, this method will do nothing.
     * 
     * Connect as a client to a specific communicant and computes differences between the two (without actually updating them).
     * All results are *added* to the selfMinusOther and otherMinusSelf parameters (passed by reference).
     * %R:  Sync_Server must have been called at that communicant.
     * 
     * @param commSync The communicant to whom to connect.
     * @param selfMinusOther A result of reconciliation.  Elements that I have that the other SyncMethod does not.
     * @param otherMinusSelf A result of reconciliation.  Elements that the other SyncMethod has that I do not.
     * @return true iff the connection and subsequent synchronization appear to be successful.
     */
    bool SyncClient(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf);
    
    /**
     * Waits for a client to connect from a specific communicant and computes differences between the two (without actually updating them).
     * All results are *added* to the selfMinusOther and otherMinusSelf parameters (passed by reference).
     *      * 
     * @param commSync The communicant to whom to connect.
     * @param selfMinusOther A result of reconciliation.  Elements that I have that the other SyncMethod does not.
     * @param otherMinusSelf A result of reconciliation.  Elements that the other SyncMethod has that I do not.
     * @return true iff the connection and subsequent synchronization appear to be successful.
     */
    bool SyncServer(Communicant* commSync, list<DataObject*> &selfMinusOther, list<DataObject*> &otherMinusSelf);

    // MANIPULATE DATA
    /**
     * Add an element to the data structure that will be performing the synchronization.
     * @param datum The element to add.  Note:  a pointer to this item is added to the
     * hash, so it is advisable not to change the datum dereference hereafter.
     * 
     * This datum (hehe what a funny word) will be added to the iblt.
     * 
     * @return true iff the addition was successful
     */
    bool addElem(DataObject* datum);

    /**
     * Delete an element from the data structure that will be performing the synchronization.
     * 
     * The datum will be removed from the iblt.
     * 
     * @param datum The element to delete.
     * @return true iff the removal was successful
     */
    bool delElem(DataObject* datum);

    // INFORMATIONAL
    /**
     * @return A human-readable name for the synchronization method.
     */
    inline string getName() { return "An IBLT Sync object"; }
    
    IBLT iblt;

private:
    int key;
    size_t valueSize;
    /**
     * Copies from the IBLT program's format to the GenSync's format.
     * 
     * @param positive Elements that I have that the other guy doesn't
     * @param negative Elements that the other guy has that I don't
     * @param selfMinusOther Elements that I have that the other guy doesn't
     * @param otherMinusSelf Elements that the other guy has that I don't
     * @return true if the switching between succeeded
     */
    bool fromIBLTtoGenSync(std::set<std::pair<uint64_t,std::vector<uint8_t> > >& positive,
        std::set<std::pair<uint64_t,std::vector<uint8_t> > >& negative,
        list<DataObject*> &selfMinusOther,
        list<DataObject*> &otherMinusSelf);
}; 


#endif /* IBLTSYNC_H */

