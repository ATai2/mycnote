#include"arraydemo.h"
#include "pch.h"
void init(struct data* pdata) //使用之前初始化
{
	pdata->p = NULL;//意味着还没有初始化
	pdata->length = 0;//长度为0；
	pdata->stat = 0;//代表无序
	pdata->reallength = 0;//实际长度
}

void  reinit(struct data* pdata)//使用之后
{
	if (pdata->p == NULL)
	{
		return;
	}
	else
	{
		free(pdata->p);//释放内存
		pdata->p = NULL;//意味着还没有初始化
		pdata->length = 0;//长度为0；
		pdata->stat = 0;//代表无序
		pdata->reallength = 0;//实际长度
	}

}

//增加一个数据
void  addobject(struct data* pdata, int num)
{
	if (pdata->p == NULL)
	{
		pdata->p = (int*)malloc(sizeof(int));//增加一个元素
		pdata->length = 1;//数组标识增加一个元素
		pdata->reallength = 1;//实际长度
		pdata->p[pdata->length - 1] = num;//赋值
	}
	else
	{
		if (pdata->length == pdata->reallength)
		{
			pdata->p = (int*)realloc(pdata->p, (pdata->length + 1) * sizeof(int));
			pdata->length += 1;//数组标识增加一个元素
			pdata->reallength += 1;//实际长度
			pdata->p[pdata->length - 1] = num;//赋值
		}
		else
		{
			pdata->length += 1;//数组标识增加一个元素
			pdata->p[pdata->length - 1] = num;//赋值
		}
	}
}
//增加一个数组
void  addobjects(struct data* pdata, int* pnum, int n) //数组作为参数退化为指针
{
	if (pdata->p == NULL)
	{
		pdata->p = (int*)malloc(sizeof(int) * n);//增加N个元素
		pdata->length = n;//数组标识增加n个元素
		pdata->reallength = n;//实际长度
		for (int i = 0; i < n; i++)
		{
			pdata->p[i] = pnum[i];//拷贝数组
		}
	}
	else
	{
		if (pdata->length + n <= pdata->reallength)
		{
			for (int i = 0; i < n; i++)
			{
				pdata->p[i + pdata->length] = pnum[i];//拷贝数组
			}
			pdata->length += n;//数组标识增加n个元素
		}
		else
		{
			pdata->p = (int*)realloc(pdata->p, (pdata->length + n) * sizeof(int));//重新分配内存

			for (int i = 0; i < n; i++)
			{
				pdata->p[i + pdata->length] = pnum[i];//拷贝数组
			}
			pdata->length += n;//数组标识增加n个元素
			pdata->reallength += n;//增加长度
		}
	}
}


void  printfall(struct data* pdata) //打印所有的数组
{
	for (int i = 0; i < pdata->length; i++)
	{
		printf("%d\n", pdata->p[i]);//输出一个数组
	}
}
void  sort(struct data* pdata, int obj)//obj=0,从小大到，否则从da到小
{
	if (obj == 0)
	{
		for (int i = 0; i < pdata->length - 1; i++)
		{
			for (int j = 0; j < pdata->length - i - 1; j++)
			{
				if (pdata->p[j] > pdata->p[j + 1])// j >j+1  
				{
					int temp = pdata->p[j]; //交换数据
					pdata->p[j] = pdata->p[j + 1];
					pdata->p[j + 1] = temp;
				}
			}
		}
		pdata->stat = 1;//代表从小到大
	}
	else
	{
		for (int i = 0; i < pdata->length - 1; i++)
		{
			for (int j = 0; j < pdata->length - i - 1; j++)//冒泡没循环一次，沉底一个极值
			{
				if (pdata->p[j] < pdata->p[j + 1])// j <j+1  
				{
					//int temp = pdata->p[j]; //交换数据
					//pdata->p[j] = pdata->p[j + 1];
					//pdata->p[j + 1] = temp;
					pdata->p[j] = pdata->p[j] ^ pdata->p[j + 1];
					pdata->p[j + 1] = pdata->p[j] ^ pdata->p[j + 1];
					pdata->p[j] = pdata->p[j] ^ pdata->p[j + 1];
					//0011  0001  3  1
					//p[j]0011
					//p[j + 1]0001
					// p[j]   0010
					//p[j + 1]0001
					// p[j]   0010
					//p[j + 1]0011
					//        0001  a=a^b,b=a^b.a=a^b;
				}
			}
		}
		pdata->stat = 2;//代表从大到小
	}
}


