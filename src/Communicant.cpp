/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

#include <NTL/RR.h>
#include "Auxiliary.h"
#include "Communicant.h"
#include "CommSocket.h"
#include "Logger.h"
#include "DataObject.h"

Communicant::Communicant() {
    resetCommCounters();
    xferBytesTot = recvBytesTot = 0;
    createTime = clock();
    MOD_SIZE = NOT_SET;
}

Communicant::~Communicant() {
}

void Communicant::resetCommCounters() {
    xferBytes = recvBytes = 0;
    resetTime = clock();
}

string Communicant::getName() {
    return "No name available";
}

long Communicant::getXmitBytes() const {
    return xferBytes;
}

long Communicant::getRecvBytes() {
    return recvBytes;
}

long Communicant::getXmitBytesTot() {
    return xferBytes;
}

long Communicant::getRecvBytesTot() {
    return recvBytes;
}

clock_t Communicant::getResetTime() {
    return resetTime;
}

clock_t Communicant::getTotalTime() {
    return createTime;
}

void Communicant::addXmitBytes(long numBytes) {
    xferBytes += numBytes;
    xferBytesTot += numBytes;
}

void Communicant::addRecvBytes(long numBytes) {
    recvBytes += numBytes;
    recvBytesTot += numBytes;
}

bool Communicant::establishModRecv(bool oneWay /* = false */) {
    NTL::ZZ otherModulus = commRecv_ZZ();

    if (otherModulus != NTL::ZZ_p::modulus()) {
        Logger::gLog(Logger::COMM, "ZZ_p moduli do not match: " + toStr(NTL::ZZ_p::modulus) + " (mine) vs " + toStr(otherModulus) + " (other).");
        if (!oneWay) // one way reconciliation does not send any data
            commSend(SYNC_FAIL_FLAG);
        return false;
    }
    MOD_SIZE = NumBytes(NTL::ZZ_p::modulus()); // record the modulus size
    if (!oneWay)
        commSend(SYNC_OK_FLAG);
    return true;
}

bool Communicant::establishModSend(bool oneWay /* = false */) {
    commSend(NTL::ZZ_p::modulus());
    MOD_SIZE = NumBytes(NTL::ZZ_p::modulus());
    if (oneWay)
        return true;  // i.e. don't want for a response
    else
        return (commRecv_byte() != SYNC_FAIL_FLAG);
}

void Communicant::commSend(const ustring toSend, const int numBytes) {
    Logger::gLog(Logger::COMM_DETAILS, "... attempting to send: ustring: "
            + base64_encode(reinterpret_cast<const char *>(toSend.data()), numBytes));

    const char *sendptr = reinterpret_cast<const char *> ((unsigned char *) toSend.data());
    commSend(sendptr, numBytes);
}

void Communicant::commSend(const string str) {
    Logger::gLog(Logger::COMM, "... attempting to send: string " + str);
    commSend((long) str.length());
    commSend(str.data(), str.length());
}

void Communicant::commSend(const ustring ustr) {

    Logger::gLog(Logger::COMM, "... attempting to send: ustring " + ustrToStr(ustr));
    commSend((long) ustr.length());
    commSend(ustr.data(), ustr.length());
}

void Communicant::commSend(DataObject& dob) {

    Logger::gLog(Logger::COMM, "... attempting to send: DataObject " + dob.to_string());

    // for now, just send the data object as a string ... this can be optimized
    commSend(dob.to_string());
}

void Communicant::commSend(DataObject& dob,bool prio) {

    Logger::gLog(Logger::COMM, "... attempting to send: DataObject " + dob.to_priority_string());

    // for now, just send the data object as a string ... this can be optimized
    commSend(dob.to_priority_string());
}

void Communicant::commSend(const list<DataObject*> &lst) {
    Logger::gLog(Logger::COMM, "... attempting to send: DataObject list ...");

    list<DataObject*>::const_iterator it;
    commSend((long) lst.size()); // the number of elements in the list

    for (it = lst.begin(); it != lst.end(); it++)
        commSend(**it);
}

void Communicant::commSend(double num) {
    // Convert to an RR type and send mantissa and exponent

    Logger::gLog(Logger::COMM, "... attempting to send: double " + toStr(num));

    NTL::RR num_RR;
    num_RR = num;
    commSend(num_RR.mantissa());
    commSend(-num_RR.exponent()); // exponent should always be negative or 0
}

void Communicant::commSend(const long num) {

    unsigned char toSend[XMIT_LONG];
    BytesFromZZ(toSend, NTL::to_ZZ(num), XMIT_LONG);
    Logger::gLog(Logger::COMM, "... attempting to send: long " + toStr(num));
    commSend(ustring(toSend, XMIT_LONG), XMIT_LONG);
}

void Communicant::commSend(const byte bt) {

    Logger::gLog(Logger::COMM, string("... attempting to send: byte num ") + toStr((int) bt));
    commSend(&bt, 1);
}

void Communicant::commSend(const int num) {

    unsigned char toSend[XMIT_INT];
    BytesFromZZ(toSend, NTL::to_ZZ(num), XMIT_INT);
    Logger::gLog(Logger::COMM, "... attempting to send: int " + toStr(num));
    commSend(ustring(toSend, XMIT_INT), XMIT_INT);
}

void Communicant::commSend(const NTL::ZZ_p& num) {

    Logger::gLog(Logger::COMM, "... attempting to send: ZZ_p " + toStr(num));

    // send like a ZZ, but with a known size
    unsigned char toSend[MOD_SIZE];

    BytesFromZZ(toSend, rep(num), MOD_SIZE);
    commSend(ustring(toSend, MOD_SIZE), MOD_SIZE);
}

