#include "GetRootExecutor.h"
#include <utility>
#include <string>

std::string GetRootExecutor::run() {
    std::pair<std::string, std::string> resource = resources.search("/");
    return (this->protocol + " 200 OK\nContent-Type: text/html\n\n" +
            resource.second);
}
