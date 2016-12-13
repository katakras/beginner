#pragma once
#include "Includes.h"
class TCPClientSocket;

class TCPClientManager
{
public:
	static const int NAME_LEN = 20;
	static const int BUF_SIZE = 1024;
	static char name[NAME_LEN];

private:
	WSADATA wsaData;
	HANDLE thread_Receive;
	HANDLE thread_Send;

public:
	TCPClientManager(char * n);
	~TCPClientManager();
	void StartReceiveThread(TCPClientSocket * sock, unsigned (_stdcall * threadMain)(void *));
	void StartSendThread(TCPClientSocket * sock, unsigned(_stdcall * threadMain)(void*));
	void WaitForUntilDone();
};