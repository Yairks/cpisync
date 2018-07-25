/*
 * This code is part of the CPISync project developed at Boston University:
 *      {@link http://nislab.bu.edu}
 * 
 * The code, explanation, references, API, and a demo can be found on this
 * web page.  The main theoretical basis for the approach can be found at
 * {@link http://ipsit.bu.edu/documents/ieee-it3-web.pdf}
 *   Y. Minsky, A. Trachtenberg, and R. Zippel,
 *   "Set Reconciliation with Nearly Optimal Communication Complexity",
 *   IEEE Transactions on Information Theory, 49:9.
 * 
 * Elements of the CPISync project code have been worked on, at various points, by:
 * @author Ari Trachtenberg
 * @author Sachin Agarwal 
 * @author Paul Varghese
 * @author Jiaxi Jin
 * @author Jie Meng
 * @author Alexander Smirnov
 * @version 2.02, 8/14/2014
 */

/*
 *  fork.h
 *  
 *
 *  Created by Jiaxi Jin on 6/18/10.
 *
 */

#ifndef FORKHANDLE_H
#define FORKHANDLE_H

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "GenSync.h"

int forkHandle(GenSync* client1, GenSync* client2, long &bytes, double &communTime, double &totalTime);


#endif