#ifndef TP3_TALLER_SERVER_H
#define TP3_TALLER_SERVER_H

#include "ClientsAcceptor.h"
#include "../common_src/Socket.h"
#include <string>
#include <utility>

class Server {
private:
    Socket socket;
    ProtectedResources resources;
    ClientsAcceptor acceptor;
    std::string service;
    bool is_running;

public:
    // Crea un serivdor listo para ser utilizado
    Server(std::string service, const std::string& resource,
           std::ifstream& rsc_file): resources(resource, rsc_file),
           acceptor(socket, resources), service(std::move(service)),
           is_running(false) {}

    // Se borran el constructor por copia y el operador =.
    Server(const Server&) = delete;
    Server operator=(const Server&) = delete;

    // Deja el servidor listo para recibir conexiones, armando una lista de
    // espera de acuerdo a 'acceptance'.
    void bindAndListen(int acceptance);

    // Pone en ejecucion el servidor.
    void run();

    // Finaliza la ejecucion del servidor.
    void stop();

    // Libera los recursos utilizados por el servidor.
    ~Server();
};


#endif //TP3_TALLER_SERVER_H
