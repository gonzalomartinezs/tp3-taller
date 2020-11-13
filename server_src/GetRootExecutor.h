#ifndef TP3_TALLER_GETROOTEXECUTOR_H
#define TP3_TALLER_GETROOTEXECUTOR_H
#include "InstructionExecutor.h"
#include "ProtectedResources.h"

class GetRootExecutor: public InstructionExecutor {
private:
    ProtectedResources& resources;
    std::string protocol;
public:
    // Crea un ejecutor de la instrucción 'GET /' listo para ser ejecutado.
    GetRootExecutor(ProtectedResources &resources, std::string &protocol):
                                    resources(resources), protocol(protocol) {}

    // Genera la respuesta en base a los atributos del petitorio.
    std::string run() override;

    // Libera los recursos utilizados por el ejecutor de instrucciones.
    ~GetRootExecutor(){}
};


#endif //TP3_TALLER_GETROOTEXECUTOR_H
