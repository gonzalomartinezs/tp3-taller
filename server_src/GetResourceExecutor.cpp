#include "GetResourceExecutor.h"
#include <utility>
#include <string>

#define NOT_FOUND "not_found"

std::string GetResourceExecutor::run() {
    std::pair<std::string, std::string> searched =
                                    resources.search(this->resource);
    if (searched.first==NOT_FOUND && searched.second==NOT_FOUND)
        return (this->received_protocol + " 404 NOT FOUND\n\n");
    return (searched.first + " 200 OK\n\n" + searched.second);
}
