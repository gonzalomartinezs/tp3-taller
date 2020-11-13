#include "PostResourceExecutor.h"
#include <utility>
#include <string>

std::string PostResourceExecutor::run() {
    std::string added_resource = this->resource;
    std::string added_protocol = this->protocol;
    std::string added_body = this->body;
    this->resources.add(std::move(added_resource), std::move(added_protocol),
                        std::move(added_body));
    return (this->protocol + " 200 OK\n\n" + this->body);
}
