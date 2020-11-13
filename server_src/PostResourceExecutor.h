#ifndef TP3_TALLER_POSTRESOURCEEXECUTOR_H
#define TP3_TALLER_POSTRESOURCEEXECUTOR_H
#include "InstructionExecutor.h"
#include "ProtectedResources.h"
#include <utility>
#include <string>

class PostResourceExecutor: public InstructionExecutor {
private:
    ProtectedResources& resources;
    const std::string resource;
    const std::string protocol;
    const std::string body;

public:
    // Crea un ejecutor de la instruccion 'GET /' listo para ser ejecutado.
    PostResourceExecutor(std::string& protocol, std::string& resource,
                         std::string& body, ProtectedResources& resources):
                         resources(resources), resource(std::move(resource)),
                         protocol(std::move(protocol)), body(std::move(body)){}

    // Genera la respuesta en base a los atributos del petitorio.
    std::string run() override;

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~PostResourceExecutor() override{}
};

#endif //TP3_TALLER_POSTRESOURCEEXECUTOR_H
