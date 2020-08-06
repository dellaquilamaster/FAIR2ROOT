#ifndef F2RREADER_H
#define F2RREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <vector>
#include <Bytes.h>
#include <Byteswap.h>

#include <F2RRunInfo.h>
#include <F2RDef.h>
#include <shared.h>

//
typedef struct fair_event_ {
  unsigned int event_size;
  std::vector<unsigned int> event_data;  
} fair_event;
//

//
unsigned int fair_char_to_word(unsigned char *);
//

class F2RReader
{
public :
  F2RReader();                         //!
  
  unsigned int Open(const char *);     //Open input file and read all the content in memory
  
  fair_event * NextEvent();            //Returns the next event from the buffer
  
  unsigned long Size() const;          //Returns the number of events in buffer
  
private :
  std::ifstream fInputFile;            //!
  
  std::vector<fair_event> fTheEvents;  //!
  unsigned long fCurrEvent;            //!
  const unsigned int fWordSize;        //Size of a word in char
};

#endif