int* finddata(struct data* pdata, int num)
{

	if (pdata->stat == 0)
	{
		for (int i = 0; i < pdata->length; i++)//顺序循环
		{
			printf("查找第%d次\n", i);
			if (num == pdata->p[i])//判定是否相等
			{
				return  &pdata->p[i];//返回一个地址
				break;//跳出循环
			}
		}
		return NULL;
	}
	else if (pdata->stat == 1) //二分查找法//从小到da
	{
		int  shang = 0;//shang
		int xia = pdata->length - 1;//下
		while (shang <= xia)//循环终止条件, 
		{
			int zhong = (shang + xia) / 2;
			printf("%d,%d,%d\n", shang, zhong, xia);
			if (pdata->p[zhong] == num)
			{
				return  &pdata->p[zhong];//返回地址
			}
			else if (pdata->p[zhong] > num)
			{
				xia = zhong - 1;
			}
			else if (pdata->p[zhong] < num)
			{
				shang = zhong + 1;
			}
		}
		return NULL;
	}
	else
	{
		int  shang = 0;//shang
		int xia = pdata->length - 1;//下

		while (shang <= xia)//循环终止条件, 
		{
			int zhong = (shang + xia) / 2;
			printf("%d,%d,%d\n", shang, zhong, xia);
			if (pdata->p[zhong] == num)
			{
				return  &pdata->p[zhong];//返回地址
			}
			else if (pdata->p[zhong] > num)
			{
				//xia = zhong - 1;
				shang = zhong + 1;

			}
			else if (pdata->p[zhong] < num)
			{
				//shang = zhong + 1;
				xia = zhong - 1;

			}
		}
		return NULL;
	}




}
void  change(struct data* pdata, int oldnum, int newnum)//实现修改
{

	int* p = finddata(pdata, oldnum);
	if (p == NULL)
	{
		printf("修改失败，没有找到");
		return;
	}
	else
	{
		*p = newnum;//修改数据
	}

}
////1代表前面插入，0代表后面插入
void  insert(struct data* pdata, int num, int insertnum, int headback)//数据插入
{
	int* p = finddata(pdata, num);//查找数据
	if (p == NULL)
	{
		return NULL;//没有找到
	}
	else
	{
		//找到,前面插入 ，否则后面插入
		if (headback == 1)
		{

			if (pdata->length < pdata->reallength)//不需要分配
			{
				int  curr = p - pdata->p;//获取要插入位置的下标
				for (int i = pdata->length - 1; i >= curr; i--)
				{
					pdata->p[i + 1] = pdata->p[i];//从后向前移动
				}
				pdata->p[curr] = insertnum;//实现插入，前面插入
				pdata->length++;//长度加1
			}
			else
			{
				int  curr = p - pdata->p;//获取要插入位置的下标
				pdata->p = (int*)realloc(pdata->p, (pdata->length + 1) * sizeof(int));//增加分配内存
				pdata->reallength++;//实际长度+1；
				for (int i = pdata->length - 1; i >= curr; i--)
				{
					pdata->p[i + 1] = pdata->p[i];//从后向前移动
				}
				pdata->p[curr] = insertnum;//实现插入，前面插入
				pdata->length++;//长度加1
			}
		}
		else
		{

			if (pdata->length < pdata->reallength)//不需要分配
			{
				int  curr = p - pdata->p;//获取要插入位置的下标

				for (int i = pdata->length - 1; i > curr; i--)//实现移动
				{
					pdata->p[i + 1] = pdata->p[i];//从后向前移动
				}
				pdata->p[curr + 1] = insertnum;//实现插入，hou插入
				pdata->length++;//长度加1
			}
			else
			{
				int  curr = p - pdata->p;//获取要插入位置的下标
				pdata->p = (int*)realloc(pdata->p, (pdata->length + 1) * sizeof(int));//增加分配内存
				pdata->reallength++;//实际长度+1；

				for (int i = pdata->length - 1; i > curr; i--)//实现移动
				{
					pdata->p[i + 1] = pdata->p[i];//从后向前移动
				}
				pdata->p[curr + 1] = insertnum;//实现插入，hou插入
				pdata->length++;//长度加1
			}
		}
	}
}

//删除
void  deleteone(struct data* pdata, int num)
{

	int* p = finddata(pdata, num);//查找数据
	if (p == NULL)
	{
		return NULL;//没有找到,删除，
	}
	else
	{
		int  curr = p - pdata->p;//cur就是要删除的下标
		//printf("\n%d,%p", *p, p);
		//printf("\n%d,%p", pdata->p[curr], &pdata->p[curr]);//输出数据
		for (int i = curr; i < pdata->length - 1; i++)
		{
			pdata->p[i] = pdata->p[i + 1];//从后向前移动
		}
		pdata->length -= 1;//数组元素减去1
	}
}

//删除全部
void  deleteall(struct data* pdata, int num) //删除所有能找到的数据
{
	for (int* p = finddata(pdata, num); p != NULL; p = finddata(pdata, num))
	{
		int  curr = p - pdata->p;//cur就是要删除的下标
		//printf("\n%d,%p", *p, p);
		//printf("\n%d,%p", pdata->p[curr], &pdata->p[curr]);//输出数据
		for (int i = curr; i < pdata->length - 1; i++)
		{
			pdata->p[i] = pdata->p[i + 1];//从后向前移动
		}
		pdata->length -= 1;//数组元素减去1
	}
}
int* find(int* p, int num, int n)//从一个地址开始，N个范围之内找到
{
	for (int i = 0; i < n; i++)//循环
	{
		if (p[i] == num)//判断
		{

			return p + i;//返回找到的地址
			break;
		}
	}
	return NULL;//代表没有找到
}

struct findres findadlldata(struct data* pdata, int num)
{
	struct findres  res1;//构建结构体变量

	int i = 0; //统计找到多少个。
	for (int* p = find(pdata->p, num, pdata->length - 1); p != NULL; p = find(p + 1, num, (pdata->length - 1) - (p - pdata->p)))
	{
		i++;
	}
	res1.n = i;//长度
	int** pint = (int*)malloc(sizeof(int*) * i);//指针数组
	res1.pp = pint;
	for (int* p = find(pdata->p, num, pdata->length - 1), j = 0; p != NULL; j++, p = find(p + 1, num, (pdata->length - 1) - (p - pdata->p)))
	{
		pint[j] = p;//循环赋值
		//printf("\n%p,%d\n", pint[j], *pint[j]);
	}
	return res1;
}

void testUtils() {
	printf("test just test");
}
