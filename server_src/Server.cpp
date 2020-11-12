#include "Server.h"
#include <sys/socket.h>

void Server::bindAndListen(int acceptance) {
    socket.bindAndListen(this->service, acceptance);
}

void Server::run() {
    this->acceptor.start();
    this->is_running = true;
}

void Server::stop() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
    this->acceptor.join();
    this->is_running = false;
}

Server::~Server() {
    if (this->is_running){
        stop();
    }
}
