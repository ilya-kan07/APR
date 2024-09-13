#include "SocketConnection.h"
#include <iostream>
#include <thread>
#include <chrono>

void StartServer(SocketType& serverSocket, sockaddr_in& addr, int addrSize) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket: " << GET_SOCKET_ERROR << std::endl;
        return;
    }

    if (bind(serverSocket, (sockaddr*)&addr, addrSize) < 0) {
        std::cerr << "Bind failed: " << GET_SOCKET_ERROR << std::endl;
        CLOSE_SOCKET(serverSocket);
        return;
    }

    if (listen(serverSocket, SOMAXCONN) < 0) {
        std::cerr << "Listen failed: " << GET_SOCKET_ERROR << std::endl;
        CLOSE_SOCKET(serverSocket);
        return;
    }

    std::cout << "Server is listening..." << std::endl;
}

SocketType AcceptConnection(SocketType serverSocket, sockaddr_in& addr, int* addrSize) {
    SocketType newConnection = accept(serverSocket, (sockaddr*)&addr, addrSize);
    if (newConnection == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << GET_SOCKET_ERROR << std::endl;
    }
    else {
        std::cout << "Client connected!" << std::endl;
    }
    return newConnection;
}

bool ConnectToServer(SocketType& connection, sockaddr_in& addr) {
    connection = socket(AF_INET, SOCK_STREAM, 0);
    if (connection == INVALID_SOCKET) {
        std::cerr << "Failed to create socket: " << GET_SOCKET_ERROR << std::endl;
        return false;
    }

    if (connect(connection, (sockaddr*)&addr, sizeof(addr)) != 0) {
        std::cerr << "Connection failed: " << GET_SOCKET_ERROR << std::endl;
        return false;
    }

    std::cout << "Connected to server!" << std::endl;
    return true;
}
