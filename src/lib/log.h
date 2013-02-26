/*
 * File:         log.cpp
 * Created:      2013-02-04
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  
 * Platforms:    Linux
 */

#ifndef LOG_H
#define LOG_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstdarg>
#include <vector>

class log {
private:
  struct logFile {
    unsigned int verbosity;
    const char* fileName;
  };
  unsigned int verbosity;
  std::vector<logFile> logFiles;
  bool quiet;
  int countLetters( const char &letter, std::string const &searchString );
public:
  log( unsigned int v, bool q = false );
  void changeVerbosity( unsigned int v );
  int addLogfile(const char* f, unsigned int v );
  int removeLogfile(const char* f);
  void printLogFiles();
  void debugMsg( unsigned int verbosityLevel, const char* printstyle , ... );
  int logMsg( unsigned int v, const char* p, ... );
  void setQuiet(bool q);
};



#endif // LOG_H




















