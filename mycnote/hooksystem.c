//#include<stdio.h>
//#include<stdlib.h>
//#include<Windows.h>
//#include"detours.h"   //载入头文件
//#pragma comment(lib, "detours.lib")//表明要使用静态库
//// detour在  realse模式生效
//static int (*oldsystem)(const char* _Command) = system;//创建函数指针等于地址
//
//int  newsystem(const char* _Command) //新的函数
//{
//	return 0;
//}
//
//
////开始拦截
//void Hook()
//{
//
//
//	DetourRestoreAfterWith();//恢复原来状态,
//	DetourTransactionBegin();//拦截开始
//	DetourUpdateThread(GetCurrentThread());//刷新当前线程
//	//这里可以连续多次调用DetourAttach，表明HOOK多个函数
//
//	DetourAttach((void**)& oldsystem, newsystem);//实现函数拦截
//
//	DetourTransactionCommit();//拦截生效
//
//
//
//}
////取消拦截
//void UnHook()
//{
//
//
//	DetourTransactionBegin();//拦截开始
//	DetourUpdateThread(GetCurrentThread());//刷新当前线程
//	//这里可以连续多次调用DetourDetach,表明撤销多个函数HOOK
//	DetourDetach((void**)& oldsystem, newsystem); //撤销拦截函数
//	DetourTransactionCommit();//拦截生效
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