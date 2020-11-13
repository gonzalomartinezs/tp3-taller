#include "ClientThread.h"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include "HTMLInstruction.h"
#define CHUNK_SIZE 256

void ClientThread::run() {
    while(this->keep_running){
        char request[CHUNK_SIZE];
        memset(request, 0, CHUNK_SIZE);
        this->peer.receive(request, CHUNK_SIZE);
        std::stringstream request_stream(request);
        parser.parse(request_stream);
        std::string method = parser.getRequestMethod();
        std::string resource = parser.getRequestResource();
        std::string protocol = parser.getRequestProtocol();
        std::string body = parser.getRequestBody();
        HTMLInstruction instruction(method, resource, protocol,
                                    body, this->resources);
        std::string response = instruction.generateResponse();
        peer.send(response.c_str(), response.size());
        std::cout << response << std::endl;
        this->keep_running = false;
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

