#ifndef TP3_TALLER_GETRESOURCEEXECUTOR_H
#define TP3_TALLER_GETRESOURCEEXECUTOR_H
#include "InstructionExecutor.h"
#include "ProtectedResources.h"
#include <string>

class GetResourceExecutor: public InstructionExecutor {
private:
    ProtectedResources& resources;
    const std::string resource;
    const std::string received_protocol;

public:
    // Crea un ejecutor de la instruccion 'GET /' listo para ser ejecutado.
    GetResourceExecutor(std::string& protocol, std::string& resource,
                        ProtectedResources& resources): resources(resources),
                        resource(resource), received_protocol(protocol){}

    // Genera la respuesta en base a los atributos del petitorio.
    std::string run() override;

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~GetResourceExecutor() override{}
};

#endif //TP3_TALLER_GETRESOURCEEXECUTOR_H
