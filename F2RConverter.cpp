#include <F2RConverter.h>

//____________________________________________________
F2RConverter::F2RConverter() :
fTheFile(0),
fTheTree(0),
fevt(new M2RMidasRootEvent()),
fTheReader(0),
fParityErrors(0),
fLengthErrors(0),
fDecorrelationErrors(0)
{}

//____________________________________________________
F2RConverter::~F2RConverter()
{
  delete fevt;
  delete fTheTree;
  delete fTheFile;
}

//____________________________________________________
int F2RConverter::InitializeConverter()
{  
  //
  //Intializing output file name
  fOutputFileName.assign(Form("%srun_%s.root", gRun->GetF2RROOTFilePath(),gRun->GetRunNumber()));
  //
  
  //
  //Opening output ROOT file
  fTheFile = new TFile(fOutputFileName.c_str(), "RECREATE");
  //
  if(fTheFile->IsZombie()) {
    return -1; 
  }
  //
  
  //
  //Creating output tree
  fTheTree = new TTree("FAIR","FAIR2ROOT Output Tree");
  //Initializing Branch
  fTheTree->Branch("DAQ.", "M2RMidasRootEvent", fevt);
  //
  
  //
  fTheTree->SetAutoSave(500000);
  //
  
  return 0;
}

//____________________________________________________
void F2RConverter::RegisterReader(F2RReader * NewReader)
{
  fTheReader = NewReader;  
}

//____________________________________________________
const char * F2RConverter::GetOutputFileName() const
{
  return fOutputFileName.c_str();
}

//____________________________________________________
void F2RConverter::Process()
{ 
  //
  fStartTime=clock();
  //
  //Reading event-by-event the Midas file
  fair_event * AnEvent;
  for (unsigned long jentry=0; (AnEvent=fTheReader->NextEvent()); jentry++) {
    //Display progress
    if(jentry%10000==0) {
      fTimeElapsed = (double)(clock() - fStartTime)/CLOCKS_PER_SEC;
      std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/fTheReader->Size()) << " %";
      std::cout << "   [";
      int printindex=0;
      for(; printindex<int(100*double(jentry)/fTheReader->Size()); printindex+=5) std::cout << "=";
      for(; printindex<100; printindex+=5) std::cout << " ";
      std::cout << "]   " << "elapsed time " << std::setprecision(1) <<
      (fTimeElapsed<60 ? fTimeElapsed : (fTimeElapsed<3600 ? fTimeElapsed/60 : fTimeElapsed/3600)) <<
      (fTimeElapsed<60 ? " s; " : (fTimeElapsed<3600 ? " m; " : " h; "));
      if(jentry>0) {
        double time_remaining = (fTimeElapsed/jentry)*(fTheReader->Size()-jentry);
        std::cout << " estimated remaining time " << std::setprecision(1) <<
        (time_remaining<60 ? time_remaining : (time_remaining<3600 ? time_remaining/60 : time_remaining/3600)) <<
        (time_remaining<60 ? " s      " : (time_remaining<3600 ? " m      " : " h      "));
      }
      std::cout << "\r";
      std::cout.flush();
    }
    
    //
    //Checking consistency of the event
    const int ErrorCode = TestEventConsistency(AnEvent);
    switch (ErrorCode) {
      case (1) :
        fDecorrelationErrors++;
        break;
      case (2) :
        fLengthErrors++;
        break;
      case (3) :
        fDecorrelationErrors++;
        break;
      default :
        break;
    }
    if(ErrorCode!=0) continue;
    //
    
    //
    //Reset event multiplicity
    fevt->fmulti=0;
    //
    
    //
    unsigned int EventLenght=AnEvent->event_size;
    unsigned int * EventData=AnEvent->event_data.data();
    for(int i_glob=0; i_glob<EventLenght; ) 
    {
      //
      //Pointer to the current event
      unsigned int * CurrentEventData = EventData+i_glob;
      //
      
      //Processing one module
      unsigned int NumWordsInModule=0;
      //
      for( ; (CurrentEventData[NumWordsInModule]&FTNMask)==0; NumWordsInModule++) {
      }
      //
      const int NumMod=(CurrentEventData[NumWordsInModule]&VSNMask) - 1;
      F2RModuleMask * ModuleMask = gLayout->GetModuleMask(NumMod);
      //
      
      //
      //Loop on all module data to verify the internal ordering of data
      for(unsigned int i_module=0; i_module<NumWordsInModule; i_module++)
      {       
        fevt->fgid[fevt->fmulti]=NumMod;
        fevt->fch[fevt->fmulti]=ModuleMask->DWN(EventData[i_glob]);
        fevt->fampl[fevt->fmulti]=EventData[i_glob];
        fevt->fmulti++;
      }
      //
      i_glob+=NumWordsInModule+1; //+1 is because the last word in the event is the footword
      //
    }
    //
    
    //
    //Filling the entry of the current event
    FillEvent();
    //
  }
  //
}

//____________________________________________________
void F2RConverter::FillEvent()
{
  fTheTree->Fill(); 
}

//____________________________________________________
void F2RConverter::EndProcess()
{
  //Writing TTree to TFile
  fTheTree->AutoSave();
  //
  
  //
  //Closing output file
  fTheFile->Close();
  //
  
  //
  //Printing summary
  PrintSummary();
  //
}


//____________________________________________________
void F2RConverter::PrintSummary() const
{
  printf("\n\nUnpakced %lu events in %.1f seconds\n", fTheReader->Size(), fTimeElapsed);
  printf("Parity errors: %lu\n", fParityErrors);
  printf("Length errors: %lu\n", fLengthErrors);
  printf("Decorrelation errors: %lu\n", fDecorrelationErrors);
  printf("---\n");
}

//____________________________________________________
int TestEventConsistency(fair_event * TheEvent)
{
  unsigned int * EventData = TheEvent->event_data.data();
  unsigned long EventLenght=TheEvent->event_size;
  
  for(unsigned int i_glob=0; i_glob<EventLenght ; )
  {
    //
    //Pointer to the current event
    unsigned int * CurrentEventData = EventData+i_glob;
    //
    
    //Processing one module
    unsigned int NumWordsInModule=0;
    //
    for( ; (CurrentEventData[NumWordsInModule]&FTNMask)==0; NumWordsInModule++) {
      //
      //Testing word parity
      if(!TestParity(CurrentEventData[NumWordsInModule])) return 1;
      //
    }
    //Checking module length consistency
    //The effective size of the module has to be the same of the size reported in the footword
    const unsigned int footword_module_length = ((CurrentEventData[NumWordsInModule])&VDWMask)>>VDWOff;
    if(NumWordsInModule!=footword_module_length) return 2;
    //
    //
    const int NumMod=(CurrentEventData[NumWordsInModule]&VSNMask) - 1;
    F2RModuleMask * ModuleMask = gLayout->GetModuleMask(NumMod);
    //
    //Loop on all module data to verify the internal ordering of data
    for(unsigned int i_module=0; i_module<NumWordsInModule-1; i_module++) {
      if(ModuleMask->DWN(CurrentEventData[i_module]) >= ModuleMask->DWN(CurrentEventData[i_module+1])) {
        return 3;
      }
    }
    //
    i_glob+=NumWordsInModule+1; //+1 is because the footword of the module was not counted before
  }
  
  //No errors found
  return 0;
}

//____________________________________________________
bool TestParity(unsigned int WordToCheck)
{
  int sum=0;
  
  for(int i=0; i<32; i++)
  {
    sum+=WordToCheck&1;
    WordToCheck>>=1;
  }
  
  return sum%2;  
}
