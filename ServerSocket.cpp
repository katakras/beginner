#include "ServerSocket.h"
#include <WinSock2.h>
#include <iostream>
using namespace std;

TCPServerSocket::TCPServerSocket(char * p)
{
	port = p;
	servSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (servSocket == INVALID_SOCKET)
	{
		cout << "socket() Error!";
		exit(-1);
	}
}

bool TCPServerSocket::ConnectServer()
{
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(port));

	if (bind(servSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		return false;

	if (listen(servSocket, CLNT_SIZE) == SOCKET_ERROR)
		return false;	

	return true;
}

TCPServerSocket::~TCPServerSocket()
{
	closesocket(servSocket);
}

UDPServerSocket::UDPServerSocket(char * p)
{
	port = p;
	servSocket = socket(PF_INET, SOCK_DGRAM, 0);

	if (servSocket == INVALID_SOCKET)
	{
		cout << "socket() Error!";
		exit(-1);
	}
}

UDPServerSocket::~UDPServerSocket()
{
	closesocket(servSocket);
}

bool UDPServerSocket::ConnectServer()
{
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(port));

	if (bind(servSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		return false;

	return true;
}
