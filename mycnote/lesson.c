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
////��ʼ����
//void Hook()
//{
//	DetourRestoreAfterWith();//�ָ�ԭ��״̬,
//	DetourTransactionBegin();//���ؿ�ʼ
//	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
//	//�������������ε���DetourAttach������HOOK�������
//	DetourAttach((void**)& OldMessageBoxW, NewMessageBoxW);//ʵ�ֺ�������
//	DetourTransactionCommit();//������Ч
//}
////ȡ������
//void UnHook()
//{
//	DetourTransactionBegin();//���ؿ�ʼ
//	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�
//	//�������������ε���DetourDetach,���������������HOOK
//	DetourDetach((void**)& OldMessageBoxW, NewMessageBoxW); //�������غ���
//	DetourTransactionCommit();//������Ч
//}
//// detours hijack funcitons
//void testDetours() {
//
//	MessageBoxW(0, L"��������", L"����������", 0);
//	Hook();
//	MessageBoxW(0, L"��������2", L"����������2", 0);
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
//	STARTUPINFO si = { sizeof(si) }; //������Ϣ
//	PROCESS_INFORMATION pi;//�����˽��̵���Ϣ
//	si.dwFlags = STARTF_USESHOWWINDOW; //��ʾ��ʾ����
//	si.wShowWindow = 1; //1��ʾ��ʾ�����Ľ��̵Ĵ��� 
//	wchar_t cmdline[] = L"c://program files//internet explorer//iexplore.exe";
//	CreateProcessW(NULL, cmdline, NULL, NULL, 0, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);//��������
//
//}
#pragma endregion

#pragma region   1 level pointer

void changenum(int num) //�����Ĳ����и������� ���½�һ�����������ɴ��ݹ���������ֵ
{
	num = 3;
	printf("\nchangenum=%p", &num);

}

void  changepnum(int* p)//����ָ�����ɵ�ַ
{
	*p = 2;//*���ݵ�ַ������ȡ������

}

void  mainP2()
{
	int num = 10;
	printf("\nmain num=%p", &num);
	//changenum(num);//��������
	changepnum(&num);//���ݵ�ַ
	printf("\n%d", num);
	getchar();

}

void mainP1()
{
	int num = 10;
	num = 5;//ֱ��
	int* p = &num;
	*p = 6;//����޸�
	printf("%d", num);

	getchar();



}
void test(int a[10])//������һ�����⣬�ܾ��������ƣ����鵱��������ʱ���ǵ�ַ
{
	printf("\ntest =%d", sizeof(a));

	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("\ntest b=%d", sizeof(b));//�������С

}
void test1(int a[10])//������һ�����⣬�ܾ��������ƣ����鵱��������ʱ���ǵ�ַ
{
	a[0] = 9;//������Ϊ�������ı����飬����ֱ�Ӳ����ⲿ����
	for (int i = 0; i < 10; i++)
	{
		printf("\ntest1= a[%d]=%d", i, a[i]);
	}


}

void test2(int* p)//һ��ָ�������Ϊ��������ʽ��������������׵�ַ
{
	*p = 9;
	for (int* px = p; px < p + 10; px++)
	{
		printf("\ntest2 =%d,%p", *px, px);//��ӡ���ݻ��е�ַ
	}

}

void  mainP3()
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("\nmain a=%d", sizeof(a));//�������С
	printf("\n%d", sizeof(a) / sizeof(int));
	test2(a);//���鵱������ʹ��
	for (int i = 0; i < 10; i++)
	{
		printf("\n main= a[%d]=%d", i, a[i]);
	}
	system("pause");
}

