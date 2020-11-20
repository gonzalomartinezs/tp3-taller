#include "ClientsAcceptor.h"
#include <iostream>
#include <list>
#include <utility>
#include "../common_src/SocketClosedException.h"

void ClientsAcceptor::run() {
    while (keep_running) {
        try {
            Socket peer = server_socket.accept();
            this->clients.push_back(new ClientThread(std::move(peer),
                                                     this->resources));
            this->clients.back()->start();
            _releaseDeadClients();
        } catch(SocketClosedException &e) {
            if (keep_running)
                std::cerr << e.what() << std::endl;
        } catch(std::exception &e) {
            std::cerr << e.what() << std::endl;
        } catch(...) {
            std::cout << "Unknown error.\n";
        }
    }
}

void ClientsAcceptor::stop() {
    this->keep_running = false;
}

ClientsAcceptor::~ClientsAcceptor() {
    for (ClientThread* client: this->clients){
        client->stop();
        client->join();
        delete client;
    }
    this->clients.clear();
}
//---------------------------- Metodos privados -----------------------------//

// Realiza un join de los hilos muertos y libera los recursos utilizados por
// los mismos.
void ClientsAcceptor::_releaseDeadClients() {
    std::list<ClientThread *>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end();) {
        if ((*it)->is_dead()) {
            (*it)->join();
            delete (*it);
            it = this->clients.erase(it);
        } else {
            ++it;
        }
    }
}



