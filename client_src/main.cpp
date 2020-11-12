#include <iostream>
#include "Client.h"
#define ERROR -1
#define SUCCESS 0

int main(int argc, char** argv) {
    Client client(argv[1], argv[2]);
    client.connect();
    client.receive(std::cout);
    return 0;
}