/*******************************************************************************
 * File:         network.cpp
 * Created:      2013-02-24
 * Authors:      Christoffer Sterner
 * License:      Apache License, see LICENSE
 * Description:  Network class implementations
 * Platforms:    Linux
 ******************************************************************************/

#include "network.h"
int network::sockfd = socket(AF_INET, SOCK_STREAM, 0);
std::string network::ip = "127.0.0.1";
int network::port = 39059;
struct sockaddr_in name;

network::network() {

}

int network::getSocket() {
    return network::sockfd;
}

std::string network::getIP() {
    return network::ip;
}

void network::setIP(std::string newIP) {
    network::ip = newIP;
}

int network::getPort() {
    return network::port;
}

void network::setPort(int newPort) {
    network::port = newPort;
}


int network::connectToHost(std::string ip, int port) {
    this->setIP(ip);
    this->setPort(port);
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

void network::writeMessage(std::string s) {
    char input[1024];
    bzero(input,1024);
    s.copy(input,1024,0);
    sendto(sockfd, input, sizeof(input), 0,
           (struct sockaddr*)&name, sizeof(name));
}

char *network::readMessage() {
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

size_t network::strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}


void network::closeSocket() {
    close(network::sockfd);
}
