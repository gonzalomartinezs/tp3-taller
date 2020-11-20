#ifndef TP3_TALLER_SOCKET_H
#define TP3_TALLER_SOCKET_H

#include <string>

class Socket {
private:
    int fd;
    bool is_closed;

public:
    // Crea un socket listo para ser utilizado.
    Socket():fd(-1), is_closed(false){}

    // Se borran el constructor por copia y el operador =.
    Socket(const Socket&) = delete;
    Socket operator=(const Socket&) = delete;

    // Se redefinen el constructor por movimiento y el operador = por movimiento
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    // Enlaza una direccion al socket de acuerdo al 'service' requerido.
    // Establece una lista de espera de acuerdo a 'acceptance'.
    void bindAndListen(const std::string& service, int acceptance);

    // Acepta la conexion de la primer peticion de conexion de la lista de
    // espera. Si la operacion es exitosa, retorna el coket aceptado.
    Socket accept() const;

    // Conecta el socket a una direccion de acuerdo al 'host' y al 'service'
    // requerido.
    void connect(const std::string& host, const std::string& service);

    // Envia 'length' bytes del 'buffer'. Retorna la cantidad de bytes enviados
    // en caso de exito..
    ssize_t send(const void* buffer, size_t length) const;

    // Recibe una cantidad de bytes menor o igual a 'length' y la carga en
    // 'buffer'. Retorna la cantidad de bytes recibidos en caso de exito.
    ssize_t receive(void *buffer, size_t length) const;

    // Realiza un shut down del socket de acuerdo al modo recibido.
    // 0 -> SHUT_RD, cierra el socket para lectura.
    // 1 -> SHUT_WR, cierra el socket para escritura.
    // 2 -> SHUT_RDWR, cierra el socket para lectoescritura.
    void shutdown(int mode) const;

    // Cierra el socket.
    void close();

    // Lbera los recursos utilizados por el socket.
    ~Socket();

private:
    explicit Socket(int fd): fd(fd), is_closed(false){}
    static void _setHints(struct addrinfo* hints);
    int _tryToBind(struct addrinfo*results);
    int _tryToConnect(struct addrinfo* results);
    static bool _couldBind(int socket_fd, struct addrinfo* info);
    static bool _couldConnect(int socket_fd, struct addrinfo* info);
};


#endif //TP3_TALLER_SOCKET_H
