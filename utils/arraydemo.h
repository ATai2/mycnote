#include<stdio.h>
#include<stdlib.h>

struct data
{
	int *p;//ָ�뱣���������ʼ��
	int length;//��������ĳ���
	int stat;//0��������1���������С����2����Ӵ�С
	int reallength;//ʵ�ʷ�����ڴ泤��
};
struct findres
{
	int **pp;
	int n;
};
//���ӣ�ɾ�������ң��޸ģ�����,����

void  init(struct data *pdata);//��ʼ��
void  reinit(struct data *pdata);//ʹ��֮�����³�ʼ��
void  addobject(struct data *pdata, int num);//����һ��Ԫ��
void  addobjects(struct data *pdata, int *pnum, int n);//����һ������
void  printfall(struct data *pdata);//��ӡ���е�����
int  * finddata(struct data *pdata, int num);//���ص�һ���ҵ����ݵĵ�ַ
void  sort(struct data *pdata, int obj);//obj=0,��С�󵽣�����ӵ�С
void  change(struct data *pdata, int oldnum, int newnum);//ʵ���޸�
void  deleteone(struct data *pdata, int num);//ɾ����һ���ҵ�������
void  deleteall(struct data *pdata, int num); //ɾ���������ҵ�������


struct findres findadlldata(struct data *pdata, int num);//����һƬ�ڴ棬���������ҵ���Ԫ�ص��׵�ַ
void  insert(struct data *pdata, int num, int insertnum, int headback);//���ݲ���
//1����ǰ����룬0����������







