#include <cstring>
#include <sstream>
#include <string>
#include "Client.h"
#define CHUNK_SIZE 64

void Client::connect() {
    this->socket.connect(this->host, this->service);
}

ssize_t Client::send(std::string message) {
    return this->socket.send(message.c_str(), message.length());
}

ssize_t Client::send(std::istream &file) {
    std::stringstream content;
    content << file.rdbuf();
    ssize_t info_sent = send(content.str());
    return info_sent;
}

ssize_t Client::receive(std::ostream &file) {
    ssize_t info_received = 0, received = -1;
    char received_text[CHUNK_SIZE+1];
    memset(received_text, 0, CHUNK_SIZE+1);
    while (received!=0){
        received = this->socket.receive(received_text, CHUNK_SIZE);
        if (received!=0) {
            received_text[CHUNK_SIZE] = '\0';
            info_received += received;
            file << received_text << std::endl;
        }
    }
    return info_received;
}

void Client::shutdown(int mode) {
    this->socket.shutdown(mode);
}

