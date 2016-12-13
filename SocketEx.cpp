#include "SocketEx.h"
#include "ServerSocket.h"
#include <WinSock2.h>

SocketEx::~SocketEx()
{
	closesocket(socket);
}

bool SocketEx::Accept(ServerSocket * servSock)
{
	szSockAddr = sizeof(sockAddr);
	socket = accept(servSock->servSocket, (SOCKADDR*)&sockAddr, &szSockAddr);
	if (socket == INVALID_SOCKET)
		return false;

	return true;
}

int SocketEx::Receive(char * message, int bufsize)
{
	return recv(socket, message, bufsize, 0);
}

int SocketEx::Send(char * message, int len)
{
	return send(socket, message, len, 0);
}
