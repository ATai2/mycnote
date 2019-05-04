#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//字符串封装，需要库函数
//不需要库函数
struct CString
{
	char* p;//保存字符串首地址
	int reallength;//实际长度
};
typedef struct CString  mystring;//简写

//字符串，初始化，打印，
//查找，查找字符，查找字符串
//尾部增加，（字符，字符串）
//删除（字符，字符串），
//任意位置增加（字符，字符串）


////修改字符串，（字符，字符串替换）

void init(mystring* string);//原封不动初始化
void initwithlength(mystring* string, int length);//开辟长度，内存清零
void initwithstring(mystring* string, char* copystring);//初始化并拷贝字符串
void printfstring(mystring* string); //打印
void backaddchar(mystring* string, char ch);//增加字符
void backaddstring(mystring* string, char* str);//增加字符串
void run(mystring* string);//执行指令
char* findfirstchar(mystring* string, char ch);//返回第一个找到的字符的地址
char* findfirststring(mystring* string, char* str);//返回第一个找到的字符串的地址
int deletefirstchar(mystring* string, const char ch);//删除第一个找到的字符
int deletefirststring(mystring* string, char* const str);//删除第一个找到的字符串
void addchar(mystring* string, char ch, char* pos);//任意增加字符
void addstring(mystring* string, char* str, char* pos);//任意增加字符串
void  changefirstchar(mystring* string, const char oldchar, const char newchar);//改变字符
void changefirststring(mystring* string, char* const oldstring, char* const newstring);//改变字符串