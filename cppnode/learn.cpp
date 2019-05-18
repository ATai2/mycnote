#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstdarg>
// cstdarg 处理通用类型
#include<locale>

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

		//strcpy(this->dataa, str1);
		//strcpy(this->datab, str2);
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

//函数模板  可变参数
//参数至少要有一个是模板类型
template<typename NT>
NT sum(int count, NT data1 ...)//累加
{
	va_list arg_ptr;//参数列表的指针
	va_start(arg_ptr, count);//限定从count开始,限定多少个参数
	NT sumres(0);
	for (int i = 0; i < count; i++)
	{
		sumres += va_arg(arg_ptr, NT);
	}
	va_end(arg_ptr);//结束
	return sumres;
}

//自动数据类型，根据实际推导出类型，
template<class T1, class T2>//根据类型获取类型
auto get(T1 data, T2 bigdata)->decltype(data* bigdata)
{

	return  data * bigdata;
}
//函数参数不允许使用自动变量
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
#pragma endregion


#pragma region kuangzifu
void mainWchar()
{
	//setlocale(LC_ALL, "chs");//设置本地化
	//wchar_t* p1 = L"123456123123qweqeqe";
	//std::wcout << p1 << std::endl;
	//wchar_t* p2 = L"北京123456";
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
//	int(&ra)[10](a);//引用就是给原来的变量有一个别名同一个地址
//	int  i = 0;
//	for (auto data: ra)//C++11的循环
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
//	int(&ra)[2][5](a);//引用就是给原来的变量有一个别名同一个地址
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
//	//int(*&rp)(int a, int b)(p);//引用函数指针
//	//rp=jian;//（）仅仅适用于初始化
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
//	//引用数组是非法的
//}
//struct mystr 
//{
//
//	
//	int b;
//	double a;
//	char c;
//	//代码区的函数不计入结构体的sizeof
//	void go()
//	{
//		std::cout << "123456789" << std::endl;
//	}
//};
//class MyClass
//{
//	char &  a;
//	char &  b;
//	char & c;//引用的本质是指针，直接sizeof引用，就是求引用的数据大小
//	//引用变量占据4个字节
//
//};
//
//
//void main6()
//{
//	int num = 10;
//	int & rnum(num);
//	double db = 10.9;
//	double & rdb(db);//直接作用引用的变量
//
//	std::cout << sizeof(rnum) << std::endl;
//	std::cout << sizeof(rdb) << std::endl;
//	std::cout << sizeof(MyClass) << std::endl;
//	system("pause");
//}
//int  getdata(int && num)//右值引用，节约内存拷贝，内存优化所必须
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
////左值，一般可以取地址就是左值
////右值某些情况可以，某些情况不可以
//void main8()
//{
//	int a = 3;
//	int b = a + 1;//右值->左值
//	std::cout << getdata(std::move(a) ) << std::endl;
//	//std::move将左值转换为右值，C++11
//
//
//}
//void main9()
//{
//	//const int num(6);
//	char str[10]("hello");//限定字符串不被修改
//	const char *pc(str);//指向常量的指针限定了指向的数据无法修改,+1，+2，+3
//	str[3] = 'x';//可以，
//	//pc[3] = 'y';
//	//*(pc + 3) = 'y';
//	pc = "world";
//}
//
//void main10()
//{
//	char str[10]("hello"); 
//	const char(&rstr)[10](str);//常量引用
//	const char(&rrstr)[10](rstr);//引用可以给另一个引用初始化
//	str[4] = 'X';
//	//rstr[4] = 'Y';
//}
//
//void  main11()
//{
//
//	int(*p)(int a, int b)(jia);
//	std::cout << p(1, 2) << std::endl;
//	int(* const &rp)(int a, int b)(p);//引用函数指针
//	//rp=jian;//（）仅仅适用于初始化
//}

// std::move(a) ;    左值转换为右值
#pragma endregion


