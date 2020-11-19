#include "ProtectedResources.h"
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#define EMPTY ""
#define NOT_FOUND "not_found"

ProtectedResources::ProtectedResources(std::string resource,
                                       std::ifstream& resource_file) {
    std::stringstream content;
    content << resource_file.rdbuf();
    this->resources[resource] = {EMPTY, content.str()};
}

void ProtectedResources::add(std::string &&resource, std::string &&protocol,
                             std::string &&body) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->resources[resource] = {protocol, body};
}

std::pair<std::string, std::string>
        ProtectedResources::search(std::string resource) {
    std::lock_guard<std::mutex> lock(this->mutex);
    if (this->resources.find(resource) != this->resources.end()) { //existe
        return this->resources[resource];
    }
    std::pair<std::string, std::string> not_found;
    not_found.first = NOT_FOUND;
    not_found.second = NOT_FOUND;
    return not_found;
}
