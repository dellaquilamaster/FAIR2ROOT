#include <F2RReader.h>

//____________________________________________________
F2RReader::F2RReader() :
fCurrEvent(0),
fWordSize(gRun->GetFAIRWordSize())
{}
  
//____________________________________________________
unsigned int F2RReader::Open(const char * file_name)
{
  //
  //Opening file
  fInputFile.open(file_name,std::ios::binary);
  //
  if(fInputFile.is_open()==0) {
    //
    //Opening failed
    return 0;
    //
  }
  //
  
  //
  unsigned int InitialSize=fTheEvents.size();
  //
  
  //
  unsigned char ReadBuffer[4];
  //
  
  //I skip one word
  fInputFile.seekg(1*fWordSize);
  
  //Reading the number of words in the file inclusive of the first junk word and the word used to store the number of words
  fInputFile.read((char *)ReadBuffer,fWordSize);
  
  //Number of words to read excluding 16 initial words used for debugging, the junk word at the beginning and the word used to store the number of words
  const unsigned int FileLength = fair_char_to_word(ReadBuffer)-16-2;
  
//   printf("length=%lu\n", FileLength);
//   getchar();
    
  //Buffer used to read the entire file content
  unsigned char * FileBuffer = new unsigned char[FileLength*fWordSize];
  
  //I skip the header and go to the beginning of first event
  fInputFile.seekg(16*fWordSize);
    
  //
  //Reading the whole content of the file into the buffer (FileLength words)
  fInputFile.read((char *)FileBuffer,FileLength*fWordSize);
  //  
  
  //
  fInputFile.close();
  //
  
  //
  //Separating buffer into events
  for(unsigned int WordsRead=0; WordsRead<FileLength; ) {
    //Creation of a new event
    fair_event NewEvent;
    //Beginning of event
    NewEvent.event_size = 0;
    for( ; WordsRead<FileLength; WordsRead++) {
      //
      unsigned int TempWord = fair_char_to_word(FileBuffer+(fWordSize*WordsRead));
      //
      NewEvent.event_data.push_back(TempWord);
      //
//       printf("%u) %02x%02x %02x%02x\n", WordsRead, (unsigned char)*((char*)FileBuffer+(fWordSize*WordsRead)+1), (unsigned char)*((char*)FileBuffer+(fWordSize*WordsRead)+0), (unsigned char)*((char*)FileBuffer+(fWordSize*WordsRead)+3), (unsigned char)*((char*)FileBuffer+(fWordSize*WordsRead)+2));
//       printf("%x %x -> %o, mod=%d\n", TempWord, FTNMask, TempWord&FTNMask, TempWord&VSNMask-1);
      if(TempWord==0xFFFFFFFF) {
        //Reached end of the event
//         getchar();
        fTheEvents.push_back(NewEvent); //Saving the current event on the buffer
        WordsRead++;
        break;
      }
      //
      NewEvent.event_size++;
    }
  }
  //

  //
  //File successfully opened
  return fTheEvents.size()-InitialSize;
  //
}

//____________________________________________________
fair_event * F2RReader::NextEvent()
{  
  return fCurrEvent<fTheEvents.size() ? &fTheEvents[fCurrEvent++] : 0;  
}

//____________________________________________________
unsigned long F2RReader::Size() const
{  
  return fTheEvents.size();  
}

//
// This function converts an array of char corresponing to the 
// succession of bits representing data, into an integer
// representing the longword
// WARNING: only assumption is that the size in bit of a char is 8!
unsigned int fair_char_to_word(unsigned char * data)
{
  unsigned int Converted=0;
  const unsigned int size_of_word = gRun->GetFAIRWordSize();
  for(int i=0; i<size_of_word; i++) {
    Converted = Converted | (data[i] << (size_of_word-(i+1))*8 );
  }
  return Converted;
}
//
