#ifndef TP3_TALLER_GETRESOURCEEXECUTOR_H
#define TP3_TALLER_GETRESOURCEEXECUTOR_H
#include "InstructionExecutor.h"
#include "ProtectedResources.h"

class GetResourceExecutor: public InstructionExecutor {
private:
    const std::string received_protocol;
    const std::string resource;
    ProtectedResources& resources;

public:
    // Crea un ejecutor de la instrucción 'GET /' listo para ser ejecutado.
    GetResourceExecutor(std::string& protocol, std::string& resource,
                        ProtectedResources& resources): resources(resources),
                        resource(resource), received_protocol(protocol){}

    // Genera la respuesta en base a los atributos del petitorio.
    std::string run() override;

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~GetResourceExecutor(){}
};

#endif //TP3_TALLER_GETRESOURCEEXECUTOR_H
