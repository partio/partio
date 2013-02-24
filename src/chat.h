/*******************************************************************************
 * File:         chat.h
 * Created:      2013-02-23
 * Authors:      Christoffer Sterner
 * License:      Apache License, see LICENSE
 * Description:  Chat class header
 * Platforms:    Linux
 ******************************************************************************/

#ifndef CHAT_H
#define CHAT_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>

class chat {
private:
    static std::string username;
public:
    chat();
    void writeMessage(std::string s);
    char *readMessage();
    std::string getUsername();
    void setUsername(std::string newName);
    size_t strlen(const char *str);
};

#endif // CHAT_H
