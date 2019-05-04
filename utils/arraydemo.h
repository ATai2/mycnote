#include<stdio.h>
#include<stdlib.h>

struct data
{
	int *p;//指针保存数组的起始点
	int length;//保存数组的长度
	int stat;//0代表无序，1代表有序从小到大，2有序从大到小
	int reallength;//实际分配的内存长度
};
struct findres
{
	int **pp;
	int n;
};
//增加，删除，查找，修改，排序,插入

void  init(struct data *pdata);//初始化
void  reinit(struct data *pdata);//使用之后重新初始化
void  addobject(struct data *pdata, int num);//增加一个元素
void  addobjects(struct data *pdata, int *pnum, int n);//增加一个数组
void  printfall(struct data *pdata);//打印所有的数据
int  * finddata(struct data *pdata, int num);//返回第一个找到数据的地址
void  sort(struct data *pdata, int obj);//obj=0,从小大到，否则从到小
void  change(struct data *pdata, int oldnum, int newnum);//实现修改
void  deleteone(struct data *pdata, int num);//删除第一个找到的数据
void  deleteall(struct data *pdata, int num); //删除所有能找到的数据


struct findres findadlldata(struct data *pdata, int num);//返回一片内存，包含所有找到的元素的首地址
void  insert(struct data *pdata, int num, int insertnum, int headback);//数据插入
//1代表前面插入，0代表后面插入







