#ifndef _USERC_H_
#define _USERC_H_
#include <winsock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

void sendData(SOCKET hClientSocket);
std::string listenData(SOCKET hClientSocket);
bool InitWinSock2_0();

#endif // !1






// TODO: Haga referencia aquí a los encabezados adicionales que el programa requiere.
