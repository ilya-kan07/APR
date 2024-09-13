#ifndef SOCKET_CONNECTION_H
#define SOCKET_CONNECTION_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

typedef SOCKET SocketType;
#define CLOSE_SOCKET closesocket
#define GET_SOCKET_ERROR WSAGetLastError()

inline bool InitSockets() {
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    return WSAStartup(DLLVersion, &wsaData) == 0;
}

inline void CleanupSockets() {
    WSACleanup();
}

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>

typedef int SocketType;
#define INVALID_SOCKET (-1)
#define CLOSE_SOCKET close
#define GET_SOCKET_ERROR errno

inline bool InitSockets() {
    // Для Linux и UNIX систем инициализация не требуется
    return true;
}

inline void CleanupSockets() {
    // Для Linux и UNIX систем очистка не требуется
}

#endif

void StartServer(SocketType& serverSocket, sockaddr_in& addr, int addrSize);
SocketType AcceptConnection(SocketType serverSocket, sockaddr_in& addr, int* addrSize);
bool ConnectToServer(SocketType& connection, sockaddr_in& addr);

#endif // SOCKET_CONNECTION_H
