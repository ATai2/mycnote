#include<stdio.h>
#include<stdlib.h>

//#pragma comment(lib, "ws2_32.lib")

#include<WinSock2.h>

int socket_send(int port,char *addrStr)
{
	// 初始化socket
	DWORD ver;
	WSADATA wsaData;
	ver = MAKEWORD(1, 1);//  用什么版本的socket
	//wsaData = ;

	WSAStartup(ver,&wsaData);
	// AF_INET  TCP/IP protocal
	// SOCK_DGRAM   UDP

	SOCKET st=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));//初始化addr
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);  //  主机上大于1个字节的，转化成网络字节流

	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	


}