void mainP4()
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	printf("%p", a);//a��һ������ָ�룬//a = a;

	int* p = a;//int*����
	printf("\np=%d��a=%d", sizeof(p), sizeof(a));//4�ֽ�,�������������������⴦��
	//�±�ѭ��
	for (int i = 0; i < 10; i++)
	{
		printf("\n%d,%p,%d,%p", p[i], &p[i], *(p + i), p + i);
		//p[i]�ȼ��� *(p+i)   &p[i]=p+i
	}
	//ָ��ѭ��
	for (int* px = a + 9; px >= a; px--)
	{
		printf("\n%d,%p", *px, px);
	}
	getchar();
}
int   go()  //return Ҳ�и������ƣ��Ĵ���
{
	int a = 3;//auto �Զ�����
	printf("%p", &a);
	printf("\n");
	return  a;
}


void mainP5()
{
	//printf("%d,%p", go(),&go()); �����ķ���ֵ������ȡ��ַ
	int x = go();
	printf("%d", x);
	int x1 = go();
	printf("\n%d", x1);
	getchar();
}
int* go1()  //return Ҳ�и������ƣ��Ĵ���
{
	int a = 3;//auto �Զ�����
	printf("%p", &a);

	printf("\n");
	return  &a;
}

void mainP6()
{
	int* p = go1();
	printf("\n\n\n\n");//  ����ִ������Ժ��ڴ汻�����ˣ�û��ʹ�û���ԭ����ֵ,ʹ�ú��ڴ��ֵ�����仯
	printf("%d,%p", *p, p);//��ӡ��ַ��������

	getchar();


}

void mainP7()
{
	char* p = "tasklist  &  pause";//ָ��洢��ַ
	//*p = 'a';//�����ַ����������޸�
	//printf("%p", p);
	char* px = p;
	while (*px != '\0')
	{
		putchar(*px);
		px++;//ָ����ǰŲ
	}

	system(p);

}


void   mainP8()
{
	int num = 10;
	int* p = &num;  //ָ������ͣ����;����˲���
	printf("%d", *p);

	getchar();


}
void   mainP9()
{
	int num = -1;
	//1111 1111  1111 1111   1111 1111   1111 1111   1111 1111 
	//�޷���ȫ������  4294967295
	//�з��ž��ǵ�һ������λ1��������ʣ��ȫ��������
	unsigned int* p1 = &num; //ָ������;�����ν���
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
	printf("%d,%f", info1.num = 10, info1.score = 29);//��ֵ���ʽ��ֵ���ڱ���ֵ������ֵ
	struct info* p1 = &info1;
	printf("\n%d,%f", (*p1).num, (*p1).score);
	printf("\n%d,%f", p1->num, p1->score);//ָ����ʽṹ��������ʽ

	struct info* p2 = (struct info*)malloc(sizeof(struct info));
	p2->num = 18;
	p2->score = 19.8;
	printf("\n%d,%f", (*p2).num, (*p2).score);//��ӡ����
	printf("\n%d,%f", p2->num, p2->score);

	getchar();
}

void mainP11()
{
	struct info* p2 = (struct info*)malloc(sizeof(struct info) * 5);//������̬����
	int i = 0;
	for (struct info* px = p2; px < p2 + 5; px++)//ָ��ѭ��
	{
		px->num = i;
		px->score = i + 3.5;
		i++;
		printf("\n%d,%f", px->num, px->score);//ָ�����

	}
	for (int j = 0; j < 5; j++)
	{
		p2[j].num = i + 3;
		p2[j].score = i + 8.5;
		i++;
		printf("\n%d,%f", p2[j].num, p2[j].score);//�±�
	}
	getchar();

}

union un
{
	int num;//4���ֽ�
	float sh;  //��һ�����ӵĹ�������
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
	p->sh;//ʱ��ֻ��һ����������

	getchar();
}

enum MyEnum
{
	С�� = 0, �೤ = 1, �ų� = 2, ����, ʦ��, ����, ˾�� = 10
};

void mainP13()
{
	enum MyEnum myenum1 = ˾��;
	printf("%d", myenum1);

	enum MyEnum* p = &myenum1;
	printf("\n%d", *p);
	getchar();
}

#define p(x) (x)*(x)  //�Լ�ʵ�ֺ������滻  1+3 *1+3
#define getname(x) #x      //  main    "main"

