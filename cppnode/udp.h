#pragma once
#include<stdio.h>
#include<stdlib.h>

#pragma comment(lib, "ws2_32.lib")

#include<WinSock2.h>
//#ifndef  UDP_H
//
//#define UDP_H
//
//extern "C"{
//	int socket_send(int port, char* addrStr);
//}
//#endif // ! UDP_H

#ifdef __cplusplus 
extern "C" {
#endif

	int socket_send(int port, char* addrStr);

#ifdef __cplusplus 
}
#endif

int sum();



