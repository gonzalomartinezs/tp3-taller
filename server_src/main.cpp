#include "Server.h"
#include <iostream>

int main(int argc, char** argv) {
    Server server(argv[1]);
    server.bindAndListen(2);
    server.run();

    char c;
    do {
       c = (char)getchar();
    } while (c != 'q');

    server.stop();
    return 0;
}