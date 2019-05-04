#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<process.h>
#include<string.h>


#pragma region hijack api
//
//#include"detours.h"
//
//#pragma comment(lib,"detours.lib")
//
//static int (WINAPI* OldMessageBoxW)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType) = MessageBoxW;
//int
//WINAPI
//NewMessageBoxW(
//	HWND hWnd,
//	LPCWSTR lpText,
//	LPCWSTR lpCaption,
//	UINT uType) {
//	printf("call once.\n");
//	return 0;
//}
//
//
////开始拦截
//void Hook()
//{
//	DetourRestoreAfterWith();//恢复原来状态,
//	DetourTransactionBegin();//拦截开始
//	DetourUpdateThread(GetCurrentThread());//刷新当前线程
//	//这里可以连续多次调用DetourAttach，表明HOOK多个函数
//	DetourAttach((void**)& OldMessageBoxW, NewMessageBoxW);//实现函数拦截
//	DetourTransactionCommit();//拦截生效
//}
////取消拦截
//void UnHook()
//{
//	DetourTransactionBegin();//拦截开始
//	DetourUpdateThread(GetCurrentThread());//刷新当前线程
//	//这里可以连续多次调用DetourDetach,表明撤销多个函数HOOK
//	DetourDetach((void**)& OldMessageBoxW, NewMessageBoxW); //撤销拦截函数
//	DetourTransactionCommit();//拦截生效
//}
//// detours hijack funcitons
//void testDetours() {
//
//	MessageBoxW(0, L"啊啊啊啊", L"顶顶顶顶顶", 0);
//	Hook();
//	MessageBoxW(0, L"啊啊啊啊2", L"顶顶顶顶顶2", 0);
//	//system("pause");
//	//system("calc");
//	//printf("%p,%p,%p", system, newsystem, oldsystem);
//	//Hook();
//	//printf("\n%p,%p,%p", system, newsystem, oldsystem);
//	//system("calc");
//	getchar();
//}
//
//
//void mainHijack()
//{
//	//system("calc");
//	//ShellExecuteA(0, "open", "calc", 0, 0, 1);
//	STARTUPINFO si = { sizeof(si) }; //启动信息
//	PROCESS_INFORMATION pi;//保存了进程的信息
//	si.dwFlags = STARTF_USESHOWWINDOW; //表示显示窗口
//	si.wShowWindow = 1; //1表示显示创建的进程的窗口 
//	wchar_t cmdline[] = L"c://program files//internet explorer//iexplore.exe";
//	CreateProcessW(NULL, cmdline, NULL, NULL, 0, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);//创建进程
//
//}
#pragma endregion

#pragma region   1 level pointer

void changenum(int num) //函数的参数有副本机制 ，新建一个变量，容纳传递过来参数的值
{
	num = 3;
	printf("\nchangenum=%p", &num);

}

void  changepnum(int* p)//创建指针容纳地址
{
	*p = 2;//*根据地址与类型取出内容

}

void  mainP2()
{
	int num = 10;
	printf("\nmain num=%p", &num);
	//changenum(num);//传递数据
	changepnum(&num);//传递地址
	printf("\n%d", num);
	getchar();

}

void mainP1()
{
	int num = 10;
	num = 5;//直接
	int* p = &num;
	*p = 6;//间接修改
	printf("%d", num);

	getchar();



}
void test(int a[10])//数组是一个例外，拒绝副本机制，数组当作参数的时候是地址
{
	printf("\ntest =%d", sizeof(a));

	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("\ntest b=%d", sizeof(b));//求数组大小

}
void test1(int a[10])//数组是一个例外，拒绝副本机制，数组当作参数的时候是地址
{
	a[0] = 9;//数组作为参数，改变数组，等于直接操作外部数组
	for (int i = 0; i < 10; i++)
	{
		printf("\ntest1= a[%d]=%d", i, a[i]);
	}


}

void test2(int* p)//一级指针可以作为函数的形式参数接受数组的首地址
{
	*p = 9;
	for (int* px = p; px < p + 10; px++)
	{
		printf("\ntest2 =%d,%p", *px, px);//打印数据还有地址
	}

}

void  mainP3()
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("\nmain a=%d", sizeof(a));//求数组大小
	printf("\n%d", sizeof(a) / sizeof(int));
	test2(a);//数组当作参数使用
	for (int i = 0; i < 10; i++)
	{
		printf("\n main= a[%d]=%d", i, a[i]);
	}
	system("pause");
}

