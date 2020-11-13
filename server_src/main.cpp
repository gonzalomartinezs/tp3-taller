#include "Server.h"
#include <fstream>

#define ERROR 1
#define SUCCESS 0
#define ROOT "/"

int main(int argc, char** argv) {

    std::ifstream resource(argv[2]);
    if (!resource){
        return ERROR;
    }
    Server server(argv[1], ROOT, resource);
    server.bindAndListen(2);
    server.run();

    char c;
    do {
       c = (char)getchar();
    } while (c != 'q');

    server.stop();
    return SUCCESS;
}