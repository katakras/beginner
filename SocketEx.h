#pragma once
#include "Includes.h"

class ServerSocket;

class SocketEx
{
public:
	SOCKET socket;
	SOCKADDR_IN sockAddr;
	int szSockAddr;
public:
	~SocketEx();
	bool Accept(ServerSocket* servSock);
	int Receive(char * message, int bufsize);
	int Send(char * message, int len);
};