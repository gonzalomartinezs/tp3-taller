#ifndef TP3_TALLER_LOCK_H
#define TP3_TALLER_LOCK_H

#include <mutex>

class Lock {
private:
    std::mutex &m;

public:
    // Realiza un lock sobre el mutex recibido.
    explicit Lock(std::mutex &m);

    // Libera el lock.
    ~Lock();

    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    Lock(Lock&&) = delete;
    Lock& operator=(Lock&&) = delete;
};

#endif //TP2_TALLER_LOCK_H
