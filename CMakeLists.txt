cmake_minimum_required(VERSION 3.17)
project(tp3-taller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(server_src/)
include_directories(common_src/)
include_directories(client_src/)

add_executable(server
                server_src/main.cpp
                server_src/Server.cpp server_src/Server.h
                server_src/ClientThread.cpp server_src/ClientThread.h
                server_src/Thread.cpp server_src/Thread.h
                server_src/ProtectedResources.cpp server_src/ProtectedResources.h
                server_src/Lock.cpp server_src/Lock.h
                server_src/ClientsAcceptor.cpp server_src/ClientsAcceptor.h
                server_src/HTMLRequestParser.cpp server_src/HTMLRequestParser.h
                common_src/Socket.cpp common_src/Socket.h
        server_src/InstructionExecutor.cpp server_src/InstructionExecutor.h server_src/GetRootExecutor.cpp server_src/GetRootExecutor.h server_src/GetResourceExecutor.cpp server_src/GetResourceExecutor.h server_src/PostRootExecutor.cpp server_src/PostRootExecutor.h server_src/PostResourceExecutor.cpp server_src/PostResourceExecutor.h server_src/HTMLInstruction.cpp server_src/HTMLInstruction.h common_src/SocketException.cpp common_src/SocketException.h)

add_executable(client client_src/main.cpp
        common_src/Socket.cpp common_src/Socket.h
        client_src/Client.cpp client_src/Client.h common_src/SocketException.cpp common_src/SocketException.h)