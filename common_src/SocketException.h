#ifndef TP3_TALLER_SOCKETEXCEPTION_H
#define TP3_TALLER_SOCKETEXCEPTION_H
#include <exception>
#define BUF_LEN 128

class SocketException : public std::exception {
private:
    int _errno;
    char error_message[BUF_LEN];

public:
    // Crea una excepcion lista para ser lanzada.
    explicit SocketException(const char* fmt, ...) noexcept;

    // Especifica el motivo de la excepcion.
    const char* what() const noexcept override;

    // Libera los recursos de la excepcion.
    ~SocketException(){}
};

#endif //TP3_TALLER_SOCKETEXCEPTION_H
