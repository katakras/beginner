#include "Includes.h"
#include "Application.h"
#include "TCPServerManager.h"
#include "SocketEx.h"

TCPServerManager::TCPServerManager()
{
	clntCnt = 0;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup() Error!" << endl;
		exit(-1);

		hMutex = CreateMutex(NULL, FALSE, NULL);
	}
	Application::manager = this;
}

TCPServerManager::~TCPServerManager()
{
	CloseHandle(hMutex);
	WSACleanup();
}

void TCPServerManager::StartThread(SocketEx * sock, unsigned (_stdcall*threadMain)(void *))
{
	WaitForSingleObject(hMutex, INFINITE);
	clntSocks[clntCnt++] = sock;
	ReleaseMutex(hMutex);

	_beginthreadex(NULL, 0, threadMain, (void *)sock, 0, NULL);
	cout << "Connected Client IP : " << inet_ntoa(sock->sockAddr.sin_addr)
		<< " port : " << sock->sockAddr.sin_port << endl;

}



