#pragma once
#include "Includes.h"

class SocketEx;

class TCPServerManager
{
public:
	static const int CLNT_SIZE = 512;
	static const int BUF_SIZE = 1024;
private:
	TCPServerManager(const TCPServerManager& sv) {}
	TCPServerManager& operator=(const TCPServerManager& sv) {}
	
public:
	SocketEx* clntSocks[CLNT_SIZE];
	HANDLE hMutex;
	int clntCnt;
	char message[BUF_SIZE];
private:
	WSADATA wsaData;
public:
	TCPServerManager();
	~TCPServerManager();
	void StartThread(SocketEx * sock, unsigned (_stdcall*threadMain)(void*));

};

