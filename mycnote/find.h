#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>

#include <Windows.h>

//�ҳ�һ��
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
	*offset = p - poff;	//����ƫ����
	return pdest - dest + 1;	//���س��ȣ�����������

}


//��������
int seek(char* dest, char* scr, char *fbuf, int *res_lenght)
{
	assert(dest && scr);
	int l = strlen(dest);
	int k = ((*dest)&(0x80)) ? 10 : 0;
	int offsetlen = 0;
	char *tail = fbuf;		//��¼����˶�Զ
	//i = 0;	//�����������
	while (*(scr + l)){
		if (memcmp(dest, scr, l)){

		}
		else{
			*res_lenght += findline(tail, scr, &offsetlen);	//ȡ�����ҵ���λ�õ���һ��
			tail = fbuf + *res_lenght;
			scr += k + offsetlen;
		}
		scr++;
	}
	return *res_lenght;
}

//���̲߳���
//���̲߳����ṹ��
typedef struct MyStruct ST;
struct MyStruct
{
	char *key;	//������Ŀ��
	char *source;	//�����ҵ���Դ
	int *result;	//�����Ƿ���ɽ��ָ��
	int *res_len;	//���ҵ����ַ�������ܵĳ���
	char *res_out_buf;	//������������
};

void ProcessSeek(void *seg)
{
	ST *st = (ST*)seg;
	if (seek(st->key, st->source, st->res_out_buf, st->res_len)){
		*(st->result) = 10;	//���ҵ��ˣ��޸�Ϊ10������������ж�6�����������λ��10λ�Ƿ�Ϊ6�ж��Ƿ����
	}
	else{
		*(st->result) = 1;	//û�в鵽����1�������ж�6������Ƿ����10���ж��Ƿ�鵽
	}
	//������û�в鵽��ֻҪ�����ˣ��Ͳ���0
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