void mainP14()
{
	//���ݺ����� main ��"main" 
	printf("%p", mainP14);
	printf("\n%d", p(1 + 3));
	printf("\n%s", getname(main));

	getchar();
}
#pragma endregion


#pragma region 2 lever pointer

//�ı�һ����������Ҫ�����ĵ�ַ����Ҫָ������ĵ�ַ 
//double **p1 = &p;����ָ��洢һ��ָ��ĵ�ַ
double  db = 3.5;
double  bd = 4.5;
void changeP(double* p)//�½�һ��ָ��洢�㴫�ݵ�ֵ
{

	p = &bd;
	printf("\nchange=%p", &p);
	printf("\nchange=%f", *p);

}

void  changep(double** pp)
{
	*pp = &bd;//�ı�ָ��
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

void  run(char* p[5]) //����û�и������ƣ������ǵ�ַ			
{
	printf("\nrun=%d", sizeof(p));//4���ֽ�
	for (char** pp = p; pp < p + 5; pp++)
	{
		system(*pp);
	}

}
void  run1(char** px) //����û�и������ƣ������ǵ�ַ			�ַ���ָ����������ö���ָ��ȡ����
{
	printf("\nrun=%d", sizeof(px));//4���ֽ�
	for (char** pp = px; pp < px + 5; pp++)
	{
		system(*pp);
	}

}

void main2levelStr()
{
	char* p[5] = { "calc", "notepad", "mspaint", "tasklist &pause", "write" };
	printf("\nmain=%d", sizeof(p));   // 20  p�Ǹ����飬����Ҫ�ö���ָ�룬��Ϊp++  �������ַ���
	run1(p);
	getchar();
}

void mainx()
{
	char* p[5] = { "calc", "notepad", "mspaint", "tasklist &pause", "write" };

	//for (int i = 0; i < 5; i++)
	//{
	//	system(p[i]);//�±�ķ�ʽ
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	system(*(p + i));�±�
	//}
	//��ѯһ�����飬��Ҫһ��ָ�룬��ѯһ��ָ�����飬��Ҫһ������ָ��

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
//	unsigned int randdata = time(&ts);//��ȡ��ǰʱ��ת��Ϊһ���޷�������
//	srand(randdata);//���������
//	
//	int a[10] = { 0 };
//	int *p[10];
//	for (int i = 0; i < 10; i++)
//	{
//		p[i] = &a[i];//ָ���Ӧ������ÿһ��Ԫ�صĵ�ַ
//	}
//	while (1)
//	{
//		for (int i = 0; i < 10; i++)
//		{
//			a[i] = rand() % 1000;//ȡ�����
//			printf("\n%d", a[i]);//��ӡ����ÿһ��Ԫ��
//		}
//		Sleep(5000);
//		printf("\n");
//		for (int i = 0; i < 10; i++)
//		{
//			if (*p[i] <= 500)
//			{
//				*p[i] += 100;//��Ѫ
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
//static int jia(int a, int b) //�޶�ֻ�б��ļ�ʹ��
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
//	int (*p)(int a, int b)=jia;//�洢����ָ��ĵ�ַ
//	//jia = jia;�������ǳ���ָ��
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
	int* p = (int*)calloc(10, sizeof(int));//�����ڴ�
	printf("%p\n", p);//�����ַ

	for (int i = 0; i < 10; i++)
	{
		*(p + i) = i;//*(p+i)�ȼ���p[i]
	}
	int* pnew = (int*)realloc(p, 100000);//�䳤
	//realloc.��һ�������������ڴ�û���ã���ֱ����չ�䳤
	//�ڶ��������������ڴ������ã��ȷ����µĳ��ȣ�����ԭ�����ڴ棬�ͷŵ�ԭ�����ڴ�
	printf("%p", pnew);
	for (int i = 10; i < 25000; i++)
	{
		*(pnew + i) = i;
	}
	system("pause");
}
#pragma endregion
