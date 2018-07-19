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
    commSync->resetCommCounters();
    commSync->commConnect();
    
    return true;
}

bool IBLTSync::SyncServer(Communicant* commSync, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    commSync->resetCommCounters();
    commSync->commListen();
    
    std::string str, read;
    int entries = 0;
    
    bool keepReading = true;
    while(keepReading) {
        read = commSync->commRecv(1);
        str += read;
        
        //Check if we're done here
        if(read.compare("]") == 0) {
            read = commSync->commRecv(1);
            
            //If it's good, append this read thing, otherwise mark that we're done.
            keepReading = (read.compare("[") == 0);
            
            if(keepReading) str+=read; 
            
            entries++;
        }
    }
    
    IBLT received(str);
    
    std::set<std::pair<uint64_t,std::vector<uint8_t> > > negativeValues;
    std::set<std::pair<uint64_t,std::vector<uint8_t> > > positiveValues;
    
    IBLT diff = iblt - received;
    
    bool successful = diff.listEntries(positiveValues, negativeValues);
    
    fromIBLTtoGenSync(positiveValues, negativeValues, selfMinusOther, otherMinusSelf);
    return successful;
}

bool IBLTSync::addElem(DataObject* datum) {
    std::stringstream ss;
    ss << datum->to_string();
    uint64_t x;
    ss >> x;
    
    std::vector<uint8_t> vec = ToVec((int) x);
    while(vec.size() < valueSize) {
        vec.push_back('0');
    }
    //Make sure vector is long enough
    iblt.insert(x, vec);
    
    return SyncMethod::addElem(datum);
}


bool IBLTSync::delElem(DataObject* datum) {
    std::stringstream ss;
    ss << std::hex << datum->to_string();
    uint64_t x;
    ss >> x;
    iblt.erase(x, ToVec(x));
    return SyncMethod::delElem(datum);
}

string IBLTSync::getName() {
    return "An IBLT Sync object";
}

bool IBLTSync::fromIBLTtoGenSync(std::set<std::pair<uint64_t, std::vector<uint8_t> > >& positive, std::set<std::pair<uint64_t, std::vector<uint8_t> > >& negative, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    std::set<std::pair<uint64_t, std::vector<uint8_t> > >::iterator entry = positive.begin();
    
    for(; entry != positive.end(); entry++) {
        DataObject* datum = new DataObject(std::to_string(FromVec(entry->second)));
        
        selfMinusOther.push_back(datum);
    }
    
    entry = negative.begin();
    for(; entry != negative.end(); entry++) {
        DataObject* datum = new DataObject(std::to_string(FromVec(entry->second)));
        
        otherMinusSelf.push_back(datum);
    }
    return true;
}

IBLTSync::~IBLTSync() {

}