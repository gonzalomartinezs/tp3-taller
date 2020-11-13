#include "PostRootExecutor.h"

std::string PostRootExecutor::run() {
    return (this->protocol + " 403 FORBIDDEN\n\n");
}
