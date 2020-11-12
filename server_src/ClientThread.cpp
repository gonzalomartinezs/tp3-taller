#include "ClientThread.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

void ClientThread::run() {
    while(this->keep_running){
        // magia
    }
    this->is_running = false;
    this->peer.shutdown(SHUT_RDWR);
    this->peer.close();
}

void ClientThread::stop() {
    this->keep_running = false;
    this->peer.shutdown(SHUT_RDWR);
    this->peer.close();
}

bool ClientThread::is_dead() {
    return !(this->is_running);
}

