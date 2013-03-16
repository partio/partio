/**
  * File:         
  * Created:      2013-02-07
  * Authors:      Dennis Vesterlund
  * License:      Apache License, see LICENSE
  * Description:  Config file parsing class
  * Platforms:    Linux
  */

#include "configFileParser.h"

/**
 * Constructor
 * Description: Takes path and filename to config file
 * Input: f - path to configfile
 *        i - maximum line length
 */
fileParser::fileParser(const char *f, const int i){
    this->fileName = f;
    this->bufferSize = i;
}

/**
 * Description: Parses the file
 * Output: < 0 - int overflow
 *           0 - if file could not be opened or no options found
 *         > 0 - the it returns the number of options found
 */
int fileParser::parseFile() {
    FILE *f;
    f = fopen(this->fileName.c_str(), "r");
    if ( f == NULL )
        return 0;
    char buffer[this->bufferSize];
    unsigned long nrOfOptions = 0;
    //std::string buffer;
    while ( fgets(buffer, this->bufferSize, f) != NULL ) {
        configOption temp = this->parseLine(buffer);
        if ( temp.optionValue.length() != 0 ) {
            configOptions.push_back(temp);
            nrOfOptions++;
        }
        this->cleanCString(buffer, this->bufferSize);
    }
  
    fclose(f);
    return nrOfOptions;
}

/**
 * Description: Parses a single line for option
 * Input: line - the line to parse
 * Output: A single key and value
 */
fileParser::configOption fileParser::parseLine(char * line) {
    std::string parseline = line;
    configOption option;
    parseline = this->stripComment(parseline);
    if ( parseline.length() < 3 )
        return option;
    parseline = this->cleanStringFrom(parseline, ' ');
    size_t found= parseline.find('=');
    if ( found != std::string::npos && found > 0 ) {
        parseline = this->cleanStringFrom(parseline, '\n');
        parseline = this->cleanStringFrom(parseline, '\r');
        option.optionName = parseline.substr(0, found);
        option.optionValue = parseline.substr(found+1);
    }
    return option;
}

/**
 * Description: Strips comments from lines
 * Input: line - line to strip
 * Output: the stripped line
 */
std::string fileParser::stripComment(std::string line) {
    size_t found = line.find('#');
    while ( found != std::string::npos ) {
        if ( line[found-1] != '\\' ) {
            line = line.substr(0, found);
            found = std::string::npos;
        } else {
            found = line.find('#', found);
        }
    }
    return line;
}

/**
 * Description: Cleans the string from non escaped('\') characters specified
 * Input: s - String to strip 
 *        c - Specific char to strip
 * Output: the stripped line
 */
std::string fileParser::cleanStringFrom(std::string s, const char c) {
    for(int i = 0; i < s.length(); i++)
        if(s[i] == c && s[-1] != '\\') {
            s.erase(i,1);
            i--;
        } 
    return s;
}

/**
 * Description: Fills string with nothing('\0')
 * Input: string - String to clean
 *        length - Length of string
 */
void fileParser::cleanCString( char * string, int length ) {
    for( int i = 0; i < length; i++)
        string[i] = '\0';
}

/**
 * Description: Returns found options
 * Output: A vector of options
 */
std::vector<fileParser::configOption> fileParser::getAllOptions() {
    return this->configOptions;
}

/**
 * Desription: Returns one option each time called
 * Output: A single key and value
 */
/// @TODO This always only returns the last option... always
fileParser::configOption fileParser::getOneOption() {
    fileParser::configOption temp;
    temp.optionName = this->configOptions.back().optionName;
    temp.optionValue = this->configOptions.back().optionValue;
    return temp;
}


/**
 * Description: Returns whether there are any config options loaded
 * Output: False if there are options in the list
 */
bool fileparser::isEmpty() {

    return this->configOptions.empty();

}



/// @TODO give a way to resave configchanges
















