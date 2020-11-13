#include <iostream>
#include <sys/socket.h>
#include "Client.h"
#define ERROR -1
#define SUCCESS 0

int main(int argc, char** argv) {
    try {
        Client client(argv[1], argv[2]);
        client.connect();
        client.send(std::cin);
        client.shutdown(SHUT_WR);
        client.receive(std::cout);
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
