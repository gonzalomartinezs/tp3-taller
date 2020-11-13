#ifndef TP3_TALLER_HTMLINSTRUCTION_H
#define TP3_TALLER_HTMLINSTRUCTION_H
#include "InstructionExecutor.h"
#include "ProtectedResources.h"
class HTMLInstruction {
private:
    InstructionExecutor* executor;
public:
    // Crea una instrucción HTML lista para ser lelvada a cabo.
    HTMLInstruction(std::string& method, std::string& resource,
                    std::string& protocol, std::string& body,
                    ProtectedResources& resources);

    // Se borran el constructor por copia y el operador =.
    HTMLInstruction(const HTMLInstruction&) = delete;
    HTMLInstruction operator=(const HTMLInstruction&) = delete;

    // Retorna un string equivalente a la respuesta al petitorio html.
    std::string generateResponse();

    // Libera los recursos utilizados por el objeto.
    ~HTMLInstruction();
};


#endif //TP3_TALLER_HTMLINSTRUCTION_H
