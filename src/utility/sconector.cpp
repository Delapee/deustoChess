#include <winsock2.h>
#include <iostream>
#include <string>
#include "sconector.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

// Constructores y destructores
Sconector::Sconector(char ip[20], int port)
{
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 0);
	if (WSAStartup(wVersion, &wsaData))
		cout << "Unable to Initialize Windows Socket environment" << WSAGetLastError() << endl;

	this->hClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_addr.s_addr = inet_addr(ip);
	this->serverAddr.sin_port = htons(port);
	this->priority = false;
}

Sconector::~Sconector() {
	closesocket(hClientSocket);
	WSACleanup();
}

// Metodos generales
bool Sconector::getPriority()
{
	return priority;
}

void Sconector::validPriority()
{
	this->priority = true;
}

string Sconector::getData()
{
	return this->data;
}

void Sconector::setData(string d)
{
	this->data = d;
}

// Metodos del socket 
bool Sconector::connectServer()
{
	cout << "Conectando al servidor..." << endl;
	if (connect(this->hClientSocket, (struct sockaddr*)&this->serverAddr, sizeof(this->serverAddr)) < 0)
	{
		closesocket(this->hClientSocket);
		WSACleanup();
		return false;
	}
	return true;
}

void Sconector::listendata()
{
	cout << "Buscando Partida..." << endl;
	char szBuffer[1024] = "";

	while (true)
	{
		int nLength = recv(this->hClientSocket, szBuffer, sizeof(szBuffer), 0);
		if (nLength > 0)
		{
			szBuffer[nLength] = '\0';
			cout << "ListenData: " << szBuffer << " from server" << endl;
			this->data = szBuffer;
			this->priority = false;
			break;
		}
	}
	
}

void Sconector::sendData() {
	char szBuffer[1024] = "";
	strcpy(szBuffer, data.c_str());

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
	this->priority = false;
}