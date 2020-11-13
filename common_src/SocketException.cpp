#include "SocketException.h"
#include <cstdio>
#include <cerrno>
#include <cstdarg>
#include <cstring>

SocketException::SocketException(const char *fmt, ...) noexcept {
    this->_errno = errno;
    memset(this->error_message, 0, BUF_LEN);
    va_list args;
    va_start(args, fmt);
    int s = vsnprintf(this->error_message, BUF_LEN, fmt, args);
    va_end(args);
    if (_errno != 0) {
        strncpy(this->error_message + s, strerror(_errno), BUF_LEN - s);
    }
    this->error_message[BUF_LEN - 1] = 0;
}

const char *SocketException::what() const noexcept {
    return this->error_message;
}
