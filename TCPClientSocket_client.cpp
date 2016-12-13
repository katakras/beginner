#include "TCPClientSocket.h"

TCPClientSocket::TCPClientSocket(char * arg[])
{
	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		cout << "socket() Error!" << endl;
		exit(-1);
	}
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(arg[0]);
	servAddr.sin_port = htons(atoi(arg[1]));
}

TCPClientSocket::~TCPClientSocket()
{
	closesocket(hSocket);
}

bool TCPClientSocket::Connect()
{
	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		return false;

	return true;
}

int TCPClientSocket::Send(char * message, int bufsize)
{
	return send(hSocket, message, bufsize, 0);
}

int TCPClientSocket::Receive(char * message, int len)
{
	return recv(hSocket, message, len, 0);
}
