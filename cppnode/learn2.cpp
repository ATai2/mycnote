#include "learn2.h"

	const int buf(512);//限定一个常量整数512
	int N(5);//数组的长度
	char buffer[buf] = { 0 };//静态区

#pragma region new
void mainNew()
{
	//p1,p3,p5作为指针变量在栈区，存储的地址指向堆区
	//手动释放内存

	//p2,p4,p6作为指针变量在栈区，存储的地址在静态区。缓冲区。
	//自动释放内存，用于分配用完了就不会再用的数据
	//避免内存泄漏，自动释放内存。牺牲了内存访问独立性，

	double* p1, * p2;

	std::cout << "\n\n\n";
	p1 = new double[N];//分配内存，N个元素的大小
	p2 = new (buffer)double[N];//指定区域分配内存
	for (int i = 0; i < N; i++)
	{
		p1[i] = p2[i] = i + 10.8;//对于数组初始化
		std::cout << "p1===   " << &p1[i] << "  " << p1[i];
		std::cout << "   p2===   " << &p2[i] << "  " << p2[i] << std::endl;
	}

	double* p3, * p4;
	std::cout << "\n\n\n";
	p3 = new double[N];//分配内存，N个元素的大小
	p4 = new (buffer)double[N];//指定区域分配内存

	for (int i = 0; i < N; i++)
	{
		p3[i] = p4[i] = i + 10.8;//对于数组初始化
		std::cout << "p3===   " << &p3[i] << "  " << p3[i];
		std::cout << "   p4===   " << &p4[i] << "  " << p4[i] << std::endl;
	}

	double* p5, * p6;
	std::cout << "\n\n\n";
	p5 = new double[N];//分配内存，N个元素的大小
	p6 = new (buffer)double[N];//指定区域分配内存

	for (int i = 0; i < N; i++)
	{
		p6[i] = p5[i] = i + 10.8;//对于数组初始化
		std::cout << "p5===   " << &p5[i] << "  " << p5[i];
		std::cout << "   p6===   " << &p6[i] << "  " << p6[i] << std::endl;
	}
	std::cin.get();
}
#pragma endregion

#pragma region wrapper
//函数包装器
//第一，设计执行接口,接口设计关卡（），计数
//第二，函数包装器依赖于函数模板，实现通用泛型
//第三，函数代码可以内嵌在另外一个函数，实现函数怀孕
//函数包装器，用于管理内嵌函数，外部函数调用





//函数包装器， T数据类型， F是函数
template<typename T, typename F>
T run(T v, F f)
{
	static int count = 0;
	count++;//计数器
	std::cout << "run  一个参数的包装器 执行" << count << "次" << std::endl;
	if (count > 1)
	{
		T  vx(0);
		return  vx;
	}
	return f(v);//函数传入参数

}
template<typename T, typename F>
T run(T v1, T v2, F f)
{

	return f(v1, v2);//函数传入参数

}

int  cheng(int a, int b)
{
	return a * b;
}


void mainWrapper()
{
	double db = 12.9;//double *2
	int  num1 = 19;
	int  num2 = 29;

	function<double(double)> fun1 = [](double u)
	{
		return u * 2;
	};
	function<double(double)> fun2 = [](double u)
	{
		return u * u;
	};
	function<int(int, int)> fun3 = [](int u1, int u2)
	{
		return u1 + u2;
	};
	function<int(int, int)> fun4 = cheng; //fun4函数指针

	cout << run(db, fun1) << endl;//调用
	cout << run(db, fun2) << endl;//调用
	cout << run(num1, num2, fun3) << endl;//调用
	cout << run(num1, num2, fun4) << endl;//调用
	cin.get();//等价于你输入一字符getchar;
}
#pragma endregion


#pragma region template overide

//函数模板实现通用，可以根据自有数据类型，进行优化

//结构体没有私有变量可以直接赋值初始化
//所有成员都是公有的类型可以赋值初始化
struct info
{
	char name[40];
	double db;
	int data;
};

template<typename T>
void swap(T& a, T& b)
{
	std::cout << "通用函数模板" << std::endl;
	T temp = a;
	a = b;
	b = temp;//交换两个变量

}
//模板为空，明确参数类型，覆盖函数模板的类型，

void  swap(info& info1, info& info2)
{
	std::cout << "特有函数模板" << std::endl;
	//通用模板可以实现通用，针对自己的数据类型做出优化
	info temp = info1;
	info1 = info2;
	info2 = temp;
}


void maintemplateOveride()
{
	info info1 = { "yincheng", 20.9, 10 };
	info info2 = { "chengyin",9.2, 1 };
	swap(info1, info2);
	std::cout << info1.name << info1.db << info1.data << std::endl;
	std::cout << info2.name << info2.db << info2.data << std::endl;
	std::cin.get();
}


void maintemplateOveride1()
{
	int num1 = 100;
	int num2 = 10;
	swap(num1, num2);//实现交换
	std::cout << num1 << "  " << num2 << std::endl;
	char  ch1 = 'Z';
	char  ch2 = 'A';
	swap<char>(ch1, ch2);
	std::cout << ch1 << "  " << ch2 << std::endl;
	std::cin.get();//getchar
}

#pragma endregion


