#include "ClientThread.h"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include "HTMLInstruction.h"

#define CHUNK_SIZE 512

void ClientThread::run() {
    try{
        while (this->keep_running){
            char request[CHUNK_SIZE];
            memset(request, 0, CHUNK_SIZE);
            ssize_t  received = this->peer.receive(request, CHUNK_SIZE);
            if (received != 0) {
                std::stringstream request_stream(request);
                std::string first_line;
                std::getline(request_stream, first_line);
                request_stream.clear();
                request_stream.seekg(0);
                std::cout << (first_line + "\n");
                std::string response = _generateResponse(request_stream);
                peer.send(response.c_str(), strlen(response.c_str()));
            } else {
                this->keep_running = false;
            }
        }
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cout << "Unknown error.\n";
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

//---------------------------- Metodos privados -----------------------------//

// Retorna la respuesta al petitorio html.
std::string ClientThread::_generateResponse(std::stringstream &request_stream) {
    std::string method, resource, protocol, body;
    this->parser(request_stream);
    method = this->parser.getRequestMethod();
    resource = this->parser.getRequestResource();
    protocol = this->parser.getRequestProtocol();
    body = this->parser.getRequestBody();
    HTMLInstruction instruction(method, resource, protocol,
                                body, this->resources);
    return instruction.generateResponse();
}

