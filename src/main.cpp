#include "chat.h"
#include "lib/network.h"
#include <string>
#include <iostream>

int main() {
    network n;
    chat c;
    n.connectToHost("127.0.0.1", 39059);
    c.writeMessage("testing!");
    n.closeSocket();
    return 0;
}
