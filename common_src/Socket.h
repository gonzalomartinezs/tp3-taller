#ifndef TP3_TALLER_SOCKET_H
#define TP3_TALLER_SOCKET_H

#include <string>

class Socket {
private:
    int fd;
    bool is_closed{};
    explicit Socket(int fd): fd(fd){}
    static void _setHints(struct addrinfo* hints);
    int _tryToBind(struct addrinfo*results);
    int _tryToConnect(struct addrinfo* results);
    static bool _couldBind(int socket_fd, struct addrinfo* info);
    static bool _couldConnect(int socket_fd, struct addrinfo* info);

public:
    // Crea un socket listo para ser utilizado.
    Socket():fd(-1), is_closed(false){}

    Socket(const Socket&) = default;
    Socket operator=(const Socket&) = delete;

    // Enlaza una dirección al socket de acuerdo al 'service' requerido.
    // Establece una lista de espera de acuerdo a 'acceptance'.
    void bindAndListen(const std::string& service, int acceptance);

    // Acepta la conexión de la primer petición de conexión de la lista de
    // espera. Si la operación es exitosa, retorna el coket aceptado.
    Socket accept() const;

    // Conecta el socket a una dirección de acuerdo al 'host' y al 'service'
    // requerido.
    void connect(const std::string& host, const std::string& service);

    // Envía 'length' bytes del 'buffer'. Retorna la cantidad de bytes enviados
    // en caso de éxito y -1 si hubo algún error.
    ssize_t send(const void* buffer, size_t length) const;

    // Recibe una cantidad de bytes menor o igual a 'length' y la carga en
    // 'buffer'. Retorna la cantidad de bytes recibidos en caso de éxito y -1
    // si hubo algún error.
    ssize_t receive(void *buffer, size_t length) const;

    void shutdown(int mode) const;

    void close() const;

    ~Socket();
};


#endif //TP3_TALLER_SOCKET_H
