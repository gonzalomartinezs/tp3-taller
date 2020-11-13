#include "HTMLInstruction.h"
#include "GetRootExecutor.h"
#include "GetResourceExecutor.h"
#include "PostResourceExecutor.h"
#include "PostRootExecutor.h"

HTMLInstruction::HTMLInstruction(std::string &method, std::string &resource,
                                 std::string &protocol, std::string &body,
                                 ProtectedResources &resources) {
    if (method == "GET" && resource == "/"){
        executor = new GetRootExecutor(resources, protocol);
    } else if (method == "GET"){
        executor = new GetResourceExecutor(protocol, resource, resources);
    } else if (method == "POST" && resource == "/"){
        executor = new PostRootExecutor(protocol);
    } else if (method == "POST"){
        executor = new PostResourceExecutor(protocol, resource, body, resources);
    } else {
        executor = new InstructionExecutor(method, protocol);
    }
}

std::string HTMLInstruction::generateResponse() {
    return executor->run();
}

HTMLInstruction::~HTMLInstruction() {
    delete executor;
}
