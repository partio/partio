/*
 * File:         directory.h
 * Created:      2013-05-02
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  Class for handling directories
 * Platforms:    Linux
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <dirent.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>



class dirHandler {
private:
    std::string directory;
    //DIR* d;
    std::vector<std::string> dirs;
    std::vector<std::string> files;
    long nrOfFolders;
    long nrOfFiles;
public:
    dirHandler();
    int changeDir(const char * newDir);
    int updateDirlist();
    std::vector<std::string> getDirList();
    std::vector<std::string> getFileList();
    long getNrOfDirs();
    ~dirHandler();
};

#endif // DIRECTORY_H


















