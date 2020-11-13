#include "Socket.h"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "SocketException.h"
#define ERROR -1
#define SUCCESS 0
#define ERROR_BINDING "Unable to bind: "
#define ERROR_CONNECTING "Unable to connect: "
#define ERROR_SENDING "Could not send: "
#define ERROR_RECEIVING "Could not receive: "


Socket::Socket(Socket &&other) noexcept {
    this->fd = other.fd;
    this->is_closed = false;
    other.fd = -1;
    other.is_closed = true;
}

Socket& Socket::operator=(Socket &&other) noexcept {
    this->fd = other.fd;
    this->is_closed = false;
    other.fd = -1;
    other.is_closed = true;
    return *this;
}


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
        throw SocketException(ERROR_BINDING);
    }
}

Socket Socket::accept() const {
    int peer_fd = ::accept(this->fd, nullptr, nullptr);
    return Socket(peer_fd);
}


void Socket::connect(const std::string& host, const std::string& service) {
    struct addrinfo hints;
    struct addrinfo *results;

    _setHints(&hints);
    hints.ai_flags = 0;

    int status = getaddrinfo(host.c_str(), service.c_str(), &hints, &results);
    if (status != SUCCESS || _tryToConnect(results) != SUCCESS) {
        throw SocketException(ERROR_CONNECTING);
    }
}

ssize_t Socket::send(const void *buffer, size_t length) const {
    auto* address = (uint8_t*)buffer;  // casteo para realizar operaciones
    ssize_t bytes_sent = 0;               // arimeticas con dicha  direccion

    while (bytes_sent < (ssize_t)length) {
        ssize_t sent = ::send(this->fd, address,length-bytes_sent,
                                                        MSG_NOSIGNAL);
        if (sent == ERROR) {
            throw SocketException(ERROR_SENDING);
        }
        bytes_sent += sent;
        address += sent;
    }
    return bytes_sent;
}

ssize_t Socket::receive(void *buffer, size_t length) const {
    bool zero_bytes_recv = false;
    auto* address = (uint8_t*)buffer;  // casteo para realizar operaciones
    ssize_t bytes_received = 0;               // arimeticas con dicha  direccion
    while (bytes_received < (ssize_t)length && !zero_bytes_recv) {
        ssize_t received = recv(this->fd, address,
                                length - bytes_received, 0);
        if (received == ERROR) {
            throw SocketException(ERROR_RECEIVING);
        } else if (received == 0){
            zero_bytes_recv = true;
        }else {
            bytes_received += received;
            address += received;
        }
    }
    return bytes_received;
}

bool Socket::is_valid() const{
    return (this->fd) > 0;
}

void Socket::shutdown(const int mode) const {
    if (mode == SHUT_RD || mode == SHUT_RDWR || mode == SHUT_WR){
        ::shutdown(this->fd, mode);
    }
}

void Socket::close() {
    if (!(this->is_closed)){
        ::close(this->fd);
        this->fd = -1;
        this->is_closed = true;
    }
}

Socket::~Socket() {
    if (!(this->is_closed)){
        ::shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
    }
}

//---------------------------- Metodos privados -----------------------------//

// Setea todos los hints en 0 y modifica el valor de algunos.
void Socket::_setHints(struct addrinfo* hints){
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
}

// Itera en las posibles direcciones hasta que se puede enlazar (bind).
// En caso de exito modifica el fd del socket y devuelve 0.
// Retorna -1 en caso contrario.
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


// Verifica si se pudo enlazar el fd con la direccion recibida.
// Retorna true en caso positivo y false en caso contrario.
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

// Itera en las posibles direcciones hasta que se puede establecer una conexion.
// En caso de exito modifica el fd del socket y devuelve 0.
// Retorna -1 en caso contrario.
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

// Verifica si se pudo establecer una conexion entre el fd y la direccion
// recibida. Retorna true en caso positivo y false en caso contrario.
bool Socket::_couldConnect(int socket_fd, struct addrinfo *info) {
    int status = ERROR;
    if (socket_fd != ERROR) {
        status = ::connect(socket_fd, info->ai_addr, info->ai_addrlen);
        if (status == ERROR) ::close(socket_fd);
    }
    return (status != ERROR);
}