void Communicant::commSend(const NTL::vec_ZZ_p& vec) {
    Logger::gLog(Logger::COMM, "... attempting to send: vec_ZZ_p " + toStr(vec));

    // pack the vec_ZZ_p into a big ZZ and send it along    
    NTL::ZZ result;
    result = 0;

    for (int ii = vec.length() - 1; ii >= 0; ii--) // append in reverse order to make decoding easier
        result = (result * (NTL::ZZ_p::modulus()+1)) + rep(vec[ii])+1; // added 1 to avoid insignificant 0's in the lead of the vector
    commSend(result);
}

NTL::vec_ZZ_p Communicant::commRecv_vec_ZZ_p() {
    // unpack the received ZZ into a vec_ZZ_p
    NTL::ZZ received = commRecv_ZZ();
    NTL::vec_ZZ_p result;

     
    while (received != 0) {
        NTL::ZZ divisor, remainder;
        DivRem(divisor, remainder, received, NTL::ZZ_p::modulus()+1);

        append(result, to_ZZ_p(remainder-1)); // subtract back the 1 that was added when sent
        received = divisor;
    }

    Logger::gLog(Logger::COMM, "... received vec_ZZ_p " + toStr(result));

    return result;
}



void Communicant::commSend(const NTL::ZZ& num, int size) {
    Logger::gLog(Logger::COMM, "... attempting to send: ZZ " + toStr(num));

    int num_size = (size == NOT_SET ? NumBytes(num) : size);
    if (num_size == 0) num_size = 1; // special case for sending the integer 0 - need one bit
    unsigned char toSend[num_size];

    if (size == NOT_SET) // first send the number of bytes represented by the ZZ
        commSend(num_size);

    // next send the actual number, as a byte sequence
    BytesFromZZ(toSend, num, num_size);

    commSend(ustring(toSend, num_size), num_size);

}

ustring Communicant::commRecv_ustring(long numBytes) {
    string received = commRecv(numBytes);
    ustring result((const unsigned char *) (received.data()), numBytes);
    Logger::gLog(Logger::COMM_DETAILS, "... received ustring: " +
            base64_encode(reinterpret_cast<const char *>(result.data()), numBytes));

    return (result); // return the result as a ustring
}

string Communicant::commRecv_string() {
    long sz = commRecv_long();
    string str = commRecv(sz);

    //Logger::gLog(Logger::COMM, "... received: string " + str);

    return str;
}

ustring Communicant::commRecv_ustring() {
    long sz = commRecv_long();
    ustring ustr = commRecv_ustring(sz);

    Logger::gLog(Logger::COMM, "... received: ustring " + ustrToStr(ustr));

    return ustr;
}

DataObject* Communicant::commRecv_DataObject() {
    DataObject *res = new DataObject(commRecv_string());
    Logger::gLog(Logger::COMM, "... received: DataObject " + res->to_string());

    return res;
}

DataObject* Communicant::commRecv_DataObject_Priority() {
    string str = commRecv_string();
    string prio = str.substr(0, str.find(','));
    str = str.substr(str.find(',') + 1);
    DataObject * res = new DataObject(str);
    res->setPriority(strTo<NTL::ZZ > (prio));
    Logger::gLog(Logger::COMM, "... received: DataObject " + res->to_string());
    return res;
}

// receives a list of data objects

list<DataObject*> Communicant::commRecv_DoList() {
    list<DataObject*> result;

    long numDiffs = commRecv_long();
    for (long ii = 0; ii < numDiffs; ii++) {
        DataObject *dobp = commRecv_DataObject();
        result.push_back(dobp);
    }

    Logger::gLog(Logger::COMM, "... received: DataObject list ...");

    return result;
}

double Communicant::commRecv_double() {
    NTL::ZZ mantissa = commRecv_ZZ();
    long exponent = -commRecv_long();
    NTL::RR result_RR = MakeRR(mantissa, exponent);
    Logger::gLog(Logger::COMM, "... received double " + toStr(result_RR));

    return to_double(result_RR);
}

long Communicant::commRecv_long() {
    ustring received = commRecv_ustring(XMIT_LONG);
    NTL::ZZ num = NTL::ZZFromBytes(received.data(), XMIT_LONG);
    Logger::gLog(Logger::COMM, "... received long " + toStr(num));

    return to_long(num);
}

int Communicant::commRecv_int() {
    ustring received = commRecv_ustring(XMIT_INT);
    NTL::ZZ num = NTL::ZZFromBytes(received.data(), XMIT_INT);
    Logger::gLog(Logger::COMM, "... received int " + toStr(num));

    return to_int(num);
}

byte Communicant::commRecv_byte() {
    string received = commRecv(1);
    Logger::gLog(Logger::COMM, string("... received byte num ") + toStr((int) received[0]));

    return received[0];
}

NTL::ZZ_p Communicant::commRecv_ZZ_p() {
    // the size is fixed by the connection initialization phase
    ustring received = commRecv_ustring(MOD_SIZE);
    NTL::ZZ_p result = NTL::to_ZZ_p(NTL::ZZFromBytes(received.data(), MOD_SIZE));

    Logger::gLog(Logger::COMM, "... received ZZ_p " + toStr(result));

    return result;
}

NTL::ZZ Communicant::commRecv_ZZ(int size) {
    int num_size;
    ustring received;
    if (size == 0)
        num_size = commRecv_int(); // first receive the number of bytes represented by the ZZ
    else
        num_size = size;

    // second receive the actual ZZ
    received = commRecv_ustring(num_size);

    NTL::ZZ result = NTL::ZZFromBytes(received.data(), num_size);
    Logger::gLog(Logger::COMM, "... received ZZ " + toStr(result));

    return result;
}
