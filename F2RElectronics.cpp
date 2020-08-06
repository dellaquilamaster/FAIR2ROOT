#include <F2RElectronics.h>

//____________________________________________________
F2RElectronics::F2RElectronics () 
{}

F2RElectronics::~F2RElectronics()
{
  for(auto && mask : fMasks) {
    delete mask.second; 
  }
}

//____________________________________________________
int F2RElectronics::Init()
{
  std::ifstream FileIn(gRun->GetElectronicsConfigFileName());
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

    if(LineReadCommentLess.find("define ")!=std::string::npos) {
      NRead+=ParseDefineConfigLine(LineReadCommentLess.c_str());
    }
    
  }
  
  //
  FileIn.close();
  //
  
  //
  return NRead;  
  //
}

//____________________________________________________
int F2RElectronics::ParseDefineConfigLine(const char * line_to_parse)
{
  std::string LineToParse(line_to_parse);

  LineToParse.assign(LineToParse.substr(LineToParse.find("define ")+7)); //remove define command

  std::istringstream LineStream(LineToParse);

  std::string WhatToDefine;
  LineStream>>WhatToDefine;
  
  std::string VSNString;
  LineStream>>VSNString;
  VSNString.assign(VSNString.substr(VSNString.find("vsn=\"")+5,VSNString.find_last_of("\"")-(VSNString.find("vsn=\"")+5)));
  const int VSNNum=std::stoi(VSNString);
  
  if(WhatToDefine.compare("SEGC")!=0 && WhatToDefine.compare("ADC")!=0 && WhatToDefine.compare("TDC")!=0 && WhatToDefine.compare("SLC")!=0) {
    return 0; 
  }
  
  //
  // Adding a new module mask
  F2RModuleMask * NewModule = new F2RModuleMask(WhatToDefine.c_str());
  fMasks[VSNNum]=NewModule;
  //
  
  //
  return 1;
  //
}

//____________________________________________________
unsigned int F2RElectronics::Size() const
{
  return fMasks.size(); 
}

//____________________________________________________
F2RModuleMask* F2RElectronics::GetModuleMask(int mod_number)
{
  return fMasks[mod_number]; 
}
