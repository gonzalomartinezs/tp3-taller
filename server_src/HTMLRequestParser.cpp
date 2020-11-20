#include "HTMLRequestParser.h"
#include <sstream>
#include <string>

void HTMLRequestParser::operator()(std::stringstream &request) {
    request >> this->method;
    request >> this->resource;
    request >> this->protocol;
    size_t body_begin = request.str().find("\n\n");
    if (body_begin != std::string::npos) {
        this->body = request.str().substr(body_begin + 2);
    }
}

std::string HTMLRequestParser::getRequestMethod() const {
    return this->method;
}

std::string HTMLRequestParser::getRequestResource() const {
    return this->resource;
}

std::string HTMLRequestParser::getRequestProtocol() const {
    return this->protocol;
}

std::string HTMLRequestParser::getRequestBody() const {
    return this->body;
}

