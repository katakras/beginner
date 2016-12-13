#include "Includes.h"
#include "thread_functions.h"
#include "TCPClientManager.h"
#include "TCPClientSocket.h"
#include "Application.h"
#pragma comment(lib, "TCPClient.lib")

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Usage : "<<argv[0]<<" IP port name" << endl;
		exit(-1);
	}

	TCPClientManager * client = new TCPClientManager(argv[3]);

	char * ag[] = { argv[1], argv[2] };
	TCPClientSocket * socket = new TCPClientSocket(ag);

	if (socket->Connect() == false)
	{
		cout << "Connect() Error!" << endl;
		exit(-1);
	}

	client->StartReceiveThread(socket, RecvMsg);
	client->StartSendThread(socket, SendMsg);

	client->WaitForUntilDone();

	return 0;
}
