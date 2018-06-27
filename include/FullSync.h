/* This code is part of the CPISync project developed at Boston University.  Please see the README for use and references. */

/* 
 * File:   FullSync.h
 * Author: kaets
 *
 * Created on June 27, 2018, 9:37 AM
 */

#ifndef FULLSYNC_H
#define FULLSYNC_H

/**
 * A data structure that stores multi-sets of data. Unlike CPISync, which
 * efficiently reconciles differences between multi-sets, this data structure
 * takes an anti-entropy way of reconciling the sets, i.e. by simply exchanging
 * entire multi-sets from one peer to another.
 */
class FullSync {
public:
    FullSync();
    FullSync(const FullSync& orig);
    virtual ~FullSync();
private:

};

#endif /* FULLSYNC_H */

