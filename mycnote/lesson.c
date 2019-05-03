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


//��ʼ����
void Hook()
{
	DetourRestoreAfterWith();//�ָ�ԭ��״̬,
	DetourTransactionBegin();//���ؿ�ʼ
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
	//�������������ε���DetourAttach������HOOK�������
	DetourAttach((void**)& OldMessageBoxW, NewMessageBoxW);//ʵ�ֺ�������
	DetourTransactionCommit();//������Ч
}
//ȡ������
void UnHook()
{
	DetourTransactionBegin();//���ؿ�ʼ
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
	//�������������ε���DetourDetach,���������������HOOK
	DetourDetach((void**)& OldMessageBoxW, NewMessageBoxW); //�������غ���
	DetourTransactionCommit();//������Ч
}
// detours hijack funcitons
void testDetours() {

	MessageBoxW(0, L"��������", L"����������", 0);
	Hook();
	MessageBoxW(0, L"��������2", L"����������2", 0);
	//system("pause");
	//system("calc");
	//printf("%p,%p,%p", system, newsystem, oldsystem);
	//Hook();
	//printf("\n%p,%p,%p", system, newsystem, oldsystem);
	//system("calc");
	getchar();
}