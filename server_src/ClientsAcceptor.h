#ifndef TP3_TALLER_CLIENTSACCEPTOR_H
#define TP3_TALLER_CLIENTSACCEPTOR_H
#include "Thread.h"
#include "../common_src/Socket.h"
#include "ClientThread.h"
#include <atomic>
#include <list>

class ClientsAcceptor: public Thread {
private:
    std::list<ClientThread*> clients;
    ProtectedResources& resources;
    Socket& server_socket;
    bool clients_released;

public:
    // Crea un aceptador de clientes listo para ser utilizado.
    ClientsAcceptor(Socket& socket, ProtectedResources& resources):
                                server_socket(socket), resources(resources),
                                clients_released(false){}

    // Se borran el constructor por copia y el operador =.
    ClientsAcceptor(const ClientsAcceptor&) = delete;
    ClientsAcceptor operator=(const ClientsAcceptor&) = delete;

    // Ejecuta la acción del aceptador de clientes.
    void run() override;

    // Libera los recursos utilizados por el aceptador de clientes.
    ~ClientsAcceptor() override;

private:
    void _releaseClients();
};


#endif //TP3_TALLER_CLIENTSACCEPTOR_H
