#include "PostRootExecutor.h"
#include <string>
std::string PostRootExecutor::run() {
    return (this->protocol + " 403 FORBIDDEN\n\n");
}
