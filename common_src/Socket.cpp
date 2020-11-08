#include "Socket.h"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#define ERROR -1
#define SUCCESS 0

void Socket::bindAndListen(const std::string& service, int acceptance) {
    bool failed = true;
    struct addrinfo hints;
    struct addrinfo *results;

    _setHints(&hints);
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(nullptr, service.c_str(), &hints, &results);
    if (status == SUCCESS){
        if (_tryToBind(results) == SUCCESS){
            if (listen(this->fd, acceptance) == SUCCESS) failed = false;
        }
    }
    if (failed){
        throw;      //exception
    }
}

Socket Socket::accept() const {
    int peer_fd = ::accept(this->fd, nullptr, nullptr);
    if (peer_fd == ERROR) {
        throw;      //exception
    }
    return Socket(peer_fd);
}


void Socket::connect(const std::string& host, const std::string& service) {
    struct addrinfo hints;
    struct addrinfo *results;

    _setHints(&hints);
    hints.ai_flags = 0;

    int status = getaddrinfo(host.c_str(), service.c_str(), &hints, &results);
    if (status != SUCCESS || _tryToConnect(results) != SUCCESS) {
        throw;      //exception
    }
}

ssize_t Socket::send(const void *buffer, size_t length) const {
    bool error_at_sending = false;
    auto* address = (uint8_t*)buffer;  // casteo para realizar operaciones
    ssize_t bytes_sent = 0;               // ariméticas con dicha  dirección

    while (bytes_sent < (ssize_t)length && !error_at_sending) {
        ssize_t sent = ::send(this->fd, address,length-bytes_sent, MSG_NOSIGNAL);
        if (sent == ERROR) {
            error_at_sending = true;
        } else {
            bytes_sent += sent;
            address += sent;
        }
    }
    return error_at_sending? ERROR : bytes_sent;
}

ssize_t Socket::receive(void *buffer, size_t length) const {
    bool valid_socket = true, zero_bytes_recv = false;
    auto* address = (uint8_t*)buffer;  // casteo para realizar operaciones
    ssize_t bytes_received = 0;               // ariméticas con dicha  dirección

    while (bytes_received < (ssize_t)length && valid_socket && !zero_bytes_recv) {
        ssize_t received = recv(this->fd, address,
                                length - bytes_received, 0);
        if (received == ERROR) {
            valid_socket = false;
        } else if (received == 0){
            zero_bytes_recv = true;
        }else {
            bytes_received += received;
            address += received;
        }
    }
    return valid_socket? bytes_received : ERROR;
}

void Socket::shutdown(const int mode) const {
    if (mode == SHUT_RD || mode == SHUT_RDWR || mode == SHUT_WR){
        ::shutdown(this->fd, mode);
    }
}

void Socket::close() const {
    if(!(this->is_closed)){
        ::close(this->fd);
    }
}

Socket::~Socket() {
    if(!(this->is_closed)){
        ::shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
    }
}

//---------------------------- Métodos privados -----------------------------//

void Socket::_setHints(struct addrinfo* hints){
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
}

int Socket::_tryToBind(struct addrinfo *results) {
    bool binded = false;
    int socket_fd = 0;
    struct addrinfo *aux;

    for (aux = results; (aux != nullptr) && (!binded); aux = aux->ai_next) {
        socket_fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        binded = _couldBind(socket_fd, aux);
    }
    freeaddrinfo(results);
    this->fd = socket_fd;
    return binded? SUCCESS : ERROR;
}

bool Socket::_couldBind(int socket_fd, struct addrinfo* info){
    int status = ERROR;
    if (socket_fd != ERROR) {
        int val = 1;
        setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        status = bind(socket_fd, info->ai_addr, info->ai_addrlen);
        if (status == ERROR) ::close(socket_fd);
    }
    return (status != ERROR);
}

int Socket::_tryToConnect(struct addrinfo *results) {
    bool connected = false;
    int socket_fd = 0;
    struct addrinfo *aux;

    for (aux = results; (aux != nullptr) && (!connected); aux = aux->ai_next) {
        socket_fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        connected = _couldConnect(socket_fd, aux);
    }
    freeaddrinfo(results);
    this->fd = socket_fd;
    return connected? SUCCESS : ERROR;
}

bool Socket::_couldConnect(int socket_fd, struct addrinfo *info) {
    int status = ERROR;
    if (socket_fd != ERROR) {
        status = ::connect(socket_fd, info->ai_addr, info->ai_addrlen);
        if (status == ERROR) ::close(socket_fd);
    }
    return (status != ERROR);
}





