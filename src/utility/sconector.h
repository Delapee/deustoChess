#pragma once
#include <winsock2.h>
#include <iostream>
#include <string>
#include <string>
#pragma comment(lib, "ws2_32.lib")

class Sconector {
private:
    SOCKET hClientSocket;
    struct sockaddr_in serverAddr;
    bool priority;
    std::string data;

public:
    Sconector(char ip[20], int port);
    ~Sconector();
    std::string getData();
    void setData(std::string d);
    bool getPriority();
    void validPriority();

    bool connectServer();
    void listendata();
    void sendData();
};