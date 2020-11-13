#include "InstructionExecutor.h"
#include <string>

std::string InstructionExecutor::run() {
    return (this->protocol + " 405 METHOD NOT ALLOWED\n\n" +
            this->method + " es un comando desconocido\n");
}
