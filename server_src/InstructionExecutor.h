#ifndef TP3_TALLER_INSTRUCTIONEXECUTOR_H
#define TP3_TALLER_INSTRUCTIONEXECUTOR_H

#include <string>

class InstructionExecutor {
private:
    std::string method;
    std::string protocol;

public:
    // Crea un ejecutor de instrucciones listo para ser ejecutado.
    InstructionExecutor(std::string& method, std::string& protocol):
                                    method(method), protocol(protocol){}
    // Constructor por default.
    InstructionExecutor(){}

    // Genera la respuesta en base a los atributos del petitorio.
    virtual std::string run();

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~InstructionExecutor(){}
};


#endif //TP3_TALLER_INSTRUCTIONEXECUTOR_H
