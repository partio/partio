/*******************************************************************************
 * File:         network.cpp
 * Created:      2013-02-24
 * Authors:      Christoffer Sterner
 * License:      Apache License, see LICENSE
 * Description:  Network class implementations
 * Platforms:    Linux
 ******************************************************************************/

#include "network.h"

struct sockaddr_in name;

network::network() {
    network::ip = "127.0.0.1";
    network::port = 39059;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    this->isConnected = false;
    this->reconTimes = 0;
    
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

        return 1;
    }
    this->isConnected = true;
    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    return 0;
}
  
void network::writeMessage(std::string s) {
    char input[1024];
    bzero(input,1024);
    s.copy(input,1024,0);
    if(isConnected) {
        sendto(sockfd, input, sizeof(input), 0,
               (struct sockaddr*)&name, sizeof(name));
    } else {
        std::cout << "Not connected to " << ip << " could not send message\n";
    }
}

char *network::readMessage() {
    char buffer[1024];
    bzero(buffer,1024);
    if((recv(sockfd,buffer,sizeof(buffer),0) == 0 || !isConnected) &&
            reconTimes < 30) {
        if(this->isConnected == true) {
            std::cout << sockfd << ": Connection failure" << std::endl;
        }
        network::isConnected = false;
        close(network::sockfd);
        network::sockfd = socket(AF_INET, SOCK_STREAM, 0);
        sleep(1);
        this->reconTimes++;
        std::cout << reconTimes << std::endl;
        if(connectToHost(this->ip, this->port) == 0) {
            this->reconTimes = 0;
        }
    }
    if (buffer[0] > 0) {
        char * resBuf = new char[1024];
        strcpy(resBuf, buffer);
        return resBuf;
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


/**
 * Description: Class creator
 */
unix_socket::unix_socket(char* s) {
    this->path = s;
    this->local.sun_family = AF_UNIX;
    this->sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
}

/**
 * Description: enable this socket
 * Output: 0 - Everything went well
 *         1 - Could not create socket
 *         2 - Could not bind socket
 *         3 - Could not listen
 */
int unix_socket::enableSocket() {
    if (this->sockfd == -1) {
        return 1;
    }

    strcpy(this->local.sun_path, this->path.c_str());
    int len = strlen(local.sun_path) + sizeof(local.sun_family);

    if (bind(this->sockfd, (struct sockaddr *)&local, len) == -1) {
        return 2;
    }

    if (listen(this->sockfd, 5) == -1) {
        return 3;
    }
    
    return 0;
}

/**
 * Description: Change socket path
 */
void unix_socket::changePath(char* s) {
    this->dissableSocket();
    this->path = s;
    this->enableSocket();
}

/**
 * Description: Returns socket
 */
int unix_socket::getSocket() {
    return this->sockfd;
}

/**
 * Description: Stops socket from litsening
 */
void unix_socket::dissableSocket() {
    unlink(this->local.sun_path);
}


void unix_socket::closeSocket() {
    close(this->sockfd);
};

char *unix_socket::readMessage() {
    
}

unix_socket::~unix_socket() {
    this->closeSocket();
}






















