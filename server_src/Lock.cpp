#include "Lock.h"

Lock::Lock(std::mutex& m) : m(m) {
    this->m.lock();
}

Lock::~Lock() {
    this->m.unlock();
}
