#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstdarg>
// cstdarg ����ͨ������
#include<locale>

#pragma region auto
//�Զ��������Զ���ȡ���ͣ����������
//�Զ�����������ʵ���Զ�ѭ��һά����
//�Զ�ѭ����ʱ�򣬶�Ӧ�ı����ǳ���

void main1()
{
	auto num = 10.9;//�Զ��������Զ�ƥ������
	auto numA = 10 / 3.0;
	std::cout << num << "     " << numA << std::endl;
	system("pause");
}

void mainAuto()
{
	//int num[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	double num[2][5] = { 1.0, 2.0, 3.0, 4.5, 5, 6, 7, 8, 9, 10 };
	//num��������һ��ָ�볣��
	//auto �Զ�ѭ�� begin  endl;��������һ������ĳ���
	//
	for (auto data : num)//����C++�﷨,ѭ��һά����,����
	{
		std::cout << data << std::endl;

		for (int i = 0; i < 5; i++)
		{
			std::cout << *(data + i) << std::endl;
		}
	}
	system("pause");


}
#pragma endregion


#pragma region struct

//�������ݻ��к���
struct bigdatacom
{
protected://�ڲ�˽��
	char dataa[100];
	char datab[100];
public://���й���
	void init(const char* str1, const char* str2)
	{
		std::cout << typeid(*this).name() << std::endl;;

		//strcpy(this->dataa, str1);
		//strcpy(this->datab, str2);
	}
	char* getbigdata()
	{
		int lengtha = strlen(dataa);
		int lengthb = strlen(datab);
		int* pres = (int*)malloc(sizeof(int) * (lengtha + lengthb));
		memset(pres, 0, sizeof(int) * (lengtha + lengthb));//��ʼ��
		//�۳�
		for (int i = 0; i < lengtha; i++)
		{
			for (int j = 0; j < lengthb; j++)
			{
				pres[i + j + 1] += (dataa[i] - '0') * (datab[j] - '0');
			}
		}
		//��λ
		for (int i = lengtha + lengthb - 1; i >= 0; i--)
		{
			if (pres[i] >= 10)//��λ
			{
				pres[i - 1] += pres[i] / 10;//��λ
				pres[i] %= 10;//ȡ����λ��
			}

		}
		int i = 0;
		while (pres[i] == 0)
		{
			i++;//ǡ�ò�Ϊ0��λ��
		}
		char* lastres = (char*)malloc(sizeof(char) * (lengtha + lengthb));
		int j;
		for (j = 0; j < lengtha + lengthb; j++, i++)
		{
			lastres[j] = pres[i] + '0';
		}
		lastres[j] = '\0';
		return lastres;
		//printf("last���=%s", lastres);
	}





};

struct myclass :public  bigdatacom //�̳�
{
	void coutstr()//����
	{
		std::cout << this->dataa << this->datab << std::endl;
	}

};


void mainStruct()
{
	myclass  class1;
	class1.init("12345", "1000");
	std::cout << class1.getbigdata() << std::endl;
	class1.coutstr();
	system("pause");
}

#pragma endregion

#pragma region newdelete

class tansheng1
{
	int* p;
	int length;
public:
	tansheng1()//������ʱ���ʼ��
	{
		std::cout << "̷ʤ������" << std::endl;
	}
	~tansheng1()//ɾ����ʱ���ͷ��ڴ�
	{
		std::cout << "̷ʤ������" << std::endl;
	}


};

void main123123()
{
	tansheng1* p = new tansheng1;
	delete  p;//�����������ͣ�delete,�������ͱ���[]
	system("pause");
}

class tansheng
{
public:
	static int jishuqi;//��̬
	int* p;
	int length;
public:
	tansheng()//������ʱ���ʼ��
	{
		std::cout << "̷ʤ������" << std::endl;
		this->length = 10;
	}
	~tansheng()//ɾ����ʱ���ͷ��ڴ�
	{
		std::cout << "̷ʤ������" << std::endl;
	}

	static void* operator new(size_t size)
	{
		jishuqi += 1;
		std::cout << "���󱻴���" << std::endl;
		tansheng* ptemp = NULL;
		//ptemp = (tansheng *) malloc(size);//::new tansheng;//�ٳ�
		return ptemp;

	}

	static void  operator delete(void* p)
	{
		jishuqi -= 1;
		std::cout << "��������" << std::endl;
		::delete p;//::ȫ��
	}
};
int tansheng::jishuqi = 0;

//����ڲ���newû����ɷ����ڴ�Ķ���
//ͨ��ȫ�ֵ�new�м�����һ���ٳ�


