#ifndef TP3_TALLER_CLIENTTHREAD_H
#define TP3_TALLER_CLIENTTHREAD_H
#include "Thread.h"
#include "../common_src/Socket.h"
#include "ProtectedResources.h"
#include "HTMLRequestParser.h"
#include <atomic>

class ClientThread: public Thread {
private:
    Socket peer;
    ProtectedResources& resources;
    HTMLRequestParser parser;
    std::atomic<bool> is_running;
    std::atomic<bool> keep_running;

public:
    // Crea un hilo de cliente listo para ser utilizado.
    ClientThread(Socket&& peer, ProtectedResources& resources):
                                peer(std::move(peer)), is_running(true),
                                keep_running(true), resources(resources){}

    // Ejecuta la acción del hilo del cliente.
    void run() override;

    // Finaliza la ejecución de la acción del hilo del cliente.
    void stop();

    // Retorna un booleano que indica si el hilo se encuentra en ejecución o no.
    bool is_dead();

    ~ClientThread() override{}

private:
    std::string generateResponse(std::stringstream &request_stream);
};


#endif //TP3_TALLER_CLIENTTHREAD_H
