#ifndef TP3_TALLER_CLIENT_H
#define TP3_TALLER_CLIENT_H
#include <fstream>
#include "../common_src/Socket.h"
#include <string>
#include <utility>

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

    // Envia al servidor el mensaje contenido en 'message' al servidor.
    // Retorna la cantidad de bytes enviados.
    ssize_t send(std::string message);

    // Envia el contenido del archivo 'file' al servidor.
    // Retorna la cantidad de bytes enviados.
    ssize_t send(std::istream &file);

    // Recibe informacion del servidor y la escribe en el archivo 'file'.
    ssize_t receive(std::ostream &file);

    // Realiza un shut down del cliente de acuerdo al modo recibido.
    // 0 -> SHUT_RD, cierra el socket para lectura.
    // 1 -> SHUT_WR, cierra el socket para escritura.
    // 2 -> SHUT_RDWR, cierra el socket para lectoescritura.
    void shutdown(int mode);

    // Libera los recursos utilizados por el cliente.
    ~Client(){}
};


#endif //TP3_TALLER_CLIENT_H
