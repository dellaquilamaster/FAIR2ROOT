#ifndef F2RMODULEMASK_H
#define F2RMODULEMASK_H

#include <string.h>

/*
 * Possible module_type:
 * 
 * ADC  --> ADC 9418V
 * TDC  --> TDC 9418T
 * SEGC --> Segment Controller
 * SCL  --> Scaler
 * 
 */

class F2RModuleMask
{
public:
  F2RModuleMask(const char *);
  ~F2RModuleMask();
  
  unsigned int DWN   (unsigned long);
  unsigned int VDW   (unsigned long);
  unsigned int Data  (unsigned long);
  bool         footer(unsigned long);
  
private:
  unsigned int DWN_;
  unsigned int VDW_;
  unsigned int Data_;
  unsigned int footer_;
  unsigned int DWN_offset;
  unsigned int VDW_offset;
  unsigned int Data_offset;
  unsigned int footer_offset;
} ;

#endif 
