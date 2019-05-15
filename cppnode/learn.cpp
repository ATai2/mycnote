#include<iostream>
#include<stdlib.h>

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

