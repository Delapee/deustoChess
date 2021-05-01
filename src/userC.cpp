#include <winsock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#include "userC.h"

using namespace std;
//77.225.46.133
//192.168.0.13
char szServerIPAddr[20] = "77.225.46.133";     
int nServerPort = 8001;                                                           
string listened;
string movement;
bool priority;


int main()
{
    cout << "CONECTANDO CHAVALES!!";
    

    if (!InitWinSock2_0())
    {
        cout << "Unable to Initialize Windows Socket environment" << WSAGetLastError() << endl;
        return -1;
    }

    SOCKET hClientSocket;

    hClientSocket = socket(
        AF_INET,        
        SOCK_STREAM,    
        0               
    );

    if (hClientSocket == INVALID_SOCKET)
    {
        cout << "Unable to create Server socket" << endl;
        
        WSACleanup();
        return -1;
    }


    
    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;     
    serverAddr.sin_addr.s_addr = inet_addr(szServerIPAddr);
    serverAddr.sin_port = htons(nServerPort);

    
    if (connect(hClientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "Unable to connect to " << szServerIPAddr << " on port " << nServerPort << endl;
        closesocket(hClientSocket);
        WSACleanup();
        return -1;
    }
    

    listened = listenData(hClientSocket);
    (listened.compare("Blanco") == 0) ? priority = true : priority = false;

    while (listened.compare("QUIT") != 0)
    {

        if (priority == true) {
            sendData(hClientSocket);
            priority = false;
        }
        else {
            listened = listenData(hClientSocket);
            priority = true;
        }

        
    }

    closesocket(hClientSocket);
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

string listenData(SOCKET hClientSocket) {
    int nLength = 0;
    char szBuffer[1024] = "";
    nLength = recv(hClientSocket, szBuffer, sizeof(szBuffer), 0);
    if (nLength > 0)
    {
        szBuffer[nLength] = '\0';
        cout << "ListenData: " << szBuffer << " from server" << endl;
        return szBuffer;
    }
}

void sendData(SOCKET hClientSocket) {
    char szBuffer[1024] = "";
    cout << "Enter the string to send (QUIT) to stop: ";
    cin >> szBuffer;

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