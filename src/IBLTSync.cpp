/*
 * Created by Yair Kosowsky-Sachs
 * 
 * No telling what this might do. My thought is that it'll probably explode
 * or something cool like that.
 */
using namespace std;

#include "IBLTSync.h"
#include "DataObject.h"
#include "testFunctions.h"
#include "iblt.h"

IBLTSync::IBLTSync(size_t _expectedNumEntries, size_t _valueSize) :
    iblt(size_t(_expectedNumEntries), _valueSize),
        valueSize(_valueSize)
{
    key = 0;
}

bool IBLTSync::SyncClient(Communicant* commSync, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    // call parent method for bookkeeping
    SyncMethod::SyncClient(commSync, selfMinusOther, otherMinusSelf);
    commSync->commConnect();

    // then what?

    return true;
}

bool IBLTSync::SyncServer(Communicant* commSync, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    // call parent method for bookkeeping
    SyncMethod::SyncServer(commSync, selfMinusOther, otherMinusSelf);
    commSync->commListen();

    std::stringstream str;
    std::string read;
    int entries = 0;
    
    bool keepReading = true;
    while(keepReading) {
        read = commSync->commRecv(1);
        str << read;
        
        //Check if we're done here
        if(read == "]") {
            read = commSync->commRecv(1);
            
            //If it's good, append this read thing, otherwise mark that we're done.
            keepReading = (read.compare("[") == 0);
            
            if(keepReading) str << read;
            
            entries++;
        }
    } // could be rewritten using Communicant methods (Communicant::commRecv_string, etc.)
    
    IBLT received(str.str());
    
    std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValues, positiveValues;

    IBLT diff = iblt - received;
    
    bool successful = diff.listEntries(positiveValues, negativeValues);
    
    fromIBLTtoGenSync(positiveValues, negativeValues, selfMinusOther, otherMinusSelf);
    return successful;
}

bool IBLTSync::addElem(DataObject* datum) {
    // If the parent addElem fails, then don't continue execution
    if(!SyncMethod::addElem(datum))
        return false;

    // Lossy... using a ZZ would be optimal since this is how DataObjects are represented
    // Works for DataObjects representing uintegers <= uint64_t max.
    std::stringstream ss;
    ss << datum->to_string();
    uint64_t x;
    ss >> x;

    std::vector<uint8_t> vec = ToVec((int) x);

    //Make sure vector is long enough
    while(vec.size() < valueSize) {
        vec.push_back(0);
    }

    iblt.insert(x, vec);
    return true;
}


bool IBLTSync::delElem(DataObject* datum) {
    // If the parent delElem fails, then don't continue execution
    // Needs to be merged with trachten/cpisync master branch to incorporate a bugfix for SyncMethod::delElem
    if(!SyncMethod::delElem(datum))
        return false;

    std::stringstream ss;
    ss << datum->to_string();
    uint64_t x;
    ss >> x;

    iblt.erase(x, ToVec(x));

    return true;
}

bool IBLTSync::fromIBLTtoGenSync(std::set<std::pair<uint64_t, std::vector<uint8_t> > >& positive, std::set<std::pair<uint64_t, std::vector<uint8_t> > >& negative, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    // could typedef the set<pair> thing at some point to save some typing in the future
    for(auto entry : positive) {
        // Fix to DataObject in trachten/cpisync master should remove the need for std::to_string
        DataObject* datum = new DataObject(std::to_string(FromVec(entry.second)));
        
        selfMinusOther.push_back(datum);
    }

    for(auto entry : negative) {
        // Fix to DataObject in trachten/cpisync master should remove the need for std::to_string
        DataObject* datum = new DataObject(std::to_string(FromVec(entry.second)));
        
        otherMinusSelf.push_back(datum);
    }
    return true;
}

IBLTSync::~IBLTSync() = default;