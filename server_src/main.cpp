#include "Server.h"
#include <fstream>
#include <iostream>

#define ARGUMENTS_AMOUNT 3
#define ERROR 1
#define SUCCESS 0
#define ROOT "/"

int main(int argc, char** argv) {
    if (argc != ARGUMENTS_AMOUNT){
        std::cerr << "Error: Wrong arguments." << std::endl;
        return ERROR;
    }
    std::ifstream resource(argv[2]);
    if (!resource){
        std::cerr << "Error: Unable to open resource file" << std::endl;
        return ERROR;
    }
    try{
        Server server(argv[1], ROOT, resource);
        server.bindAndListen(2);
        server.run();
        char c;
        do {
           c = (char)getchar();
        } while (c != 'q');
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    } catch(...){
        std::cout << "Unknown error.\n";
        return ERROR;
    }

    return SUCCESS;
}
