
#ifndef IBLT_H
#define IBLT_H

#include <inttypes.h>
#include <set>
#include <vector>

using std::string;

//
// Invertible Bloom Lookup Table implementation
// References:
//
// "What's the Difference? Efficient Set Reconciliation
// without Prior Context" by Eppstein, Goodrich, Uyeda and
// Varghese
//
// "Invertible Bloom Lookup Tables" by Goodrich and
// Mitzenmacher
//

class IBLT
{
public:
  //constructors and desctructors
    IBLT(size_t _expectedNumEntries, size_t _ValueSize);
    IBLT(const IBLT& other);
    IBLT(std::string serial);
    virtual ~IBLT();

    void insert(uint64_t k, const std::vector<uint8_t> v);
    void erase(uint64_t k, const std::vector<uint8_t> v);

    // Returns true if a result is definitely found or not
    // found. If not found, result will be empty.
    // Returns false if overloaded and we don't know whether or
    // not k is in the table.
    bool get(uint64_t k, std::vector<uint8_t>& result) const;

    // Adds entries to the given sets:
    //  positive is all entries that were inserted
    //  negative is all entreis that were erased but never added (or
    //   if the IBLT = A-B, all entries in B that are not in A)
    // Returns true if all entries could be decoded, false otherwise.
    bool listEntries(std::set<std::pair<uint64_t,std::vector<uint8_t> > >& positive,
        std::set<std::pair<uint64_t,std::vector<uint8_t> > >& negative) const;
    
    /**
     * Turns this IBLT into a string. Can be deserialized by creating a new IBLT
     * object with the string constructor.
     * 
     * String is in hexadecimal, to condense it as much as possible
     * 
     * number of entries in this message: 8 bytes
     * list of all entries: variable bytes
     * 
     * per entry:
     * number of bytes in this entry:
     * @return A string of all the condensed important information.
     */
    std::string serializeEntries();
    
    // Subtract two IBLTs
    IBLT operator-(const IBLT& other) const;

    // For debugging:
    std::string DumpTable() const;
    
    

private:
    void _insert(int plusOrMinus, uint64_t k, const std::vector<uint8_t> v);

    size_t valueSize;
    uint64_t vs;


    //represents each cell in the iblt
    class HashTableEntry
    {
    public:
        int32_t count;
        uint64_t keySum;
        uint32_t keyCheck;
        std::vector<uint8_t> valueSum;
        uint32_t valueCheck;

        bool isPure() const;
        bool empty() const;
        void addValue(const std::vector<uint8_t> v);
    };

    //vector of all cells
    std::vector<HashTableEntry> hashTable;
};

#endif /* IBLT_H */
