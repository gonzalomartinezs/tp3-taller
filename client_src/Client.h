#ifndef TP3_TALLER_CLIENT_H
#define TP3_TALLER_CLIENT_H
#include <fstream>

#include "../common_src/Socket.h"


class Client {
private:
    Socket socket;
    std::string host;
    std::string service;

public:
    // Crea un cliente listo para ser utilizado
    Client(std::string host, std::string service): host(std::move(host)),
                                                service(std::move(service)){}
    // Se borran el constructor por copia y el operador =.
    Client(const Client&) = delete;
    Client operator=(const Client&) = delete;

    // Conecta el cliente al servidor.
    void connect();

    // Envía al servidor el mensaje contenido en 'message' al servidor.
    // Retorna la cantidad de bytes enviados.
    ssize_t send(std::string message);

    // Envía el contenido del archivo 'file' al servidor.
    // Retorna la cantidad de bytes enviados.
    ssize_t send(std::istream &file);

    // Recibe información del servidor y la escribe en el archivo 'file'.
    ssize_t receive(std::ostream &file);

    // Libera los recursos utilizados por el cliente.
    ~Client(){}
};


#endif //TP3_TALLER_CLIENT_H
