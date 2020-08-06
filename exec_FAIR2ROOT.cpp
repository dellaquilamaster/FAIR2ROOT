/*
 * FAIR2ROOT program
 * created by Daniele Dell'Aquila (ddellaquila@uniss.it)
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <F2RConverter.h>
#include <F2RReader.h>
#include <F2RRunInfo.h>

#include <shared.h>

void F2RPrintLogo() {
  printf("\n\nFAIR2ROOT\n");
  printf("Created by Daniele Dell'Aquila (ddelalquila@uniss.it)\n");
  printf("A Universal unpacker for the FAIR DAQ created for the NUCL-EX collaboration.\n");
  printf("v_1.0\n\n");
  
  return;
}

int ReadInput(int argc, char ** argv, std::string & Source)
{
  int Nread=0;
  
  for(int i=1; i<argc; i++) {
    std::string AnImput(argv[i]);
    if(AnImput.find("--run=")!=std::string::npos) {
      std::string TheValue(AnImput.substr(AnImput.find("=")+1));
      Source.assign(TheValue);
      Nread++;
    }
  }
  
  return Nread;
}

int main (int argc, char ** argv)
{
  //
  //Print logo
  F2RPrintLogo();
  //
  
  //
  //Reading Input
  std::string Source;
  if(ReadInput(argc,argv,Source)<=0) {
    printf("Error: missing valid source file!\nPlease use --run=xxx command to specify a run number.\nAborting!\n"); 
    exit(1);
  }
  //
    
  //
  //Initializing run info class
  gRun=new F2RRunInfo(Source.c_str());
  if(gRun->InitClass("config/FAIR2ROOT.conf")<=0)  {
    printf("Error while intializing RunInfo class for run %s.\nAborting!",Source.c_str());
    exit(2);
  }
  //
  
  //
  //Initializing experiment electronics layout
  gLayout = new F2RElectronics();
  if(gLayout->Init()<=0) {
    printf("Error while intializing Electronics class for run %s.\nAborting!",Source.c_str());
    exit(3);
  }
  //
  
  //
  //Creating FAIR Reader
  F2RReader * TheReader = new F2RReader();
  //
  
  //
  //Opening all Input Files related to the run
  for(int curr_file=1; ; curr_file++) {
    std::string run_file_name(Form("%s/%s_%06d.dat", gRun->GetRunFilePathName(), gRun->GetRunNumber(), curr_file));
    
    const unsigned int SizeRead=TheReader->Open(run_file_name.c_str());
        
    if(SizeRead==0 && curr_file>1) {
      printf("\nReached end of run, converting data into ROOT format\n");
      break;
    } else if (SizeRead==0 && curr_file==1) {      
      printf("\nError: failed to open source file %s\nAborting!\n", run_file_name.c_str()); 
      exit(4);
    }
    
    printf("Successfully read file %s\n", run_file_name.c_str());     
  }
  //
  
  //
  //Creating Root Converter
  F2RConverter * TheRootConverter = new F2RConverter();
  //
  
  //
  //Registering Reader
  TheRootConverter->RegisterReader(TheReader);
  //
  
  //
  //Initializing Output Tree
  if (TheRootConverter->InitializeConverter()!=0) {
    printf("Error: failed to create output file in folder %s.\nAborting!", gRun->GetF2RROOTFilePath());
    exit(3);
  }
  //
  
  //
  //FAIR to ROOT conversion
  TheRootConverter->Process();
  //
  
  //
  //Closing output file
  TheRootConverter->EndProcess();
  //
 
  printf("\nSuccessfully created file: %s\n\n", TheRootConverter->GetOutputFileName());
  return 0;
}
