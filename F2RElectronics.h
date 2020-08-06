#ifndef F2RELECTRONICS_H
#define F2RELECTRONICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <fstream>

#include <F2RModuleMask.h>
#include <F2RRunInfo.h>

#include <shared.h>

class F2RElectronics
{
public:
  F2RElectronics();
  ~F2RElectronics();
  
  //
  int Init();
  //
  
  //
  unsigned int Size () const;
  F2RModuleMask * GetModuleMask (int);
  //
  
private:
  std::map <int, F2RModuleMask *> fMasks;
  
  int ParseDefineConfigLine(const char *);
} ;

#endif
