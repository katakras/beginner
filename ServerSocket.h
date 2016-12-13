#pragma once
#include "Includes.h"

class ServerSocket
{
protected:
	static const int CLNT_SIZE = 512;
public:
	SOCKET servSocket;
	SOCKADDR_IN servAddr;
	char * port;
public:
	virtual bool ConnectServer()=0;
};

class TCPServerSocket : public ServerSocket
{
public:
	TCPServerSocket(char * p);
	~TCPServerSocket();
	virtual bool ConnectServer();
};

class UDPServerSocket : public ServerSocket
{
public:
	UDPServerSocket(char * p);
	~UDPServerSocket();
	virtual bool ConnectServer();
};