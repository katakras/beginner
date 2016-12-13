#include "TCPClientManager.h"
#include "TCPClientSocket.h"

char TCPClientManager::name[NAME_LEN] = "[default]";

TCPClientManager::TCPClientManager(char * n)
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup() Error!" << endl;
		exit(-1);
	}
	sprintf(name, "[%s]", n);
}

TCPClientManager::~TCPClientManager()
{
	WSACleanup();
}

void TCPClientManager::StartReceiveThread(TCPClientSocket * sock, unsigned (_stdcall *threadMain)(void*))
{
	thread_Receive = (HANDLE)_beginthreadex(NULL, 0, threadMain, (void *)sock, 0, NULL);
}

void TCPClientManager::StartSendThread(TCPClientSocket * sock, unsigned(_stdcall * threadMain)(void*))
{
	thread_Send = (HANDLE)_beginthreadex(NULL, 0, threadMain, (void *)sock, 0, NULL);
}

void TCPClientManager::WaitForUntilDone()
{
	HANDLE threadArray[] = { thread_Receive, thread_Send };
	WaitForMultipleObjects(2, threadArray, true, INFINITE);
}
