#ifndef F2RCONVERTER_H
#define F2RCONVERTER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>
#include <TTree.h>
#include <TFile.h>
#include <Bytes.h>
#include <Byteswap.h>

#include <F2RReader.h>
#include <M2RMidasRootEvent.h>
#include <F2RRunInfo.h>
#include <F2RElectronics.h>
#include <F2RModuleMask.h>
#include <F2RDef.h>
#include <shared.h>

class F2RConverter
{
public :
  
  F2RConverter();
  ~F2RConverter();
  
  void RegisterReader(F2RReader *);
  int InitializeConverter();
  
  const char * GetOutputFileName() const;
  
  void Process();
  void EndProcess();
  
private :
  TFile * fTheFile;
  TTree * fTheTree;
  M2RMidasRootEvent * fevt;
  F2RReader * fTheReader;
  std::string fOutputFileName;
  
  void FillEvent();  
  
  void PrintSummary() const;
  
  clock_t fStartTime;
  double fTimeElapsed;
  
  unsigned long fParityErrors;
  unsigned long fLengthErrors;
  unsigned long fDecorrelationErrors;
};

bool TestParity(unsigned int);
int TestEventConsistency(fair_event *);

#endif
