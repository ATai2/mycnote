#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//�ַ�����װ����Ҫ�⺯��
//����Ҫ�⺯��
struct CString
{
	char* p;//�����ַ����׵�ַ
	int reallength;//ʵ�ʳ���
};
typedef struct CString  mystring;//��д

//�ַ�������ʼ������ӡ��
//���ң������ַ��������ַ���
//β�����ӣ����ַ����ַ�����
//ɾ�����ַ����ַ�������
//����λ�����ӣ��ַ����ַ�����


////�޸��ַ��������ַ����ַ����滻��

void init(mystring* string);//ԭ�ⲻ����ʼ��
void initwithlength(mystring* string, int length);//���ٳ��ȣ��ڴ�����
void initwithstring(mystring* string, char* copystring);//��ʼ���������ַ���
void printfstring(mystring* string); //��ӡ
void backaddchar(mystring* string, char ch);//�����ַ�
void backaddstring(mystring* string, char* str);//�����ַ���
void run(mystring* string);//ִ��ָ��
char* findfirstchar(mystring* string, char ch);//���ص�һ���ҵ����ַ��ĵ�ַ
char* findfirststring(mystring* string, char* str);//���ص�һ���ҵ����ַ����ĵ�ַ
int deletefirstchar(mystring* string, const char ch);//ɾ����һ���ҵ����ַ�
int deletefirststring(mystring* string, char* const str);//ɾ����һ���ҵ����ַ���
void addchar(mystring* string, char ch, char* pos);//���������ַ�
void addstring(mystring* string, char* str, char* pos);//���������ַ���
void  changefirstchar(mystring* string, const char oldchar, const char newchar);//�ı��ַ�
void changefirststring(mystring* string, char* const oldstring, char* const newstring);//�ı��ַ���