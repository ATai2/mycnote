#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>

#include <Windows.h>

//找出一行
int findline(char* dest, char *p, int * offset)
{
	char *pdest = dest;
	char *poff = p;
	while (*p-- != '\n');
	++p;

	while (*++p != '\n'){
		*pdest++ = *p;
	}
	*pdest = '\n';
	*offset = p - poff;	//计算偏移量
	return pdest - dest + 1;	//返回长度（包括结束）

}


//查找数据
int seek(char* dest, char* scr, char *fbuf, int *res_lenght)
{
	assert(dest && scr);
	int l = strlen(dest);
	int k = ((*dest)&(0x80)) ? 10 : 0;
	int offsetlen = 0;
	char *tail = fbuf;		//记录输出了多远
	//i = 0;	//控制输出数量
	while (*(scr + l)){
		if (memcmp(dest, scr, l)){

		}
		else{
			*res_lenght += findline(tail, scr, &offsetlen);	//取出查找到的位置的那一行
			tail = fbuf + *res_lenght;
			scr += k + offsetlen;
		}
		scr++;
	}
	return *res_lenght;
}

//多线程查找
//多线程参数结构体
typedef struct MyStruct ST;
struct MyStruct
{
	char *key;	//待查找目标
	char *source;	//供查找的资源
	int *result;	//查找是否完成结果指针
	int *res_len;	//查找到的字符串结果总的长度
	char *res_out_buf;	//结果输出到缓冲
};

void ProcessSeek(void *seg)
{
	ST *st = (ST*)seg;
	if (seek(st->key, st->source, st->res_out_buf, st->res_len)){
		*(st->result) = 10;	//查找到了，修改为10。后面加起来判断6个加起来后个位加10位是否为6判断是否结束
	}
	else{
		*(st->result) = 1;	//没有查到，就1。后面判断6个想加是否大于10来判断是否查到
	}
	//不管有没有查到，只要返回了，就不是0
}
typedef struct out_f O_F;
struct out_f{
	char* buf[6];
	int count[6];
};


void Out_res(void *f)
{
	O_F *pb = (O_F*)f;
	FILE *fpres = fopen("res.txt", "w");
	for (int i = 0; i < 6; ++i){
		fwrite(pb->buf[i], 1, pb->count[i], fpres);
	}
	fclose(fpres);
}
