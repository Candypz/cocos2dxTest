// SocketClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	printf("start up client...\n");

	WSADATA wsaData;
	int nRet = WSAStartup(0x0101, &wsaData);
	if (nRet){
		printf("failed to start up socket.\n");
		return 0;
	}

	SOCKET stClient = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addServer;
	addServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addServer.sin_family = AF_INET;
	addServer.sin_port = htons(4000);
	int nErr = connect(stClient, (SOCKADDR*)&addServer, sizeof SOCKADDR);

	while (true){
		char szSendMsg[256] = { 0 };
		std::cin >> szSendMsg;

		if (strcmp(szSendMsg, "q") == 0){
			break;
		}
		send(stClient, szSendMsg, strlen(szSendMsg) + 1, 0);
		
		char szRevBuff[256] = { 0 };
		recv(stClient, szRevBuff, 256, 0);
		printf("receive %s.\n", szRevBuff);
	}
	closesocket(stClient);
	WSACleanup();

	return 0;
}