void mainP4()
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("%p", a);//a是一个常量指针，//a = a;

	int* p = a;//int*类型
	printf("\np=%d，a=%d", sizeof(p), sizeof(a));//4字节,数组名编译器做了特殊处理
	//下标循环
	for (int i = 0; i < 10; i++)
	{
		printf("\n%d,%p,%d,%p", p[i], &p[i], *(p + i), p + i);
		//p[i]等价于 *(p+i)   &p[i]=p+i
	}
	//指针循环
	for (int* px = a + 9; px >= a; px--)
	{
		printf("\n%d,%p", *px, px);
	}
	getchar();
}
int   go()  //return 也有副本机制，寄存器
{
	int a = 3;//auto 自动变量
	printf("%p", &a);
	printf("\n");
	return  a;
}


void mainP5()
{
	//printf("%d,%p", go(),&go()); 函数的返回值不可以取地址
	int x = go();
	printf("%d", x);
	int x1 = go();
	printf("\n%d", x1);
	getchar();
}
int* go1()  //return 也有副本机制，寄存器
{
	int a = 3;//auto 自动变量
	printf("%p", &a);

	printf("\n");
	return  &a;
}

void mainP6()
{
	int* p = go1();
	printf("\n\n\n\n");//  函数执行完成以后，内存被回收了，没有使用还是原来的值,使用后内存的值发生变化
	printf("%d,%p", *p, p);//打印地址还有内容

	getchar();


}

void mainP7()
{
	char* p = "tasklist  &  pause";//指针存储地址
	//*p = 'a';//常量字符串不可以修改
	//printf("%p", p);
	char* px = p;
	while (*px != '\0')
	{
		putchar(*px);
		px++;//指针向前挪
	}

	system(p);

}


void   mainP8()
{
	int num = 10;
	int* p = &num;  //指针的类型，类型决定了步长
	printf("%d", *p);

	getchar();


}
void   mainP9()
{
	int num = -1;
	//1111 1111  1111 1111   1111 1111   1111 1111   1111 1111 
	//无符号全部数据  4294967295
	//有符号就是第一个符号位1代表负数，剩下全部是数据
	unsigned int* p1 = &num; //指针的类型决定如何解析
	int* p2 = &num;
	printf("%u,%d", *p1, *p2);
	getchar();
}

struct info
{
	int num;
	float  score;
};

void mainP10()
{
	struct info  info1;
	printf("%d,%f", info1.num = 10, info1.score = 29);//赋值表达式的值等于被赋值变量的值
	struct info* p1 = &info1;
	printf("\n%d,%f", (*p1).num, (*p1).score);
	printf("\n%d,%f", p1->num, p1->score);//指针访问结构体两种形式

	struct info* p2 = (struct info*)malloc(sizeof(struct info));
	p2->num = 18;
	p2->score = 19.8;
	printf("\n%d,%f", (*p2).num, (*p2).score);//打印数据
	printf("\n%d,%f", p2->num, p2->score);

	getchar();
}

void mainP11()
{
	struct info* p2 = (struct info*)malloc(sizeof(struct info) * 5);//构建动态数组
	int i = 0;
	for (struct info* px = p2; px < p2 + 5; px++)//指针循环
	{
		px->num = i;
		px->score = i + 3.5;
		i++;
		printf("\n%d,%f", px->num, px->score);//指针访问

	}
	for (int j = 0; j < 5; j++)
	{
		p2[j].num = i + 3;
		p2[j].score = i + 8.5;
		i++;
		printf("\n%d,%f", p2[j].num, p2[j].score);//下标
	}
	getchar();

}

union un
{
	int num;//4个字节
	float sh;  //穿一条裤子的共用体体
};

void  mainP12()
{
	union un uni1;
	uni1.num = 4;
	printf("%d", uni1.num);
	uni1.sh = 3;
	printf("\n%d", uni1.num);

	union un* p = &uni1;
	p->num;
	p->sh;//时刻只有一个变量存在

	getchar();
}

enum MyEnum
{
	小兵 = 0, 班长 = 1, 排长 = 2, 连长, 师长, 军长, 司令 = 10
};

void mainP13()
{
	enum MyEnum myenum1 = 司令;
	printf("%d", myenum1);

	enum MyEnum* p = &myenum1;
	printf("\n%d", *p);
	getchar();
}

#define p(x) (x)*(x)  //自己实现函数，替换  1+3 *1+3
#define getname(x) #x      //  main    "main"

void mainP14()
{
	//传递函数名 main ，"main" 
	printf("%p", mainP14);
	printf("\n%d", p(1 + 3));
	printf("\n%s", getname(main));

	getchar();
}
#pragma endregion


#pragma region 2 lever pointer

//改变一个变量，需要变量的地址，需要指针变量的地址 
//double **p1 = &p;二级指针存储一级指针的地址
double  db = 3.5;
double  bd = 4.5;
void changeP(double* p)//新建一个指针存储你传递的值
{

	p = &bd;
	printf("\nchange=%p", &p);
	printf("\nchange=%f", *p);

}

