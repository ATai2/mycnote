#include<iostream>
#include<stdlib.h>

#pragma region auto
//自动变量，自动获取类型，输出，泛型
//自动变量，可以实现自动循环一维数组
//自动循环的时候，对应的必须是常量

void main1()
{
	auto num = 10.9;//自动变量，自动匹配类型
	auto numA = 10 / 3.0;
	std::cout << num << "     " << numA << std::endl;
	system("pause");
}

void mainAuto()
{
	//int num[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	double num[2][5] = { 1.0, 2.0, 3.0, 4.5, 5, 6, 7, 8, 9, 10 };
	//num数组名是一个指针常量
	//auto 自动循环 begin  endl;，必须是一个数组的常量
	//
	for (auto data : num)//泛型C++语法,循环一维数组,常量
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

//除了数据还有函数
struct bigdatacom
{
protected://内部私有
	char dataa[100];
	char datab[100];
public://公有公开
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
		memset(pres, 0, sizeof(int) * (lengtha + lengthb));//初始化
		//累乘
		for (int i = 0; i < lengtha; i++)
		{
			for (int j = 0; j < lengthb; j++)
			{
				pres[i + j + 1] += (dataa[i] - '0') * (datab[j] - '0');
			}
		}
		//进位
		for (int i = lengtha + lengthb - 1; i >= 0; i--)
		{
			if (pres[i] >= 10)//进位
			{
				pres[i - 1] += pres[i] / 10;//进位
				pres[i] %= 10;//取出个位数
			}

		}
		int i = 0;
		while (pres[i] == 0)
		{
			i++;//恰好不为0的位置
		}
		char* lastres = (char*)malloc(sizeof(char) * (lengtha + lengthb));
		int j;
		for (j = 0; j < lengtha + lengthb; j++, i++)
		{
			lastres[j] = pres[i] + '0';
		}
		lastres[j] = '\0';
		return lastres;
		//printf("last结果=%s", lastres);
	}





};

struct myclass :public  bigdatacom //继承
{
	void coutstr()//新增
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
	tansheng1()//构建的时候初始化
	{
		std::cout << "谭胜被创建" << std::endl;
	}
	~tansheng1()//删除的时候释放内存
	{
		std::cout << "谭胜被销毁" << std::endl;
	}


};

void main123123()
{
	tansheng1* p = new tansheng1;
	delete  p;//基本数据类型，delete,复杂类型必须[]
	system("pause");
}

class tansheng
{
public:
	static int jishuqi;//静态
	int* p;
	int length;
public:
	tansheng()//构建的时候初始化
	{
		std::cout << "谭胜被创建" << std::endl;
		this->length = 10;
	}
	~tansheng()//删除的时候释放内存
	{
		std::cout << "谭胜被销毁" << std::endl;
	}

	static void* operator new(size_t size)
	{
		jishuqi += 1;
		std::cout << "对象被创建" << std::endl;
		tansheng* ptemp = NULL;
		//ptemp = (tansheng *) malloc(size);//::new tansheng;//劫持
		return ptemp;

	}

	static void  operator delete(void* p)
	{
		jishuqi -= 1;
		std::cout << "对象被销毁" << std::endl;
		::delete p;//::全局
	}
};
int tansheng::jishuqi = 0;

//类的内部的new没有完成分配内存的动作
//通往全局的new中间做了一个劫持


//空类占一个字节，表示自己存在
//类的对象，数据是独立，代码是共享的
//没有分配内存，构造函数无意义
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

