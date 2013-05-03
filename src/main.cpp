#include "chat.h"
#include "lib/network.h"
#include <string>
#include <iostream>

int main() {
    network n;
    chat c;
    n.connectToHost("127.0.0.1", 39059);
    c.writeMessage("testing!\n", n);
    char *msg;
    int i = 0;
    while (i < 2) {
        msg = c.readMessage(n);
        if(msg != NULL && i < 2) {
            printf("%s", msg);
            i++;
        }
    }
    n.closeSocket();
    return 0;
}