#pragma region template override private field
////函数模板实现通用，可以根据自有数据类型，进行优化
//
////结构体可以直接赋值（没有私有变量）
//
////所有成员都是公有的类型可以赋值（一开始初始化）
////如果类有私有成员变量，不可以用{}初始化
//
////类的对象之间默认是可以直接赋值
//
////类，结构体都有一个默认赋值操作= 浅拷贝 ，交换数据
//
////深拷贝用的最多，函数模板的覆盖
//
//
//class info
//{
//public:
//	char name[40];
//	char* p;
//	int data;
//private:
//	int num;
//public:
//	void set(int X)
//	{
//		this->num = X;//通过接口设置私有变量
//	}
//	int get()
//	{
//		return this->num;//返回值，副本机制
//	}
//
//
//};
//
//template<typename T>
//void swap(T& a, T& b)
//{
//	std::cout << "通用函数模板" << std::endl;
//	T temp = a;
//	a = b;
//	b = temp;//交换两个变量
//
//}
//
//
////模板为空，明确类型，
//template<>
//void  swap(info& info1, info& info2)
//{
//	std::cout << "特有函数模板" << std::endl;
//	//通用模板可以实现通用，针对自己的数据类型做出优化
//	//计数器，对象交换计数器
//	info temp = info1;
//	info1 = info2;
//	info2 = temp;
//	//
//
//}
//
//void main()
//{
//	info info1;
//	info info2;
//	std::strcpy(info1.name, "yincheng");
//	std::strcpy(info2.name, "chengyin ");
//	info1.data = 102;
//	info2.data = 201;//初始化
//	info1.p = new char[10];
//	std::strcpy(info1.p, "魔王");
//
//
//	//info2.p = nullptr;//C++的空指针
//	info2.p = new char[100];
//	std::strcpy(info2.p, "da魔王");
//	info1.set(89);
//	info2.set(98);
//
//	swap(info1, info2);
//
//	std::cout << info1.name << "   " << info1.data << "   " << info1.get() << std::endl;
//	std::cout << info1.p << std::endl;
//	std::cout << info2.name << "   " << info2.data << "    " << info2.get() << std::endl;
//	std::cout << info2.p << std::endl;
//	std::cin.get();
//
//
//}

#pragma endregion


#pragma region in function bind

//仿函数，创建一个函数指针，引用一个结构体内部或者一个类内部的公有函数

struct MyStruct
{
	void add(int a)
	{
		cout << a << endl;
	}

	void add2(int a, int b)
	{
		cout << a + b << endl;
	}
	void add3(int a, int b, int c)
	{
		cout << a + b + c << endl;
	}



};
void mainBind()
{
	MyStruct struct1;
	//创建函数指针，类结构体，数据私有，代码共享
	//函数通过调用，调用需要传递对象名进行区分
	void(MyStruct:: * p)(int a) = &MyStruct::add;





}

int mainbind1()
{
	using namespace std::placeholders;
	MyStruct struct1;
	//auto自动变量，地址，函数指针，bind绑定
	//第一个参数引用内部函数，绑定一个实体对象，
	auto func = bind(&MyStruct::add, &struct1, _1);
	auto func2 = bind(&MyStruct::add2, &struct1, _1, _2);
	auto func3 = bind(&MyStruct::add3, &struct1, _1, _2, _3);
	func(100);
	func2(10, 20);
	func3(10, 20, 30);
	cin.get();

	return 0;

}

#pragma endregion

#pragma region remove zhuanyi 

void mainRemoveTrans() {
	std::string path = R"(\home)";
}


//typedef  int(*ADD)(int a, int b);
//using  FUNC = int (*)(int a, int b);//别名
//using  co = std::ios_base::fmtflags;//using只可以用于简写数据类型
#pragma endregion

#pragma region thread

#include <thread>
#include <windows.h>
using namespace std::this_thread;
using namespace std;

void msg()
{
	MessageBoxA(0, "12345", "678910", 0);
}
void msgA(int num)
{
	std::cout << get_id() << "  num=   " << num << std::endl;
}

void main1()
{

	// thread::hardware_concurrency线程
	auto n = thread::hardware_concurrency();
	std::cout << n << std::endl;
	//获取当前线程编号
	std::cout << "thread=" << get_id() << std::endl;


	thread thread1(msg);//创建多线程
	thread thread2(msg);
	thread1.join();//开始执行
	thread2.join();





	std::cin.get();



}

void main2()
{

	vector<thread*> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(new thread(msg));//创建线程
	}

	for (auto th : threads)
	{
		th->join();
	}

	std::cin.get();





}
void main()
{

	vector<thread*> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(new thread(msgA, i));//创建线程
	}

	for (auto th : threads)
	{
		th->join();
	}

	std::cin.get();
}

#pragma endregion


#pragma region hong

#define  N 10
#define M
#include<assert.h>

void mainHong() {
	int num = 100;
	cout << num << endl;
	cout << __FILE__ << endl;
	cout << __LINE__ << endl;
	cout << __DATE__ << endl;
	cout << __TIME__ << endl;
	cout << __FUNCTION__ << endl;

	char  num = 10;
	//字节>4
#ifdef  M
  // static_assert(sizeof(num) >= 4, "yincheng error");
#endif


	//调试代码，迅速代码错误在哪一行

	cin.get();
}
#pragma endregion
