#ifndef TP3_TALLER_POSTRESOURCEEXECUTOR_H
#define TP3_TALLER_POSTRESOURCEEXECUTOR_H
#include <utility>

#include "InstructionExecutor.h"
#include "ProtectedResources.h"

class PostResourceExecutor: public InstructionExecutor {
private:
    const std::string protocol;
    const std::string resource;
    const std::string body;
    ProtectedResources& resources;

public:
    // Crea un ejecutor de la instrucción 'GET /' listo para ser ejecutado.
    PostResourceExecutor(std::string protocol, std::string resource,
                         std::string body, ProtectedResources& resources):
                         resources(resources), resource(std::move(resource)),
                         protocol(std::move(protocol)), body(std::move(body)){}

    // Genera la respuesta en base a los atributos del petitorio.
    std::string run() override;

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~PostResourceExecutor(){}
};

#endif //TP3_TALLER_POSTRESOURCEEXECUTOR_H
