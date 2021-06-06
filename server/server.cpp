#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <ws2tcpip.h>
#include "server.h"

using namespace std;


CLIENT_INFO connectedUsers[2];              //maximo num de players.
//192.168.0.13
char* szServerIPAddr = new char[16];         // Ip del server
int nServerPort = 8001;                     // puerto del servidor que se utilizará

int main()
{
    cout << "Introduce tu ip local: ";
    cin >> szServerIPAddr;
    //--Comprobación error incio lib--
    if (!InitWinSock2_0())
    {
        cout << "Unable to Initialize Windows Socket environment" << WSAGetLastError() << endl;
        return -1;
    }

    //1º
    SOCKET hServerSocket;

    hServerSocket = socket(
        AF_INET,        // tipo de direccion TCP/UDP
        SOCK_STREAM,    // especifica TCP
        0               // 0 para AF_INET
    );

    // Asociamiento de direccion con socket.
    if (bindPort(hServerSocket) == -1) return -1;

    // Dejar el socket en modo escucha
    if (listen(hServerSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Unable to put server in listen state" << endl;

        closesocket(hServerSocket);
        WSACleanup();
        return -1;
    }
    cout << "ESCUCHANDO.." << endl;

    // Start the infinite loop
    listenUsers(hServerSocket); //acepta y asigna un espacio y prioridad de juego.
    cout << "User 1: " << inet_ntoa(connectedUsers[0].clientAddr.sin_addr) << endl;
    cout << "User 2: " << inet_ntoa(connectedUsers[1].clientAddr.sin_addr) << endl;
    transferData(); //servidor recibe informacion del cliente.

    closesocket(hServerSocket);
    WSACleanup();
    return 0;
}


bool InitWinSock2_0()
{
    WSADATA wsaData;
    WORD wVersion = MAKEWORD(2, 0);

    if (!WSAStartup(wVersion, &wsaData))
        return true;

    return false;
}

int bindPort(SOCKET hServerSocket)
{
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;                            // The address family. MUST be AF_INET
    serverAddr.sin_addr.s_addr = inet_addr(szServerIPAddr);
    serverAddr.sin_port = htons(nServerPort);

    // Bind the Server socket to the address & port
    if (bind(hServerSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Unable to bind to " << szServerIPAddr << " port " << nServerPort << endl;
        // Free the socket and cleanup the environment initialized by WSAStartup()
        closesocket(hServerSocket);
        WSACleanup();
        return -1;
    }
    cout << "Puertos enlazados corectamente" << endl;
}

void listenUsers(SOCKET hServerSocket)
{
    int nUsers = 0;

    while (nUsers < 2) {
        SOCKET hClientSocket;
        struct sockaddr_in clientAddr;
        int nSize = sizeof(clientAddr);

        hClientSocket = accept(hServerSocket, (struct sockaddr*)&clientAddr, &nSize);
        if (hClientSocket == INVALID_SOCKET)
        {
            cout << "accept( ) failed" << endl;
        }
        else
        {

            (nUsers == 0) ? setPriority(hClientSocket, "Blanco") : setPriority(hClientSocket, "Negro");
            HANDLE hClientThread; //unsigned pointer/index to a int/ resource in kernel (LA OSTIA)
            struct CLIENT_INFO clientInfo;
            clientInfo.clientAddr = clientAddr;
            clientInfo.hClientSocket = hClientSocket;

            cout << "Client connected from " << inet_ntoa(clientAddr.sin_addr) << endl;

            connectedUsers[nUsers] = clientInfo;
            nUsers++;
        }
    }
}

void transferData()
{
    int player = 0;

    while (true)
    {
        int nLength;
        char szBuffer[1024];
        nLength = recv(connectedUsers[player].hClientSocket, szBuffer, sizeof(szBuffer), 0);
        if (nLength > 0)
        {
            szBuffer[nLength] = '\0';
            cout << "Received " << szBuffer << " from " << inet_ntoa(connectedUsers[player].clientAddr.sin_addr) << endl;

            int nCntSend = 0;
            char* pBuffer = szBuffer;

            if (player == 0) player = 1; else player = 0;

            while ((nCntSend = send(connectedUsers[player].hClientSocket, pBuffer, nLength, 0) != nLength))
            {
                if (nCntSend == -1)
                {
                    cout << "Error sending the data to server" << endl;
                    break;
                }
                if (nCntSend == nLength)
                    break;

                pBuffer += nCntSend;
                nLength -= nCntSend;
            }

            if (strcmp(szBuffer, "QUIT") == 0)
            {
                closesocket(connectedUsers[0].hClientSocket); closesocket(connectedUsers[1].hClientSocket);
                return;
            }

        }
    }
}

void setPriority(SOCKET hClientSocket, char szBuffer[]) {

    cout << "Mensaje enviado: " << szBuffer << endl;
    int nLength = strlen(szBuffer);
    int nCntSend = 0;
    char* pBuffer = szBuffer;

    while ((nCntSend = send(hClientSocket, pBuffer, nLength, 0) != nLength))
    {
        if (nCntSend == -1)
        {
            cout << "Error sending the data to server" << endl;
            break;
        }
        if (nCntSend == nLength)
            break;

        pBuffer += nCntSend;
        nLength -= nCntSend;
    }
}