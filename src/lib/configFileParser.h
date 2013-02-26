/*
 * File:         configFileParser.h
 * Created:      2013-02-07
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  Header for config file parsing class
 * Platforms:    Linux
 */

#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H

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
  std::string cleanStringFrom(std::string s, const char c);
  std::string stripComment(std::string line);
  void cleanCString( char * string, int length );
  configOption parseLine(char * line);

private:
  std::vector<configOption> configOptions;
  std::string fileName;
  int bufferSize;
};


#endif // CONFIGFILEPARSER_H




