void  changep(double** pp)
{
	*pp = &bd;//改变指针
}
void main20()
{

	double* p = &db;
	printf("\nmain=%p", &p);
	printf("\n%f", *p);
	//p = &bd;
	changep(&p);
	printf("\n%f", *p);
	getchar();
}

#pragma endregion

#pragma region 2 level string app pointer

void  run(char* p[5]) //数组没有副本机制，传递是地址			
{
	printf("\nrun=%d", sizeof(p));//4个字节
	for (char** pp = p; pp < p + 5; pp++)
	{
		system(*pp);
	}

}
void  run1(char** px) //数组没有副本机制，传递是地址			字符串指针数组可以用二级指针取代。
{
	printf("\nrun=%d", sizeof(px));//4个字节
	for (char** pp = px; pp < px + 5; pp++)
	{
		system(*pp);
	}

}

void main2levelStr()
{
	char* p[5] = { "calc", "notepad", "mspaint", "tasklist &pause", "write" };
	printf("\nmain=%d", sizeof(p));   // 20  p是个数组，所以要用二级指针，因为p++  不能移字符串
	run1(p);
	getchar();
}

void mainx()
{
	char* p[5] = { "calc", "notepad", "mspaint", "tasklist &pause", "write" };

	//for (int i = 0; i < 5; i++)
	//{
	//	system(p[i]);//下标的方式
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	system(*(p + i));下标
	//}
	//轮询一个数组，需要一个指针，轮询一个指针数组，需要一个二级指针

	for (char** pp = p; pp < p + 5; pp++)
	{
		system(*pp);
	}
}
#pragma endregion


#pragma region function pointer

//void main1()
//{
//	time_t ts;
//	unsigned int randdata = time(&ts);//获取当前时间转换为一个无符号数据
//	srand(randdata);//随机数种子
//	
//	int a[10] = { 0 };
//	int *p[10];
//	for (int i = 0; i < 10; i++)
//	{
//		p[i] = &a[i];//指针对应了数组每一个元素的地址
//	}
//	while (1)
//	{
//		for (int i = 0; i < 10; i++)
//		{
//			a[i] = rand() % 1000;//取随机数
//			printf("\n%d", a[i]);//打印数组每一个元素
//		}
//		Sleep(5000);
//		printf("\n");
//		for (int i = 0; i < 10; i++)
//		{
//			if (*p[i] <= 500)
//			{
//				*p[i] += 100;//加血
//			}
//			printf("\n%d", *p[i]);
//		}
//		Sleep(5000);
//
//		 
//
//	}
//
//
//
//
//
//
//}
//
//void main2()
//{
//	char * p[] = { "calc", "notepad", "mspaint", "write", "tasklist & pause" };
//	int n = sizeof(p) / sizeof(char *);
//	for (int i = 0; i < n; i++)
//	{
//		printf("\n%s",p[i]);
//		system(p[i]);
//
//	}
//
//
//
//}
//
//
//static int jia(int a, int b) //限定只有本文件使用
//{
//	return a + b;
//}
//static  int jian(int a, int b)
//{
//	return a - b;
//}
//static int cheng(int a, int b)
//{
//	return a * b;
//}
//static  int chu(int a, int b)
//{
//	return a / b;
//}
//
//void main3()
//{
//	int (*p)(int a, int b)=jia;//存储函数指针的地址
//	//jia = jia;函数名是常量指针
//	printf("%d", p(1, 2));
//	p = jian;
//	printf("\n%d", p(1, 2));
//
//
//	getchar();
//}
//
//void main4()
//{
//	//int* a;
//	//int* a[10];
//	int(*p[4])(int a, int b) = { jia, jian, cheng, chu };
//	for (int i = 0; i < 4; i++)
//	{
//		printf("\n%d", p[i](10, 2));
//	}
//
//	getchar();
//}

#pragma endregion

#pragma region  multiproccess






#pragma endregion


#pragma region calloc

void mainCalloc()
{
	int* p = (int*)calloc(10, sizeof(int));//分配内存
	printf("%p\n", p);//输出地址

	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i;//*(p+i)等价于p[i]
	}
	int* pnew = (int*)realloc(p, 100000);//变长
	//realloc.第一种情况，后面的内存没人用，就直接拓展变长
	//第二种情况，后面的内存有人用，先分配新的长度，拷贝原来的内存，释放的原来的内存
	printf("%p", pnew);
	for (int i = 10; i < 25000; i++)
	{
		*(pnew + i) = i;
	}
	system("pause");
}
#pragma endregion
