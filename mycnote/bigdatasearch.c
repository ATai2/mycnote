#define _CRT_SECURE_NO_WARNINGS     //�رհ�ȫ���
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <string.h>

#include <Windows.h>
#include <process.h>
#include "find.h"

//----------------------------------------��������ʼ------------------------------------------------
int mainBigSearch()
{
	//----------------------------------------��ȡ�ļ�------------------------------------------------
	FILE* fp = fopen("res.txt", "r");
	FILE* resFile = fopen("result.txt", "w");
	if (!fp) {
		puts("�ļ���ʧ�ܣ���������˳�����...");
		getchar();
		return -1;	//main�˳�
	}

	char* ft[6] = { NULL };	//��������ͷָ������
	char* pft = NULL;	//���ݶ�ȡ�α�ָ��

	puts("��ʼ����ѯϵͳ����...");
	//��ȡ����
	for (int i = 0; i < 6; ++i) {
		//�����ڴ汣���ȡ����
		ft[i] = (char*)malloc(1024 * 1024 * 200 + 3);
		//�ж�����ɹ���
		if (!ft[i]) {
			puts("�����ڴ�ʧ�ܣ���������˳�����...");
			//getchar();
			return -1;	//main�˳�
		}

		//��ȡ���ݿ�ʼ
		{
			pft = ft[i];
			*pft++ = '\n';
			if (i < 5) {
				//��ȡ����
				for (int i = 0; i < 50; ++i) {
					fread(pft, 1, 4 * 1024 * 1024, fp);
					//ferror(fp);	//�ж϶�ȡ״̬
					pft += 4 * 1024 * 1024;
				}

			}
			else {
				while (!feof(fp)) {		//���200M�����ر����
					fread(pft, 1, 4 * 1024 * 1024, fp);
					pft += 4 * 1024 * 1024;
				}
			}

			*pft++ = '\n';	//��ӽ�β��־
			*pft = '\0';	//��ӽ�����־

		}//��ȡ���ݽ���

	}//end for i=0-6

	fclose(fp);//��ȡ���ر��ļ�
//------------------------------------��ʼ����Ҫ����-----------------------------------------------------------

	char m[120] = "����";

	//puts("����������ҵ�����");
	//scanf("%s", m);

	int res[6] = { 0 };		//�����߳�״̬�Ͳ�ѯ���
	int res_len[6] = { 0 };	//������������
	char* out_buf[6] = { NULL };	//�ļ�����


	for (int i = 0; i < 6; ++i) {
		out_buf[i] = (char*)malloc(1024 * 1024 * 10);//����10M�Ļ���
	}
	   
	//�������߳�
	ST st[6];
	for (int i = 0; i < 6; ++i) {
		st[i].key = m;			//����ѯ�Ĺؼ���
		st[i].source = ft[i];	//��ȡ��Դ
		st[i].result = res + i;		//�����ѯ���
		st[i].res_len = res_len + i;	//����������
		st[i].res_out_buf = out_buf[i];		//��ѯ�������
	}

	int whether = 1;	//�Ƿ�������ҵ��ж�

	int starttime = 0;	//��ʱ��ʼ����
	int endtime = 0;	//��ʱ��������

	while (1) {	//ѭ�����ҿ�ʼ

		puts("������Ҫ���ҵĹؼ��֣�");
		scanf("%s", m);
		starttime = GetTickCount();
		//��ʼ���̲߳������������̲߳���
		for (int i = 0; i < 6; ++i) {
			res[i] = 0;	//�����ʼ��Ϊ0����Ȼ��Ӱ����һ�ζ�ȡ
			res_len[i] = 0;		//�����ʼ��Ϊ0����Ȼ����ͬ������һ�ν��
			_beginthread(ProcessSeek, 0, st + i);	//�������̲߳���
		}
		//--------------------------------�жϲ��ҽ��-----------------------------------------------
		int finish = 0;		//�ж��Ƿ��������
		while (1) {
			Sleep(10);		//ÿ10ms���һ��
			//�ȼ����������Ƿ񶼽����˲���
			finish = res[0] + res[1] + res[2] + res[3] + res[4] + res[5];
			if (finish == 6) {
				//���ҽ�����û�н��
				endtime = GetTickCount();	//��ȡ���ҽ���ʱ��

				puts("��Ҫ��Ķ���ȥ���Ǵ�����");	//�����̶߳���������û���ҵ�
				break;	//�˳�while����߳�
			}

			if ((finish % 10 + finish / 10) == 6) {
				//�ϲ�����Ľ���ļ�����ɾ����ʱ�ļ�
				{
					//���������ļ�
					O_F outf;
					for (int i = 0; i < 6; ++i) {
						outf.buf[i] = st[i].res_out_buf;
						outf.count[i] = res_len[i];
					}
					_beginthread(Out_res, 0, &outf);

				}
				endtime = GetTickCount();	//��ȡ���ҽ���ʱ��
				break;	//�����̶߳�������
			}//end if
		}//end �߳̽������
		//�������ʱ��
		printf("\n\n����ʱ��=%d\n\n", endtime - starttime);
		//�����̶߳������ˣ������ѵ���ʱ��,������
		if (((finish % 10 + finish / 10) == 6) && (finish > 10)) {
			//�򿪱������ļ�
			system("more res.txt");		//���ü��±��򿪣���ѯ������ܴܺ󣨿ɴ�100M��
			system("explorer .");	//���ļ������ļ��У��Լ�ѡ��򿪷�ʽ
		}
		//-----------------------------------------������һ�β���-------------------------------------------
		puts("\n\n�Ƿ������ѯ��������?\n<�����������룺1 / �������룺0 >");
		scanf("%d", &whether);
		if (whether == 0) {
			break;
		}
	}// end while(1)
//-------------------------------����ǰ�ͷ��ڴ�--------------------------------------------
	getchar();
	getchar();
	for (int i = 0; i < 6; ++i) {
		free(ft[i]);
		free(st[i].res_out_buf);
	}
	return 0;
}