//����ռһ���ֽڣ���ʾ�Լ�����
//��Ķ��������Ƕ����������ǹ����
//û�з����ڴ棬���캯��������
class MyClass
{
	int num;
public:
	MyClass();
	~MyClass();

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

void mainNewDelete()
{

	tansheng* p1 = new tansheng;
	tansheng* p2 = new tansheng;
	tansheng* p3 = new tansheng;
	tansheng* p4 = new tansheng;
	std::cout << p1 << p2 << std::endl;
	delete p1;
	delete p2;
	std::cout << tansheng::jishuqi << std::endl;
	std::cout << "myclass size" << sizeof(MyClass) << std::endl;
	int* p = new int;

	system("pause");
}
#pragma endregion


#pragma region template function

template<typename T> T MAX(T* p, const int n)
{
	T maxdata(p[0]);
	for (int i = 0; i < n; i++)
	{
		maxdata = maxdata > p[i] ? maxdata : p[i];
	}
	return maxdata;
}

//����ģ��  �ɱ����
//��������Ҫ��һ����ģ������
template<typename NT>
NT sum(int count, NT data1 ...)//�ۼ�
{
	va_list arg_ptr;//�����б��ָ��
	va_start(arg_ptr, count);//�޶���count��ʼ,�޶����ٸ�����
	NT sumres(0);
	for (int i = 0; i < count; i++)
	{
		sumres += va_arg(arg_ptr, NT);
	}
	va_end(arg_ptr);//����
	return sumres;
}

//�Զ��������ͣ�����ʵ���Ƶ������ͣ�
template<class T1, class T2>//�������ͻ�ȡ����
auto get(T1 data, T2 bigdata)->decltype(data* bigdata)
{

	return  data * bigdata;
}
//��������������ʹ���Զ�����
//int putnum(auto num)
//{
//
//}


void mainTemplate()
{
	std::cout << typeid(get(12.0, 'A')).name() << std::endl;
	std::cout << get(12.0, 'A') << std::endl;
	std::cout << typeid(get(12, 'A')).name() << std::endl;
	std::cout << get(12, 'A') << std::endl;
	system("pause");
}
#pragma endregion


#pragma region bigdata


//�������ݻ��к���
struct bigdatacom
{
protected://�ڲ�˽��
	char dataa[100];
	char datab[100];
public://���й���
	void init(const char* str1, const char* str2)
	{
		std::cout << typeid(*this).name() << std::endl;;

		strcpy(this->dataa, str1);
		strcpy(this->datab, str2);
	}
	char* getbigdata()
	{
		int lengtha = strlen(dataa);
		int lengthb = strlen(datab);
		int* pres = (int*)malloc(sizeof(int) * (lengtha + lengthb));
		memset(pres, 0, sizeof(int) * (lengtha + lengthb));//��ʼ��
		//�۳�
		for (int i = 0; i < lengtha; i++)
		{
			for (int j = 0; j < lengthb; j++)
			{
				pres[i + j + 1] += (dataa[i] - '0') * (datab[j] - '0');
			}
		}
		//��λ
		for (int i = lengtha + lengthb - 1; i >= 0; i--)
		{
			if (pres[i] >= 10)//��λ
			{
				pres[i - 1] += pres[i] / 10;//��λ
				pres[i] %= 10;//ȡ����λ��
			}
		}
		int i = 0;
		while (pres[i] == 0)
		{
			i++;//ǡ�ò�Ϊ0��λ��
		}
		char* lastres = (char*)malloc(sizeof(char) * (lengtha + lengthb));
		int j;
		for (j = 0; j < lengtha + lengthb; j++, i++)
		{
			lastres[j] = pres[i] + '0';
		}
		lastres[j] = '\0';
		return lastres;
		//printf("last���=%s", lastres);
	}
};

struct myclass :public  bigdatacom //�̳�
{
	void coutstr()//����
	{
		std::cout << this->dataa << this->datab << std::endl;
	}

};
#pragma endregion


#pragma region kuangzifu
void mainWchar()
{
	//setlocale(LC_ALL, "chs");//���ñ��ػ�
	//wchar_t* p1 = L"123456123123qweqeqe";
	//std::wcout << p1 << std::endl;
	//wchar_t* p2 = L"����123456";
	//std::wcout << p2 << std::endl;

	//system("pause");
}
#pragma endregion

#pragma region function reference

//#include<iostream>
//#include<stdlib.h>
////	int a[10]
////  int (&ra)[10]
////   int a[2][5]
////   int (&ra)[2][5]
//void main1()
//{
//	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	int(&ra)[10](a);//���þ��Ǹ�ԭ���ı�����һ������ͬһ����ַ
//	int  i = 0;
//	for (auto data: ra)//C++11��ѭ��
//	{
//		data = i + 5;
//		std::cout << data << std::endl;
//
//	}
//	std::cout << a << ra << std::endl;
//	std::cout << &a << &ra << std::endl;
//
//	system("pause");
//}
//
//void main2()
//{
//	int a[2][5] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	int(&ra)[2][5](a);//���þ��Ǹ�ԭ���ı�����һ������ͬһ����ַ
//	for (int i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			std::cout << " " << ra[i][j];
//		}
//		std::cout << "\n";
//	}
//
//
//
//	std::cout << a << ra << std::endl;
//	std::cout << &a << &ra << std::endl;
//
//	system("pause");
//
//
//
//
//}
//
//int jia(int a, int b)
//{
//	return a + b;
//}
//int jian(int a, int b)
//{
//	return a - b;
//}
//
//void change(int(* & rp)(int,int))
//{
//	rp = jian;
//}
//
//void main3()
//{
//	int(* p)(int a, int b)(jia);
//	std::cout << p(1, 2) << std::endl;
//	//int(*&rp)(int a, int b)(p);//���ú���ָ��
//	//rp=jian;//�������������ڳ�ʼ��
//
//	change(p);
//	std::cout << p(1, 2) << std::endl;
//}
//
//int(*& changep(int (*&rp)(int,int)))(int, int)
//{
//	rp = jian;
//	return rp;
//}
//void main4()
//{
//	int(*p)(int a, int b)(jia);
//	std::cout << p(1, 2) << std::endl;
//	
//	p = changep(p);
//
//
//	std::cout << p(1, 2) << std::endl;
//
//	system("pause");
//}
//
//void main5()
//{
//	//int *p[4];
//	int a = 1, b = 2, c = 3;
//	int *px[3] = { &a, &b, &c };
//	//int && p [4] = {a,b,c };
//	//���������ǷǷ���
//}
//struct mystr 
//{
//
//	
//	int b;
//	double a;
//	char c;
//	//�������ĺ���������ṹ���sizeof
//	void go()
//	{
//		std::cout << "123456789" << std::endl;
//	}
//};
//class MyClass
//{
//	char &  a;
//	char &  b;
//	char & c;//���õı�����ָ�룬ֱ��sizeof���ã����������õ����ݴ�С
//	//���ñ���ռ��4���ֽ�
//
//};
//
//
//void main6()
//{
//	int num = 10;
//	int & rnum(num);
//	double db = 10.9;
//	double & rdb(db);//ֱ���������õı���
//
//	std::cout << sizeof(rnum) << std::endl;
//	std::cout << sizeof(rdb) << std::endl;
//	std::cout << sizeof(MyClass) << std::endl;
//	system("pause");
//}
//int  getdata(int && num)//��ֵ���ã���Լ�ڴ濽�����ڴ��Ż�������
//{
//	std::cout << num << std::endl;
//	num += 10;
//	return num;
//}
//
//
//void  main7()
//{
//	int a = 5;
//	int b = 4;
//
//	std::cout << getdata(a+1) << std::endl;
//
//	system("pause");
//
//}
////��ֵ��һ�����ȡ��ַ������ֵ
////��ֵĳЩ������ԣ�ĳЩ���������
//void main8()
//{
//	int a = 3;
//	int b = a + 1;//��ֵ->��ֵ
//	std::cout << getdata(std::move(a) ) << std::endl;
//	//std::move����ֵת��Ϊ��ֵ��C++11
//
//
//}
//void main9()
//{
//	//const int num(6);
//	char str[10]("hello");//�޶��ַ��������޸�
//	const char *pc(str);//ָ������ָ���޶���ָ��������޷��޸�,+1��+2��+3
//	str[3] = 'x';//���ԣ�
//	//pc[3] = 'y';
//	//*(pc + 3) = 'y';
//	pc = "world";
//}
//
//void main10()
//{
//	char str[10]("hello"); 
//	const char(&rstr)[10](str);//��������
//	const char(&rrstr)[10](rstr);//���ÿ��Ը���һ�����ó�ʼ��
//	str[4] = 'X';
//	//rstr[4] = 'Y';
//}
//
//void  main11()
//{
//
//	int(*p)(int a, int b)(jia);
//	std::cout << p(1, 2) << std::endl;
//	int(* const &rp)(int a, int b)(p);//���ú���ָ��
//	//rp=jian;//�������������ڳ�ʼ��
//}

// std::move(a) ;    ��ֵת��Ϊ��ֵ
#pragma endregion


