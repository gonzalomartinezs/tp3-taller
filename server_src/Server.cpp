#include "Server.h"
#include <sys/socket.h>

void Server::bindAndListen(int acceptance) {
    socket.bindAndListen(this->service, acceptance);
}

void Server::run() {
    this->acceptor.start();
}

Server::~Server() {
    this->acceptor.stop();
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
    this->acceptor.join();
}
