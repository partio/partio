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
#include <sys/socket.h>
#include <sys/un.h>

class network {
private:
    std::string ip;
    int port;
    int sockfd;
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


class unix_socket {
private:
    std::string path;
    int sockfd;
    struct sockaddr_un local;
public:
    unix_socket(char *s);
    int enableSocket();
    void changePath(char* s);
    int getSocket();
    void dissableSocket();
    void closeSocket();
    char *readMessage();
    ~unix_socket();
    
};

#endif // NETWORK_H


















