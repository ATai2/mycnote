#define _CRT_SECURE_NO_WARNINGS     //关闭安全检查
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>

#include <Windows.h>
#include <process.h>
#include "find.h"

//----------------------------------------主函数开始------------------------------------------------
int mainBigSearch()
{
	//----------------------------------------读取文件------------------------------------------------
	FILE* fp = fopen("res.txt", "r");
	FILE* resFile = fopen("result.txt", "w");
	if (!fp) {
		puts("文件打开失败，按任意键退出程序...");
		getchar();
		return -1;	//main退出
	}

	char* ft[6] = { NULL };	//数据区块头指针数组
	char* pft = NULL;	//数据读取游标指针

	puts("初始化查询系统环境...");
	//读取数据
	for (int i = 0; i < 6; ++i) {
		//申请内存保存读取数据
		ft[i] = (char*)malloc(1024 * 1024 * 200 + 3);
		//判断申请成功否
		if (!ft[i]) {
			puts("申请内存失败，按任意键退出程序...");
			//getchar();
			return -1;	//main退出
		}

		//读取数据开始
		{
			pft = ft[i];
			*pft++ = '\n';
			if (i < 5) {
				//读取数据
				for (int i = 0; i < 50; ++i) {
					fread(pft, 1, 4 * 1024 * 1024, fp);
					//ferror(fp);	//判断读取状态
					pft += 4 * 1024 * 1024;
				}

			}
			else {
				while (!feof(fp)) {		//最后200M给予特别待遇
					fread(pft, 1, 4 * 1024 * 1024, fp);
					pft += 4 * 1024 * 1024;
				}
			}

			*pft++ = '\n';	//添加结尾标志
			*pft = '\0';	//添加结束标志

		}//读取数据结束

	}//end for i=0-6

	fclose(fp);//读取完后关闭文件
//------------------------------------初始化必要数据-----------------------------------------------------------

	char m[120] = "厦门";

	//puts("请输入待查找的数据");
	//scanf("%s", m);

	int res[6] = { 0 };		//保存线程状态和查询结果
	int res_len[6] = { 0 };	//保存结果保存量
	char* out_buf[6] = { NULL };	//文件缓冲


	for (int i = 0; i < 6; ++i) {
		out_buf[i] = (char*)malloc(1024 * 1024 * 10);//分配10M的缓冲
	}
	   
	//开启多线程
	ST st[6];
	for (int i = 0; i < 6; ++i) {
		st[i].key = m;			//待查询的关键字
		st[i].source = ft[i];	//读取来源
		st[i].result = res + i;		//保存查询结果
		st[i].res_len = res_len + i;	//保存结果长度
		st[i].res_out_buf = out_buf[i];		//查询结果缓冲
	}

	int whether = 1;	//是否继续查找的判断

	int starttime = 0;	//计时开始保存
	int endtime = 0;	//计时结束保存

	while (1) {	//循环查找开始

		puts("请输入要查找的关键字：");
		scanf("%s", m);
		starttime = GetTickCount();
		//初始化线程参数，开启多线程查找
		for (int i = 0; i < 6; ++i) {
			res[i] = 0;	//必须初始化为0，不然会影响下一次读取
			res_len[i] = 0;		//必须初始化为0，不然会连同保存上一次结果
			_beginthread(ProcessSeek, 0, st + i);	//开启多线程查找
		}
		//--------------------------------判断查找结果-----------------------------------------------
		int finish = 0;		//判断是否完成搜索
		while (1) {
			Sleep(10);		//每10ms检测一次
			//先加起来，看是否都结束了查找
			finish = res[0] + res[1] + res[2] + res[3] + res[4] + res[5];
			if (finish == 6) {
				//查找结束，没有结果
				endtime = GetTickCount();	//获取查找结束时间

				puts("你要查的东西去火星打酱油了");	//所有线程都结束，且没有找到
				break;	//退出while检查线程
			}

			if ((finish % 10 + finish / 10) == 6) {
				//合并输出的结果文件，并删除临时文件
				{
					//输出结果到文件
					O_F outf;
					for (int i = 0; i < 6; ++i) {
						outf.buf[i] = st[i].res_out_buf;
						outf.count[i] = res_len[i];
					}
					_beginthread(Out_res, 0, &outf);

				}
				endtime = GetTickCount();	//获取查找结束时间
				break;	//所有线程都结束了
			}//end if
		}//end 线程结束检查
		//输出消耗时间
		printf("\n\n消耗时间=%d\n\n", endtime - starttime);
		//所以线程都搞完了，且有搜到的时候,输出结果
		if (((finish % 10 + finish / 10) == 6) && (finish > 10)) {
			//打开保存结果文件
			system("more res.txt");		//不用记事本打开，查询结果可能很大（可达100M）
			system("explorer .");	//打开文件保存文件夹，自己选择打开方式
		}
		//-----------------------------------------开启下一次查找-------------------------------------------
		puts("\n\n是否继续查询其他数据?\n<继续搜索输入：1 / 结束输入：0 >");
		scanf("%d", &whether);
		if (whether == 0) {
			break;
		}
	}// end while(1)
//-------------------------------结束前释放内存--------------------------------------------
	getchar();
	getchar();
	for (int i = 0; i < 6; ++i) {
		free(ft[i]);
		free(st[i].res_out_buf);
	}
	return 0;
}
