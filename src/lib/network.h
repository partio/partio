/*******************************************************************************
 * File:         network.h
 * Created:      2013-02-24
 * Authors:      Christoffer Sterner
 * License:      Apache License, see LICENSE
 * Description:  Network class header
 * Platforms:    Linux
 ******************************************************************************/

#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>

class network {
private:
    static std::string ip;
    static int port;
    static int sockfd;
public:
    network();
    int connectToHost(std::string ip, int port);
    void writeMessage(std::string s);
    char *readMessage();
    std::string getIP();
    void setIP(std::string newIP);
    int getPort();
    void setPort(int newPort);
    int getSocket();
    void closeSocket();
    size_t strlen(const char *str);
};

#endif // NETWORK_H
