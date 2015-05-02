// SocketServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	printf("start up server...\n");

	WSADATA wsaData;
	int nRet = WSAStartup(0x0101, &wsaData);
	if (nRet){
		printf("failed to start up socket.\n");
		return 0;
	}

	SOCKET stServer = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(4000);

	bind(stServer, (SOCKADDR*)&addrServer, sizeof SOCKADDR);
	
	listen(stServer, 5);
	
	SOCKADDR_IN addrClient; 
	int nLen = sizeof SOCKADDR;
	SOCKET stConn = accept(stServer, (SOCKADDR*)&addrClient, &nLen);
	
	while (true){
		char szRevBuffer[1024] = { 0 };
		int nRevRet = recv(stConn, szRevBuffer, 1024, 0);
		if (nRevRet==0||nRevRet==SOCKET_ERROR){
			printf("client reset %d.\n", nRevRet);
			break;
		}
		printf("receive data:%s\n", szRevBuffer);

		char *szSenBuffer = "hello world from server.";
		send(stConn, szSenBuffer, strlen(szSenBuffer) + 1, 0);
	}
	closesocket(stConn);
	closesocket(stServer);
	WSACleanup();

	getchar();
	return 0;
}

