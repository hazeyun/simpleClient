#include <stdio.h>
#include <Windows.h>

#pragma comment (lib, "ws2_32.lib")

#define IP "127.0.0.1"
#define PORT 7406

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET clntSock;
	SOCKADDR_IN svrAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		fprintf(stderr, "fail WSAStartup\n");
		return -1;
	}

	clntSock = socket(PF_INET, SOCK_STREAM, 0);
	if (clntSock == INVALID_SOCKET)
	{
		fprintf(stderr, "fail socket\n");
		WSACleanup();
		return -2;
	}

	memset(&svrAddr, 0, sizeof(svrAddr));
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_addr.S_un.S_addr = inet_addr(IP);
	svrAddr.sin_port = htons(PORT);

	char userId[32] = "user123";
	fprintf(stderr, "input user name : ");
	gets(userId);

	if (connect(clntSock, (SOCKADDR*)&svrAddr, sizeof(svrAddr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "fail connect\n");
		closesocket(clntSock);
		WSACleanup();
		return -3;
	}
	
	send(clntSock, userId, strlen(userId), 0);

	char buf[255] = "";
	while (1)
	{
		fprintf(stderr, "input data : ");
		gets(buf);

		if (strstr(buf, "quit") != 0)
		{
			fprintf(stderr, "client exit!\n");
			break;
		}
		else
		{
			fprintf(stderr, "message - %s\n", buf);
			send(clntSock, buf, strlen(buf), 0);
		}

	}

	return 0;
}