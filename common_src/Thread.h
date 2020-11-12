#ifndef TP3_TALLER_THREAD_H
#define TP3_TALLER_THREAD_H
#include <thread>

class Thread {
private:
    std::thread thread;

public:
    // Crea un thread listo para ser utilizado.
    Thread(){}

    // Comienza la ejecución del hilo.
    void start();

    // Libera los recursos utilizados por el thread.
    void join();

    // Ejecuta la acción del hilo.
    virtual void run() = 0;

    // Destruye el thread
    virtual ~Thread() {}
};

#endif //TP3_TALLER_THREAD_H
