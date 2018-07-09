//
// Created by eliezer pearl on 7/9/18.
//

#ifndef CPISYNCLIB_IBLT_H
#define CPISYNCLIB_IBLT_H

#include <vector>
#include <list>
#include <utility>
#include <NTL/ZZ.h>

using std::vector;
using std::pair;
using std::list;
using namespace NTL;

/*
 * IBLT (Invertible Bloom Lookup Table) is a data-structure designed to add
 * partial invertibility to the standard Bloom Filter data-structure.
 *
 * A complete description of the IBLT data-structure can be found in: 
 * Goodrich, Michael T., and Michael Mitzenmacher. "Invertible bloom lookup tables." 
 * arXiv preprint arXiv:1101.2245 (2011).
 */

// K represents the type of the key, V the value, of the key-value pairs stored in this data structure
template <class K, class V>
class IBLT {
public:
    // default constructor
    IBLT();
    
    // default destructor
    ~IBLT();
    
    /**
     * Inserts a key-value pair to the IBLT.
     * This operation always succeeds.
     * @param key The key to be added
     * @param value The value to be added
     * @require The key must be distinct in the IBLT
     */
    void insert(K key, V value);
    
    /**
     * Removes a key-value pair from the IBLT.
     * This operation always succeeds.
     * @param key The key to be removed
     * @param value The value to be removed
     * @require the key-value pair must be in the IBLT
     */
    void remove(K key, V value);
    
    /**
     * Produces the value s.t. (key, value) is in the IBLT.
     * This operation doesn't always succeed.
     * @param key The key corresponding to the value returned by this function
     * @param result The resulting value corresponding with the key, if found.
     * If not found, result will be null. result is unchanged iff the operation returns false.
     * @return true iff the presence of the key could be determined
     */
    bool get(K key, V& result);
    
    /**
     * Produces a list of all the key-value pairs in the IBLT.
     * With a low, constant probability, only a partial list will be produced
     * Listing is destructive. Will remove all key-value pairs from the IBLT that are listed.
     * @param result The resulting full list of key-value pairs in IBLT iff the operation returns true
     * Otherwise, result will be set to a partial list of key-value pairs in the IBLT
     * @return true iff the operation has successfully recovered the entire list
     */
    bool listEntries(list<pair<K, V>>& result);
    
private:
    // local data
    
    /**
     * Converts an item into a ZZ
     * @param item An item to be converted into a ZZ
     * @return A ZZ representing T
     */
    template <class T>
    ZZ toZZ(T item);
    
    // class representing a table entry
    class Entry {
    public:
        int getCount();
        ZZ getKeySum();
        ZZ getValueSum();
        void addKeyValue(ZZ key, ZZ value);
        void removeKeyValue(ZZ key, ZZ value);
    private:
        int count;
        ZZ keySum;
        ZZ valueSum;
    }; 
    
    // the table is stored as a vector of entries
    vector<Entry> table;
};


#endif //CPISYNCLIB_IBLT_H
