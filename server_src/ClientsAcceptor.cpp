#include <iostream>
#include "ClientsAcceptor.h"
#include <list>
#include <utility>

void ClientsAcceptor::run() {
    while (this->server_socket.is_valid()){
        Socket peer = server_socket.accept(); // si el socket se cierra el fd
        if (peer.is_valid()){                 // de peer vale -1
            this->clients.push_back(new ClientThread(std::move(peer),
                                                     this->resources));
            this->clients.back()->start();
            std::list<ClientThread*>::iterator it;
            for (it = this->clients.begin(); it != this->clients.end(); ++it) {
                if ((*it) != nullptr && (*it)->is_dead()) {
                    (*it)->join();
                    delete (*it);
                    (*it) = nullptr;
                }
            }
        }
    }
    _releaseClients();
    this->clients_released = true;
}

ClientsAcceptor::~ClientsAcceptor() {
    if (!clients_released){
        _releaseClients();
    }
}

//---------------------------- Metodos privados -----------------------------//

// Corta la ejecucion y realiza un join de los hilos que no se hayan muertos.
// Libera los recursos utilizados.
// Posteriormente, vacia la lista de clientes.
void ClientsAcceptor::_releaseClients() {
    for (ClientThread* client: this->clients){
        if (client != nullptr){
            client->stop();
            client->join();
            delete client;
        }
    }
    this->clients.clear();
}


