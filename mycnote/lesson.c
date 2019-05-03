#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>
#include<string.h>

#include"detours.h"

#pragma comment(lib,"detours.lib")

static int (WINAPI* OldMessageBoxW)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) = MessageBoxW;

int
WINAPI
NewMessageBoxW(
	HWND hWnd,
	LPCWSTR lpText,
	LPCWSTR lpCaption,
	UINT uType) {
	printf("call once.\n");
	return 0;
}


//开始拦截
void Hook()
{
	DetourRestoreAfterWith();//恢复原来状态,
	DetourTransactionBegin();//拦截开始
	DetourUpdateThread(GetCurrentThread());//刷新当前线程
	//这里可以连续多次调用DetourAttach，表明HOOK多个函数
	DetourAttach((void**)& OldMessageBoxW, NewMessageBoxW);//实现函数拦截
	DetourTransactionCommit();//拦截生效
}
//取消拦截
void UnHook()
{
	DetourTransactionBegin();//拦截开始
	DetourUpdateThread(GetCurrentThread());//刷新当前线程
	//这里可以连续多次调用DetourDetach,表明撤销多个函数HOOK
	DetourDetach((void**)& OldMessageBoxW, NewMessageBoxW); //撤销拦截函数
	DetourTransactionCommit();//拦截生效
}
// detours hijack funcitons
void testDetours() {

	MessageBoxW(0, L"啊啊啊啊", L"顶顶顶顶顶", 0);
	Hook();
	MessageBoxW(0, L"啊啊啊啊2", L"顶顶顶顶顶2", 0);
	//system("pause");
	//system("calc");
	//printf("%p,%p,%p", system, newsystem, oldsystem);
	//Hook();
	//printf("\n%p,%p,%p", system, newsystem, oldsystem);
	//system("calc");
	getchar();
}