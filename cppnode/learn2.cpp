#include "learn2.h"

	const int buf(512);//�޶�һ����������512
	int N(5);//����ĳ���
	char buffer[buf] = { 0 };//��̬��

#pragma region new
void mainNew()
{
	//p1,p3,p5��Ϊָ�������ջ�����洢�ĵ�ַָ�����
	//�ֶ��ͷ��ڴ�

	//p2,p4,p6��Ϊָ�������ջ�����洢�ĵ�ַ�ھ�̬������������
	//�Զ��ͷ��ڴ棬���ڷ��������˾Ͳ������õ�����
	//�����ڴ�й©���Զ��ͷ��ڴ档�������ڴ���ʶ����ԣ�

	double* p1, * p2;

	std::cout << "\n\n\n";
	p1 = new double[N];//�����ڴ棬N��Ԫ�صĴ�С
	p2 = new (buffer)double[N];//ָ����������ڴ�
	for (int i = 0; i < N; i++)
	{
		p1[i] = p2[i] = i + 10.8;//���������ʼ��
		std::cout << "p1===   " << &p1[i] << "  " << p1[i];
		std::cout << "   p2===   " << &p2[i] << "  " << p2[i] << std::endl;
	}

	double* p3, * p4;
	std::cout << "\n\n\n";
	p3 = new double[N];//�����ڴ棬N��Ԫ�صĴ�С
	p4 = new (buffer)double[N];//ָ����������ڴ�

	for (int i = 0; i < N; i++)
	{
		p3[i] = p4[i] = i + 10.8;//���������ʼ��
		std::cout << "p3===   " << &p3[i] << "  " << p3[i];
		std::cout << "   p4===   " << &p4[i] << "  " << p4[i] << std::endl;
	}

	double* p5, * p6;
	std::cout << "\n\n\n";
	p5 = new double[N];//�����ڴ棬N��Ԫ�صĴ�С
	p6 = new (buffer)double[N];//ָ����������ڴ�

	for (int i = 0; i < N; i++)
	{
		p6[i] = p5[i] = i + 10.8;//���������ʼ��
		std::cout << "p5===   " << &p5[i] << "  " << p5[i];
		std::cout << "   p6===   " << &p6[i] << "  " << p6[i] << std::endl;
	}
	std::cin.get();
}
#pragma endregion

#pragma region wrapper
//������װ��
//��һ�����ִ�нӿ�,�ӿ���ƹؿ�����������
//�ڶ���������װ�������ں���ģ�壬ʵ��ͨ�÷���
//�������������������Ƕ������һ��������ʵ�ֺ�������
//������װ�������ڹ�����Ƕ�������ⲿ��������





//������װ���� T�������ͣ� F�Ǻ���
template<typename T, typename F>
T run(T v, F f)
{
	static int count = 0;
	count++;//������
	std::cout << "run  һ�������İ�װ�� ִ��" << count << "��" << std::endl;
	if (count > 1)
	{
		T  vx(0);
		return  vx;
	}
	return f(v);//�����������

}
template<typename T, typename F>
T run(T v1, T v2, F f)
{

	return f(v1, v2);//�����������

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
	function<int(int, int)> fun4 = cheng; //fun4����ָ��

	cout << run(db, fun1) << endl;//����
	cout << run(db, fun2) << endl;//����
	cout << run(num1, num2, fun3) << endl;//����
	cout << run(num1, num2, fun4) << endl;//����
	cin.get();//�ȼ���������һ�ַ�getchar;
}
#pragma endregion


#pragma region template overide

//����ģ��ʵ��ͨ�ã����Ը��������������ͣ������Ż�

//�ṹ��û��˽�б�������ֱ�Ӹ�ֵ��ʼ��
//���г�Ա���ǹ��е����Ϳ��Ը�ֵ��ʼ��
struct info
{
	char name[40];
	double db;
	int data;
};

