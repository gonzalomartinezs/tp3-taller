#ifndef TP3_TALLER_HTMLREQUESTPARSER_H
#define TP3_TALLER_HTMLREQUESTPARSER_H

#include <string>

class HTMLRequestParser {
private:
    std::string method;
    std::string resource;
    std::string protocol;
    std::string body;

public:
    // Crea un parser de petitorios listo para ser utilizado.
    HTMLRequestParser(){}

    // Pre: El petitorio posee el formato correcto.
    // Post: Parsea el petitorio recibido y almacena los elementos del mismo
    // como atributo de la clase.
    void parse(std::stringstream &request);

    // Retorna el método del último petitorio parseado.
    std::string getRequestMethod() const;

    // Retorna el método del último petitorio parseado.
    std::string getRequestResource() const;

    // Retorna el método del último petitorio parseado.
    std::string getRequestProtocol() const;

    // Retorna el método del último petitorio parseado.
    std::string getRequestBody() const;

    // Libera los recursos utilizados por el parser.
    ~HTMLRequestParser(){}
};


#endif //TP3_TALLER_HTMLREQUESTPARSER_H
