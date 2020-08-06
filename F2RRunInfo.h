#ifndef F2RRUNINFO_H
#define F2RRUNINFO_H

#include <fstream>
#include <sstream>
#include <TROOT.h>

class F2RRunInfo
{
public:
  F2RRunInfo(const char * run_number);                   //! Constructor
  ~F2RRunInfo();                                         //! Destructor
  
  int InitClass(const char *);                           //! Class initializer called by the main program
  
  int LoadSetupConfiguration(const char *);              //! Read general setup lines from configuration file of the experiment
  int LoadRunConfiguration(const char *, const char *);  //! Read run configuration for a specific run

  const char * GetName() const;                          //! Get Experiment Name
  const char * GetTitle() const;                         //! Get Experiment Title
  const char * GetRunNumber() const;                     //! Get Run number as a string
  const char * GetRunFolderName() const;                 //! Get the file relative path name of the folder associated to the run
  const char * GetRunFilePathName() const;               //! Get the file absolute path name of the folder associated to the run
  int GetFAIRWordSize() const;                           //! Returns the size of a FAIR Word in char
  const char * GetBinaryFilePath() const;                //! Returns path containing binary files for the run
  const char * GetF2RROOTFilePath() const;               //! Returns the path to the unpacked files of the run (output of the program)
  const char * GetElectronicsConfigFileName() const;     //! Returns the file name of the FAIR electronics configuration file

  void SetBinaryFilePath(const char *);                  //! Set path for the binary files of the run

private:
  std::string fRunName;                                  //!
  std::string fRunNumber;                                //!
  std::string fExperimentName;                           //!
  std::string fExperimentTitle;                          //!
  std::string fF2RRootFilePath;                          //!
  int fFAIRWordSize;                                     //!
  std::string fBinaryFilePath;                           //!
  std::string fRunFolderName;                            //!
  std::string fElectronicsConfigurationFileName;         //!
  
  void ParseSetConfigLine(const char *);                 //! Parse a "set" line in the configuration file
  void ParseSetConfigLineRunInfo(const char *, const char * );    //! Parse a "set" line of a run-by-run instruction
};

#endif
