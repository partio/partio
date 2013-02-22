/*******************************************************************************
 * File:         chat.cpp
 * Created:      2013-02-23
 * Authors:      Christoffer Sterner
 * License:      Apache License, see LICENSE
 * Description:  Chat class implementations
 * Platforms:    Linux
 ******************************************************************************/

#include "chat.h"
int chat::sockfd = socket(AF_INET, SOCK_STREAM, 0);
std::string chat::username = "worfox";
std::string chat::ip = "127.0.0.1";
int chat::port = 39059;
struct sockaddr_in name;

chat::chat() {

}

int chat::getSocket() {
    return chat::sockfd;
}

std::string chat::getUsername() {
    return chat::username;
}

std::string chat::getIP() {
    return chat::ip;
}

void chat::setIP(std::string newIP) {
    chat::ip = newIP;
}

int chat::getPort() {
    return chat::port;
}

void chat::setPort(int newPort) {
    chat::port = newPort;
}

void chat::setUsername(std::string newName) {
    chat::username = newName;
}

int chat::connectToHost(std::string ip, int port) {
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(ip.c_str());
    name.sin_port = htons(port);

    if (connect(sockfd,(struct sockaddr *) &name,sizeof(name)) < 0) {
        std::cout << "Connection failure" << std::endl;
        return 1;
    }
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    return 0;
}

void chat::writeMessage(std::string s) {
    char input[1024];
    bzero(input,1024);
    s.copy(input,1024,0);
    sendto(sockfd, input, sizeof(input), 0,
           (struct sockaddr*)&name, sizeof(name));
}

char *chat::readMessage() {
    char buffer[1024];
    bzero(buffer,1024);
    recv(sockfd,buffer,sizeof(buffer),0);
    if (buffer[0] > 0) {
        char *resBuf;
        resBuf = buffer;
        return resBuf;
        bzero(resBuf, sizeof resBuf);
    }
    return 0;
}

size_t chat::strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}


void chat::closeSocket() {
    close(chat::sockfd);
}
