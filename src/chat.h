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
    static std::string ip;
    static int port;
    static int sockfd;
public:
    chat();
    int connectToHost(std::string ip, int port);
    void writeMessage(std::string s);
    char *readMessage();
    std::string getIP();
    void setIP(std::string newIP);
    std::string getUsername();
    void setUsername(std::string newName);
    int getPort();
    void setPort(int newPort);
    int getSocket();
    void closeSocket();
    size_t strlen(const char *str);
};

#endif // CHAT_H
