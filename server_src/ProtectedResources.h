#ifndef TP3_TALLER_PROTECTEDRESOURCES_H
#define TP3_TALLER_PROTECTEDRESOURCES_H
#include <string>
#include <map>
#include <mutex>

class ProtectedResources {
private:
    std::map<std::string, std::pair<std::string, std::string>> resources;
    std::mutex mutex;

public:
    // Pre: el archivo es valido.
    // Post: Crea un monitor listo para ser utilizado.
    ProtectedResources(std::string resource,
                       std::ifstream& resource_file);

    // Agrega un recurso y sus respectivos protocolo y body al map de recursos.
    void
    add(std::string &&resource, std::string &&protocol, std::string &&body);

    // Retorna un par (protocolo, body) correspondiente al recurso requerido.
    std::pair<std::string, std::string> search(std::string resource);

    ~ProtectedResources(){}
};


#endif //TP3_TALLER_PROTECTEDRESOURCES_H
