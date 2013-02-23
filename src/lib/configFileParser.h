/*
 * File:         log.cpp
 * Created:      2013-02-07
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  
 * Platforms:    Linux
 */

#include <cstdio>
#include <string>
#include <vector>

class fileParser {
 public:
  struct configOption {
    std::string optionName;
    std::string optionValue;
  };
  fileParser(const char * f, int i = 255);
  int parseFile();
  std::vector<configOption> getAllOptions();
  configOption getOneOption();
 private:
  std::vector<configOption> configOptions;
  void cleanCString( char * string, int length );
  configOption parseLine(char * line);
  std::string fileName;
  int bufferSize;
  std::string stripComment(std::string line);
  std::string cleanStringFrom(std::string s, const char c);
};



















