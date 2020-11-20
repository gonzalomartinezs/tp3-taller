#include "SocketClosedException.h"
#include <cstring>

SocketClosedException::SocketClosedException() noexcept {
    char* message = (char*)"Error: The socket is closed\0";
    memset(this->error_message, 0, BUF_LEN);
    strncpy(this->error_message, message, BUF_LEN);
}

const char *SocketClosedException::what() const noexcept {
    return this->error_message;
}
