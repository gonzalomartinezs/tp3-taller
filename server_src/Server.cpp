#include "Server.h"
#include <sys/socket.h>

void Server::bindAndListen(int acceptance) {
    socket.bindAndListen(this->service, acceptance);
}

void Server::run() {
    this->acceptor.start();
}

Server::~Server() {
    _stop();
}

// Finaliza la ejecucion del servidor.
void Server::_stop() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
    this->acceptor.join();
}
