#pragma once
#include "Includes.h"

class TCPClientSocket
{
public:
	SOCKET hSocket;
	SOCKADDR_IN servAddr;
public:
	TCPClientSocket(char * arg[]);
	~TCPClientSocket();
	bool Connect();
	int Send(char * message, int bufsize);
	int Receive(char * message, int len);
};