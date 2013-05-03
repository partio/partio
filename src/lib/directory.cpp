/*
 * File:         directory.cpp
 * Created:      2013-05-02
 * Authors:      Dennis Vesterlund
 * License:      Apache License, see LICENSE
 * Description:  Class for handeling directories
 * Platforms:    Linux
 */

#include "directory.h"

dirHandler::dirHandler() {
#ifdef WIN32
    this->directory = getenv("HOMEPATH");
#else
    this->directory = getenv("HOME");
#endif
    //this->d = opendir(this->directory.c_str());
}

dirHandler::~dirHandler() {
    //if ( this->d != NULL ) closedir(this->d);
}

int dirHandler::changeDir(const char * newDir) {
    DIR * nD;
    nD = opendir(newDir);
    if ( nD == NULL ) {
        return -1;
    } else {
        closedir(nD);
        this->directory = newDir;
        return 0;
    }
}

int dirHandler::updateDirlist() {
    this->nrOfFolders = 0;
    this->nrOfFiles = 0;
    struct dirent *dirnt;
    DIR *dir = opendir(this->directory.c_str());
    struct stat st;
    if (!dir) return -1;
    while ( (dirnt = readdir(dir)) ) {
        std::string tempName = dirnt->d_name;
        stat(dirnt->d_name, &st);
        if ( S_ISDIR( st.st_mode ) ) {
            this->dirs.push_back(tempName);
        } else {
            this->files.push_back(tempName);
        }
        
    }
    std::sort(this->dirs.begin(), this->dirs.end());
    std::sort(this->files.begin(), this->files.end());
    closedir(dir);
    return 0;
}



std::vector<std::string> dirHandler::getDirList() {
    return this->dirs;
}

std::vector<std::string> dirHandler::getFileList() {
    return this->files;
}

long dirHandler::getNrOfDirs() {
    return this->nrOfFolders;
}


int main() {
    dirHandler d;
    d.updateDirlist();
    std::vector<std::string> folders = d.getFileList();
    for(std::vector<std::string>::iterator it = folders.begin(); it < folders.end(); ++it ) {
        std::cout << it->c_str() << std::endl;
    }
}



















