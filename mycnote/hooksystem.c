//#include<stdio.h>
//#include<stdlib.h>
//#include<Windows.h>
//#include"detours.h"   //����ͷ�ļ�
//#pragma comment(lib, "detours.lib")//����Ҫʹ�þ�̬��
//// detour��  realseģʽ��Ч
//static int (*oldsystem)(const char* _Command) = system;//��������ָ����ڵ�ַ
//
//int  newsystem(const char* _Command) //�µĺ���
//{
//	return 0;
//}
//
//
////��ʼ����
//void Hook()
//{
//
//
//	DetourRestoreAfterWith();//�ָ�ԭ��״̬,
//	DetourTransactionBegin();//���ؿ�ʼ
//	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
//	//�������������ε���DetourAttach������HOOK�������
//
//	DetourAttach((void**)& oldsystem, newsystem);//ʵ�ֺ�������
//
//	DetourTransactionCommit();//������Ч
//
//
//
//}
////ȡ������
//void UnHook()
//{
//
//
//	DetourTransactionBegin();//���ؿ�ʼ
//	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
//	//�������������ε���DetourDetach,���������������HOOK
//	DetourDetach((void**)& oldsystem, newsystem); //�������غ���
//	DetourTransactionCommit();//������Ч
//}
//
//void mainHookSys()
//{
//	system("calc");
//	printf("%p,%p,%p", system, newsystem, oldsystem);
//	Hook();
//	printf("\n%p,%p,%p", system, newsystem, oldsystem);
//	system("calc");
//	getchar();
//
//}