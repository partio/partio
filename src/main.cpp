#include "chat.h"

int main() {
    std::cout << "Starting partio!" << std::endl;
    network n;
    network n2;
    chat c;
    n2.connectToHost("127.0.0.1", 39057);
    n.connectToHost("127.0.0.1", 39059);
    c.writeMessage("testing!\n", n);
    std::cout << n.getSocket() << std::endl;
    std::cout << n2.getSocket() << std::endl;
    c.writeMessage("testing2!\n", n2);
    std::string msg;
    std::string msg2;
    int i = 0;
    while (1) {
        sleep(1);
        msg = c.readMessage(n);
        msg2 = c.readMessage(n2);
        if(!msg.empty()) {
            std::cout << n.getSocket() << ": " <<  msg;
        }
        if(!msg2.empty()) {
            std::cout << n2.getSocket() << ": " << msg2;
            i++;
        }
    }
    n.closeSocket();
    n2.closeSocket();
    return 0;
}
