#include "Includes.h"
#include "SocketEx.h"
#include "Application.h"
#include "TCPServerManager.h"
#include "HandleClient.h"

unsigned WINAPI HandleClient(void * arg)
{
	SocketEx * sock = (SocketEx*)arg;
	int recvLen = 0;

	while ((recvLen = recv(sock->socket, Application::manager->message, Application::manager->BUF_SIZE, 0)) != 0)
	{
		if (recvLen == -1)
			break;

		SendMsg(recvLen);
	}
	WaitForSingleObject(Application::manager->hMutex, INFINITE);
	for (int i = 0; i < Application::manager->clntCnt; i++)
	{
		if (sock == Application::manager->clntSocks[i])
		{
			for (int j = i; j < Application::manager->clntCnt - 1; j++)
				Application::manager->clntSocks[j] = Application::manager->clntSocks[j + 1];
		}
	}
	Application::manager->clntCnt--;
	ReleaseMutex(Application::manager->hMutex);
	closesocket(sock->socket);

	return 0;
}

void SendMsg(int len)
{
	WaitForSingleObject(Application::manager->hMutex, INFINITE);
	for (int i = 0; i < Application::manager->clntCnt; i++)
	{
		Application::manager->clntSocks[i]->Send(Application::manager->message, len);
	}
	ReleaseMutex(Application::manager->hMutex);
}
