/*
 * shared.h
 * Created by Daniele Dell'Aquila (daniele.dellaquila@irb.hr)
 * 
 * This file contains the declaration of the global variables used by
 * Midas2ROOT program.
 */

#ifndef SHARED_H
#define SHARED_H

class F2RRunInfo;
class F2RElectronics;

extern F2RRunInfo * gRun;
extern F2RElectronics * gLayout;
extern const unsigned int MAX_MULT_ROOTEVENT;

#endif
