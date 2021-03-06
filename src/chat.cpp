/*******************************************************************************
 * File:         chat.cpp
 * Created:      2013-02-23
 * Authors:      Christoffer Sterner
 * License:      Apache License, see LICENSE
 * Description:  Chat class implementations
 * Platforms:    Linux
 ******************************************************************************/

#include "chat.h"
#include "lib/network.h"
std::string chat::username = "worfox";

chat::chat() {

}

std::string chat::getUsername() {
    return chat::username;
}

void chat::setUsername(std::string newName) {
    chat::username = newName;
}

void chat::writeMessage(std::string s, network *n) {
    s.insert(0, username + ": ");
    n->writeMessage(s);
}

std::string chat::readMessage(network *n) {
    char *temp = n->readMessage();
    if(temp != NULL) {
        std::string s(temp);
        return s;
    }
    std::string s;
    return s;

}

size_t chat::strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s);
    return(s - str);
}











