#include <F2RRunInfo.h>

//________________________________________________
F2RRunInfo::F2RRunInfo(const char * run_number) :
fRunName(run_number),
fRunFolderName(fRunName)
{}

//________________________________________________
F2RRunInfo::~F2RRunInfo()
{}

//________________________________________________
int F2RRunInfo::InitClass(const char *file_name)
{
  int NLinesRead=0;

  //Set general setup configuration
  NLinesRead += LoadSetupConfiguration(file_name);
  
  //Load run-by-run information
  NLinesRead += LoadRunConfiguration(file_name,fRunName.c_str());

  return NLinesRead;
}

//________________________________________________
int F2RRunInfo::LoadSetupConfiguration(const char *file_name)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }

  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("set ")!=std::string::npos) {
      ParseSetConfigLine(LineReadCommentLess.c_str());
    }

    NRead++;
  }
  FileIn.close();

  return NRead;
}

//________________________________________________
int F2RRunInfo::LoadRunConfiguration(const char *file_name, const char * run_num)
{
  std::ifstream FileIn(file_name);
  if(!FileIn.is_open()) {
    return -1;
  }

  int NRead=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("set ")!=std::string::npos) {
      ParseSetConfigLineRunInfo(LineReadCommentLess.c_str(), run_num);
    }

    NRead++;
  }
  FileIn.close();

  return NRead;
}

const char * F2RRunInfo::GetName() const
{
  return fExperimentName.c_str();
}

const char * F2RRunInfo::GetTitle() const
{
   return fExperimentTitle.c_str(); 
}

const char * F2RRunInfo::GetRunNumber() const
{
   return fRunName.c_str(); 
}

const char * F2RRunInfo::GetRunFolderName() const
{
  return fRunFolderName.c_str();  
} 

const char * F2RRunInfo::GetRunFilePathName() const
{
  return Form("%s%s",fBinaryFilePath.c_str(), fRunFolderName.c_str());  
} 

int F2RRunInfo::GetFAIRWordSize() const
{
  return fFAIRWordSize;  
} 

const char * F2RRunInfo::GetBinaryFilePath() const
{
  return fBinaryFilePath.c_str();  
} 

const char * F2RRunInfo::GetF2RROOTFilePath() const
{
  return fF2RRootFilePath.c_str();  
}          

const char * F2RRunInfo::GetElectronicsConfigFileName() const
{
  return fElectronicsConfigurationFileName.c_str();  
}          

//________________________________________________
void F2RRunInfo::ParseSetConfigLine(const char *line_to_parse)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("set ")+4)); //remove set command

  std::istringstream LineStream(LineToParse);

  std::string ValueToSet;
  LineStream>>ValueToSet;
  std::string NewValue(LineToParse.substr(LineToParse.find("\"")+1,LineToParse.find_last_of("\"")-(LineToParse.find("\"")+1)));

  if(ValueToSet.compare("EXPERIMENT_NAME")==0) {
    fExperimentName.assign(NewValue);
  } else if (ValueToSet.compare("EXPERIMENT_TITLE")==0) {
    fExperimentTitle.assign(NewValue);
  } else if (ValueToSet.compare("BINARY_FILE_PATH")==0) {
    if(LineToParse.find("--run")==std::string::npos) { //EvtFileName might be different run-by-run, if --run is specified don't set it now but in ParseSetConfigLineRunInfo
      fBinaryFilePath.assign(NewValue);
    }
  } else if (ValueToSet.compare("F2R_ROOT_FILE_PATH")==0) {
    fF2RRootFilePath.assign(NewValue);
  } else if (ValueToSet.compare("FAIR_WORD_SIZE")==0) {
    fFAIRWordSize=std::stoi(NewValue);
  } else if (ValueToSet.compare("FAIR_CONFIGURATION_FILE")==0) {
    fElectronicsConfigurationFileName.assign(NewValue);
  }

  return;
}

//________________________________________________
void F2RRunInfo::ParseSetConfigLineRunInfo(const char *line_to_parse, const char * run_num)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("set ")+4)); //remove set command

  std::istringstream LineStream(LineToParse);

  std::string ValueToSet;
  LineStream>>ValueToSet;
  std::string NewValue;
  std::string Option;
  bool RunFound=false;

  //NOTE: for a future improvement take into account more possible options not only --run and --exclude
  //A --run or --exclude option can contain or "," or "-" as a separator, not combination of both
  // Loop on the option strings, every time one finds -- this is an option string, e.g. --run, --exclude
  // 2018/08/20 Included the possibility of specifying only 1 run with --run or --exclude options
  while(LineStream>>Option && Option.find("--")!=std::string::npos) {
    if(Option.find("--run=")!=std::string::npos) {
      Option.assign(Option.substr(Option.find("--run=")+6));
      std::istringstream LineRunStream(Option);
      if(Option.find(",")!=std::string::npos) {
        std::string RunToInclude;
        while(std::getline(LineRunStream, RunToInclude, ',')) {
          if(strcmp(run_num, RunToInclude.c_str())==0) RunFound=true;
        }
      }
      if(Option.find("-")!=std::string::npos) {
        std::string StartRun;
        std::string StopRun;
        std::getline(LineRunStream, StartRun, '-');
        std::getline(LineRunStream, StopRun, '-');
        if(strcmp(run_num, StartRun.c_str())>=0 && strcmp(run_num, StopRun.c_str())<=0) RunFound=true;
      }
      if(Option.find(",")==std::string::npos && Option.find("-")==std::string::npos && !Option.empty()) {
        if(strcmp(run_num, Option.c_str())==0) RunFound=true;
      }
    } else if (Option.find("--exclude=")!=std::string::npos) {
        Option.assign(Option.substr(Option.find("--exclude=")+10));
        std::istringstream LineExcludeStream(Option);
        if(Option.find(",")!=std::string::npos) {
          std::string RunToExclude;
          while(std::getline(LineExcludeStream, RunToExclude, ',')) {
            if(strcmp(run_num, RunToExclude.c_str())==0) return; //this run is excluded
          }
        }
        if(Option.find("-")!=std::string::npos) {
          std::string StartRun;
          std::string StopRun;
          std::getline(LineExcludeStream, StartRun, '-');
          std::getline(LineExcludeStream, StopRun, '-');
          if(strcmp(run_num, StartRun.c_str())>=0 && strcmp(run_num, StopRun.c_str())<=0) return; //this run belong to a bunch of runs to be excluded
        }
        if(Option.find(",")==std::string::npos && Option.find("-")==std::string::npos && !Option.empty()) {
          if(strcmp(run_num, Option.c_str())==0) return;
        }
      }
  }

  if(RunFound) {
    NewValue.assign(LineToParse.substr(LineToParse.find("\"")+1,LineToParse.find_last_of("\"")-(LineToParse.find("\"")+1)));
  } else return;

  // if I'm here so run_num has been found in the configuration line
  if(ValueToSet.compare("MBINARY_FILE_PATH")==0) {
    fBinaryFilePath.assign(NewValue);
  } else if (ValueToSet.compare("FAIR_CONFIGURATION_FILE")==0) {
    fElectronicsConfigurationFileName.assign(NewValue);
  }

  return;
}
