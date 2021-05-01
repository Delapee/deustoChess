#ifndef _CONEXION_H_
#define _CONEXION_H_

#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <ws2tcpip.h>

struct CLIENT_INFO
{
    SOCKET hClientSocket;                  // 1º
    struct sockaddr_in clientAddr;         // 2º
};

bool InitWinSock2_0();
int bindPort(SOCKET hServerSocket);
void listenUsers(SOCKET hServerSocket);
void transferData();
void setPriority(SOCKET hClientSocket, char szBuffer[]);






#endif