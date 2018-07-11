/*
 * Created by Yair Kosowsky-Sachs
 * 
 * No telling what this might do. My thought is that it'll probably explode
 * or something cool like that.
 */
using namespace std;

#include "/home/regular/Documents/BU_2018/falafels/IBLT-Research/iblt.h"
#include "IBLTSync.h"
#include "DataObject.h"
#include "testFunctions.h"
#include "iblt.h"

IBLTSync::IBLTSync(size_t _expectedNumEntries, size_t _ValueSize) :
    iblt(size_t(_expectedNumEntries), sizeof(_ValueSize))
{
    key = 0;
    cout << "Hiya there! You've created an IBLT object." << endl;
}

bool IBLTSync::SyncClient(Communicant* commSync, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    commSync->resetCommCounters();
    commSync->commConnect();
    
    return true;
}

bool IBLTSync::SyncServer(Communicant* commSync, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    commSync->resetCommCounters();
    return true;
}

bool IBLTSync::addElem(DataObject* datum) {
    std::stringstream ss;
    ss << std::hex << datum->to_string();
    uint64_t x;
    ss >> x;
    iblt.insert(datum->getObjectID(), ToVec<uint64_t>(x));
    if(datum->getObjectID() == 19) {
        iblt.serializeEntries(1);
    }
    
    iblt.YairIsAwesome();
    
    return SyncMethod::delElem(datum);
}


bool IBLTSync::delElem(DataObject* datum) {
    std::stringstream ss;
    ss << std::hex << datum->to_string();
    uint64_t x;
    ss >> x;
    iblt.erase(key++, ToVec<uint64_t>(x));
    return SyncMethod::delElem(datum);
}

string IBLTSync::getName() {
    return "An IBLT Sync object";
}


bool IBLTSync::fromGenSynctoIBLT(std::set<std::pair<uint64_t, std::vector<uint8_t> > >& positive, std::set<std::pair<uint64_t, std::vector<uint8_t> > >& negative, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    return true;
}

bool IBLTSync::fromIBLTtoGenSync(std::set<std::pair<uint64_t, std::vector<uint8_t> > >& positive, std::set<std::pair<uint64_t, std::vector<uint8_t> > >& negative, list<DataObject*>& selfMinusOther, list<DataObject*>& otherMinusSelf) {
    return true;
}

IBLTSync::~IBLTSync() {

}