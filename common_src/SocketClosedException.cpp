#include "SocketClosedException.h"
#include <cstring>

SocketClosedException::SocketClosedException(const char* message) noexcept {
    char* info = (char*)"The socket was closed.\0";
    memset(this->error_message, 0, BUF_LEN);
    strncpy(this->error_message, message, BUF_LEN);
    size_t len = strlen(message);
    strncpy(this->error_message+len, info, BUF_LEN-len);
}

const char *SocketClosedException::what() const noexcept {
    return this->error_message;
}
