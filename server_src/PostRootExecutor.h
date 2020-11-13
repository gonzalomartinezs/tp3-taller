#ifndef TP3_TALLER_POSTROOTEXECUTOR_H
#define TP3_TALLER_POSTROOTEXECUTOR_H
#include "InstructionExecutor.h"
#include <string>

class PostRootExecutor: public InstructionExecutor {
private:
    const std::string protocol;
public:
    // Crea un ejecutor de la instrucción 'GET /' listo para ser ejecutado.
    PostRootExecutor(std::string& protocol): protocol(protocol) {}

    // Genera la respuesta en base a los atributos del petitorio.
    std::string run() override;

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~PostRootExecutor(){}
};



#endif //TP3_TALLER_POSTROOTEXECUTOR_H