template<typename T>
void swap(T& a, T& b)
{
	std::cout << "ͨ�ú���ģ��" << std::endl;
	T temp = a;
	a = b;
	b = temp;//������������

}
//ģ��Ϊ�գ���ȷ�������ͣ����Ǻ���ģ������ͣ�

void  swap(info& info1, info& info2)
{
	std::cout << "���к���ģ��" << std::endl;
	//ͨ��ģ�����ʵ��ͨ�ã�����Լ����������������Ż�
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
	swap(num1, num2);//ʵ�ֽ���
	std::cout << num1 << "  " << num2 << std::endl;
	char  ch1 = 'Z';
	char  ch2 = 'A';
	swap<char>(ch1, ch2);
	std::cout << ch1 << "  " << ch2 << std::endl;
	std::cin.get();//getchar
}

#pragma endregion


#pragma region template override private field
////����ģ��ʵ��ͨ�ã����Ը��������������ͣ������Ż�
//
////�ṹ�����ֱ�Ӹ�ֵ��û��˽�б�����
//
////���г�Ա���ǹ��е����Ϳ��Ը�ֵ��һ��ʼ��ʼ����
////�������˽�г�Ա��������������{}��ʼ��
//
////��Ķ���֮��Ĭ���ǿ���ֱ�Ӹ�ֵ
//
////�࣬�ṹ�嶼��һ��Ĭ�ϸ�ֵ����= ǳ���� ����������
//
////����õ���࣬����ģ��ĸ���
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
//		this->num = X;//ͨ���ӿ�����˽�б���
//	}
//	int get()
//	{
//		return this->num;//����ֵ����������
//	}
//
//
//};
//
//template<typename T>
//void swap(T& a, T& b)
//{
//	std::cout << "ͨ�ú���ģ��" << std::endl;
//	T temp = a;
//	a = b;
//	b = temp;//������������
//
//}
//
//
////ģ��Ϊ�գ���ȷ���ͣ�
//template<>
//void  swap(info& info1, info& info2)
//{
//	std::cout << "���к���ģ��" << std::endl;
//	//ͨ��ģ�����ʵ��ͨ�ã�����Լ����������������Ż�
//	//�����������󽻻�������
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
//	info2.data = 201;//��ʼ��
//	info1.p = new char[10];
//	std::strcpy(info1.p, "ħ��");
//
//
//	//info2.p = nullptr;//C++�Ŀ�ָ��
//	info2.p = new char[100];
//	std::strcpy(info2.p, "daħ��");
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

//�º���������һ������ָ�룬����һ���ṹ���ڲ�����һ�����ڲ��Ĺ��к���

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
	//��������ָ�룬��ṹ�壬����˽�У����빲��
	//����ͨ�����ã�������Ҫ���ݶ�������������
	void(MyStruct:: * p)(int a) = &MyStruct::add;





}

int mainbind1()
{
	using namespace std::placeholders;
	MyStruct struct1;
	//auto�Զ���������ַ������ָ�룬bind��
	//��һ�����������ڲ���������һ��ʵ�����
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
//using  FUNC = int (*)(int a, int b);//����
//using  co = std::ios_base::fmtflags;//usingֻ�������ڼ�д��������
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

	// thread::hardware_concurrency�߳�
	auto n = thread::hardware_concurrency();
	std::cout << n << std::endl;
	//��ȡ��ǰ�̱߳��
	std::cout << "thread=" << get_id() << std::endl;


	thread thread1(msg);//�������߳�
	thread thread2(msg);
	thread1.join();//��ʼִ��
	thread2.join();





	std::cin.get();



}

void main2()
{

	vector<thread*> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.push_back(new thread(msg));//�����߳�
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
		threads.push_back(new thread(msgA, i));//�����߳�
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
	//�ֽ�>4
#ifdef  M
  // static_assert(sizeof(num) >= 4, "yincheng error");
#endif


	//���Դ��룬Ѹ�ٴ����������һ��

	cin.get();
}
#pragma endregion
