#include "udp.h"

int socket_send(int port,char *addrStr)
{
	// ��ʼ��socket
	DWORD ver;
	WSADATA wsaData;
	ver = MAKEWORD(1, 1);//  ��ʲô�汾��socket
	//wsaData = ;

	int res=WSAStartup(ver,&wsaData);
	// AF_INET  TCP/IP protocal
	// SOCK_DGRAM   UDP

	SOCKET st=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));//��ʼ��addr
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);  //  �����ϴ���1���ֽڵģ�ת���������ֽ���

	addr.sin_addr.S_un.S_addr = inet_pton("127.0.0.1");
	
	char buf[1024] = { 0 };
	strcpy_s(buf,20, "hello world");
	sendto(st, buf, strlen(buf), 0, (struct sockaddr*) & addr,sizeof(addr));

	closesocket(st);
	WSACleanup();
	return 0;
}