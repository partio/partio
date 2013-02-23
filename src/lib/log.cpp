/*
 * File:         log.cpp
 * Created:      2013-01-16
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  
 * Platforms:    Linux
 */

#include "log.h"

/*
 * Constructor
 */
log::log( unsigned int v, bool q ) {
  this->verbosity = v;
  this->quiet = q;
}

/*
 * Change global verbosity
 */
void log::changeVerbosity( unsigned int v ) {
  this->verbosity = v;
}

/*
 * Adds logfile
 * Returns:
 * 0 - Logfile added to list
 * 1 - Could not open file for writing
 */
int log::addLogfile(const char* f, unsigned int v ) {
  FILE *test;
  test = fopen(f, "a");
  if ( test == NULL )
    return 1;
  logFile file;
  file.verbosity = v;
  file.fileName = f;
  this->logFiles.push_back(file);
  return 0;
}

/*
 * Removes the first matching logfile
 * 0 - Logfile removed from list
 * 1 - Logfile not found
 */
int log::removeLogfile(const char* f){
  bool erased = false;
  //this->debugMsg(10, "not dead yeat");
  std::string fileToRemove = f;
  for (std::vector<logFile>::iterator i = this->logFiles.begin() ; i != this->logFiles.end(); ++i) {
    //std::string currentFile = i->fileName;
    this->debugMsg(1, "filename -> %s", i->fileName);
    if ( fileToRemove.compare(i->fileName) == 0 ){
      i = this->logFiles.erase(i);
      erased = true;
      break;
    }
  }
  return (erased)? 0 :1 ;
}

/*
 * Debug function
 */
void log::printLogFiles() {
  printf("Verbosity : Filename\n");
  for (std::vector<logFile>::iterator i = this->logFiles.begin() ; i != this->logFiles.end(); ++i) {
    printf("%2d : %s\n", i->verbosity, i->fileName);
  }
}

/*
 * Count Letters occuring in string
 */
int log::countLetters( const char &letter, std::string const &searchString ) {
  int count = 0;
  int lastSame = 0;
  for (unsigned int i = 0; i < searchString.size(); i++) {
    if (searchString[i] == letter  && lastSame == 0 ){
      count++;
      lastSame++;
    } else if ( searchString[i] == letter  && lastSame > 0 ) {
      count--;
      lastSame = 0;
    } else {
      lastSame = 0;
    }
  }
  
  return count;
}

/*
 * Outputs message to stdout
 */
void log::debugMsg( unsigned int v, const char* p , ... ){
  if (this->verbosity < v || this->quiet) return;
  /*
  std::va_list fmtargs;
  std::string buffer;
  std::string temp = p;
  
  va_start(fmtargs,p);
  
  int nrOfArgs = countLetters('%', temp);
  
  for ( int i = 0; i < nrOfArgs; i++ ) {
    buffer.append(va_arg(fmtargs, char*));
  }
  
  va_end(fmtargs);
  */
  
  std::va_list fmtargs;
  char buffer[1024];
  
  va_start(fmtargs,p);
  vsnprintf(buffer,sizeof(buffer)-1,p,fmtargs);
  va_end(fmtargs);

  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  char timeBuffer[80];
  // Fills timeBuffer with time from timeinfo. ex. 2012-03-05 21:06:18
  strftime(timeBuffer, 80, "%Y-%m-%d %X %Z",timeinfo);
  _IO_FILE *stdDest;
  // if verbosityLevel is 4 or lower print to STDERR
  if (v <= 4) stdDest=stderr; else stdDest = stdout;
  
  fprintf(stdDest, "[%s] [%2d] %s\n", timeBuffer, v, buffer);
  
}

/*
 * Outputs string to logfiles and stdout
 */
int log::logMsg( unsigned int v, const char* p, ... ){
  /*
  std::va_list fmtargs;
  std::string buffer;
  std::string temp = p;

  int nrOfArgs = this->countLetters('%', temp);
  if ( nrOfArgs > 0 ) {
    va_start(fmtargs,p);
	
    for ( int i = 0; i < nrOfArgs; i++ ) {
      buffer.append(va_arg(fmtargs, char*));
    }
	
    va_end(fmtargs);
  } else {
    buffer.append(p);
  } */
  
  std::va_list fmtargs;
  char buffer[1024];
  
  va_start(fmtargs,p);
  vsnprintf(buffer,sizeof(buffer)-1,p,fmtargs);
  va_end(fmtargs);
  
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  char timeBuffer[80];
  // Fills timeBuffer with time from timeinfo. ex. 2012-03-05 21:06:18
  strftime(timeBuffer, 80, "%Y-%m-%d %X %Z",timeinfo);

  for (std::vector<logFile>::iterator i = this->logFiles.begin() ; i != this->logFiles.end(); ++i) {
    if ( i->verbosity >= v ) {
      FILE * log;
      log = fopen(i->fileName, "a");
      if (log == NULL ){
	this->removeLogfile(i->fileName);
	
      } else {
	
	fprintf(log, "[%s] [%2d] %s\n", timeBuffer, v, buffer);
	fclose(log);
      }
    }
  }
  if (this->verbosity >= v && !this->quiet) {
    _IO_FILE *stdDest;
    // if verbosityLevel is 4 or lower print to STDERR
    if (v <= 4) stdDest=stderr; else stdDest = stdout;
    fprintf(stdDest, "[%s] [%2d] %s\n", timeBuffer, v, buffer);
  }
  return 0;
}

void log::setQuiet(bool q) {
  this->quiet = q;
}



