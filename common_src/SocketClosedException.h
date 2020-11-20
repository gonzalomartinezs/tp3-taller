#ifndef TP3_TALLER_SOCKETCLOSEDEXCEPTION_H
#define TP3_TALLER_SOCKETCLOSEDEXCEPTION_H
#include <exception>
#define BUF_LEN 128

class SocketClosedException : public std::exception {
private:
    char error_message[BUF_LEN];

public:
    // Crea una excepcion lista para ser lanzada.
    explicit SocketClosedException(const char*) noexcept;

    // Especifica el motivo de la excepcion.
    const char* what() const noexcept override;

    // Libera los recursos de la excepcion.
    ~SocketClosedException(){}
};

#endif //TP3_TALLER_SOCKETCLOSEDEXCEPTION_H
