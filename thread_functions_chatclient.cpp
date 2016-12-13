#include "thread_functions.h"
#include "TCPClientSocket.h"
#include "Application.h"

unsigned WINAPI SendMsg(void * arg)
{
	TCPClientSocket * sock = (TCPClientSocket*)arg;
	const int name_size = Application::manager->NAME_LEN;
	const int buf_size = Application::manager->BUF_SIZE;
	char message[buf_size];
	char nameMsg[name_size + buf_size];
	int strLen = 0;

	while (1)
	{
		fgets(message, buf_size, stdin);
		sprintf(nameMsg, "%s %s", Application::manager->name, message);
		strLen = strlen(nameMsg) + 1;
		sock->Send(nameMsg, strLen);
	}
	return 0;
}

unsigned WINAPI RecvMsg(void * arg)
{
	int recvLen = 0;
	TCPClientSocket * sock = (TCPClientSocket*)arg;
	const int name_size = Application::manager->NAME_LEN;
	const int buf_size = Application::manager->BUF_SIZE;

	char nameMsg[name_size + buf_size];
	char cpyMsg[name_size + buf_size];
	char * exitPtr;

	while (1)
	{
		recvLen = recv(sock->hSocket, nameMsg, name_size + buf_size - 1, 0);
		if (recvLen == -1)
			return -1;


		strcpy(cpyMsg, nameMsg);
		strtok(cpyMsg, " ");
		exitPtr = strtok(NULL, " ");

		if (!strcmp("q\n", exitPtr) || !strcmp("Q\n", exitPtr))
		{
			if (!strcmp(cpyMsg, Application::manager->name))
			{
				delete sock;
				exit(0);
			}
			sprintf(nameMsg, "%s %s", cpyMsg, "님이 퇴장했습니다!\n");
		}
		fputs(nameMsg, stdout);
	}

	return 0;
}