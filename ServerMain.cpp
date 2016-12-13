#include "Includes.h"
#include "ServerSocket.h"
#include "SocketEx.h"
#include "TCPServerManager.h"
#include "HandleClient.h"

#pragma comment(lib, "TCPServer.lib")

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Usage : "<<argv[0]<<" port"<<endl;
		exit(-1);
	}

	TCPServerManager * manager = new TCPServerManager();
	ServerSocket * servSock = new TCPServerSocket(argv[1]);
	servSock->ConnectServer();

	while (1)
	{
		SocketEx * rcvSock = new SocketEx;
		rcvSock->Accept(servSock);

		manager->StartThread(rcvSock, HandleClient);
	}

	delete manager;
	return 0;
}
