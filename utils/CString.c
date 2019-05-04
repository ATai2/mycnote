#include"CString.h"

int mystrlen(char* p)
{
	if (p == NULL)
	{
		return -1;//ʧ�ܣ�
	}
	int length = 0;
	while (*p != '\0')//�ַ�����ֹ����
	{
		length++;//��������
		p++;//ָ�벻����ǰ
	}
	return length;
}

char* mystrcpy(char* dest, const char* source)//const�޶����������޸�
{
	if (dest == NULL || source == NULL)
	{
		return  NULL;//Ϊ��û�б�Ҫ�ɻ���
	}
	char* destbak = dest;
	while (*source != '\0')//һֱ����
	{
		*dest = *source;//��ֵ�ַ�
		source++;
		dest++;//ָ�벻����ǰ���ַ�������ֵ
	}
	*dest = '\0';//��β
	return destbak;//���ص�ַ
}

char* mystrcat(char* dest, const char* source)
{
	if (dest == NULL || source == NULL)
	{
		return NULL;//ʧ��
	}
	else
	{
		char* destbak = dest;//������ַ
		while (*dest != '\0')
		{
			dest++;//ָ����ǰ�ƶ�
		}
		//��β����ʼ����
		while (*source != '\0') //ѭ�������������ַ���
		{
			*dest = *source;//�ַ�����ֵ
			dest++;
			source++;

		}
		*dest = '\0';//��β
		return destbak;

	}



}

char* mystrchr(const char* dest, const char ch)
{
	if (dest == NULL)
	{
		return NULL;
	}

	while (*dest != '\0')
	{
		if (*dest == ch)
		{
			return dest;//�ҵ����ص�ַ
		}
		dest++;
	}
	return  NULL;//����

}

char* mystrstr(const char* const  dest, const char* const findstr)
{
	if (dest == NULL || findstr == NULL)
	{
		return NULL;
	}
	char* destbak = dest;
	char* p = NULL;//�����ҵ��ĵ�ַ
	while (*destbak != '\0')
	{
		int flag = 1;//�ٶ������
		char* findstrbak = findstr;
		char* nowdestbak = destbak;
		while (*findstrbak != '\0')
		{
			if (*nowdestbak != '\0')
			{

				if (*findstrbak != *nowdestbak)//��һ������
				{
					flag = 0;//��ֵΪ0������
				}
				nowdestbak++;
				findstrbak++;

			}
			else
			{
				flag = 0;//���ñ�ʶ
				break;
			}



		}

		if (flag == 1)
		{
			p = destbak;//��ǰλ��
			return p;
		}

		destbak++;
	}


	return NULL;

}





void init(mystring* string)
{
	string->p = NULL;
	string->reallength = 0;//��ʼ���ṹ���ַ���
}
void initwithlength(mystring* string, int length)
{
	//string->p =(char *) malloc(sizeof(char)*length);//�����ڴ�
	string->p = (char*)calloc(length, sizeof(char));//�����ڴ沢����
	string->reallength = length;//����


}
void initwithstring(mystring* string, char* copystring)
{
	int length = strlen(copystring);//��ȡ�ַ�������
	string->p = (char*)calloc(length + 1, sizeof(char));//�����ڴ�
	mystrcpy(string->p, copystring);//�����ַ���
	string->reallength = length + 1;//���ó���

}
void backaddchar(mystring* string, char ch)
{

	if (mystrlen(string->p) + 1 == string->reallength)//��ζ������
	{
		//���·����ڴ�
		string->p = realloc(string->p, string->reallength + 1);
		string->reallength += 1;
		string->p[string->reallength - 2] = ch;
		string->p[string->reallength - 1] = '\0';


	}
	else
	{
		int nowlength = mystrlen(string->p);//�����ǰ����
		string->p[nowlength] = ch;
		string->p[nowlength + 1] = '\0';//�ַ�������

	}

}
void backaddstring(mystring * string, char* str)
{
	int nowmystringlength = mystrlen(string->p);//��ȡ��ǰ����
	int addstringlength = mystrlen(str);//Ҫ���ӵĳ���
	if (nowmystringlength + addstringlength + 1 > string->reallength)//�ж��Ƿ�Խ��
	{
		int needaddlength = nowmystringlength + addstringlength + 1 - (string->reallength);
		//printf("%d", needaddlength);
		string->p = (char*)realloc(string->p, string->reallength + needaddlength);//�����ַ�������
		mystrcat(string->p, str);//�����ַ���
		string->reallength += needaddlength;//���ӳ���

	}
	else
	{
		mystrcat(string->p, str);//�����ַ���



	}



}
void printfstring(mystring * string)
{

	printf("\nstring=%s", string->p);//��ӡ�ַ���

}
void run(mystring * string)
{

	system(string->p);//ִ��ָ��
}

char* findfirstchar(mystring * string, char ch)
{
	char* p = mystrchr(string->p, ch);//����
	return p;


}
char* findfirststring(mystring * string, char* str)
{

	char* pres = mystrstr(string->p, str);
	return pres;//���ص�ַ



}
int deletefirstchar(mystring * string, const char ch)
{

	char* p = mystrchr(string->p, ch);//����
	if (p == NULL)
	{
		return 0;

	}
	else
	{

		char* pnext = p + 1;
		while (*pnext != '\0')
		{
			*p = *pnext; //ɾ��һ���ַ�������ǰ�ƶ�
			p++;
			pnext++;
		}
		*p = '\0';//�ַ���Ҫ�н�β
		return 1;
	}




}
int deletefirststring(mystring * string, char* const str)
{
	char* pres = mystrstr(string->p, str);//����
	if (pres == NULL)
	{
		return 0;

	}
	else
	{
		int length = mystrlen(str);//���ַ�������
		char* pnext = pres + length;//��һ���ַ�
		while (*pnext != '\0')
		{
			*pres = *pnext; //ɾ��һ���ַ�������ǰ�ƶ�
			pres++;
			pnext++;

		}
		*pres = '\0';//�ַ���Ҫ�н�β
		return 1;
	}



}


void addchar(mystring * string, char ch, char* pos)
{
	if (pos == NULL || string == NULL)
	{
		return;
	}
	if (mystrlen(string->p) + 1 == string->reallength)//��ζ������
	{
		//���·����ڴ�
		string->p = realloc(string->p, string->reallength + 1);
		string->reallength += 1;

		int nowlength = mystrlen(string->p);//�����ǰ����
		int movelength = mystrlen(pos);//�������Ҫ�ƶ��ĳ���
		for (int i = nowlength; i > nowlength - movelength; i--)//�ƶ�
		{
			string->p[i] = string->p[i - 1];//��ѯ
		}
		string->p[nowlength - movelength] = ch;//����

		string->p[nowlength + 1] = '\0';//��β

	}
	else
	{
		int nowlength = mystrlen(string->p);//�����ǰ����
		int movelength = mystrlen(pos);//�������Ҫ�ƶ��ĳ���
		for (int i = nowlength; i > nowlength - movelength; i--)//�ƶ�
		{
			string->p[i] = string->p[i - 1];//��ѯ
		}
		string->p[nowlength - movelength] = ch;//����
		string->p[nowlength + 1] = '\0';//��β





	}



}
void addstring(mystring * string, char* str, char* pos)//���������ַ���
{
	if (pos == NULL || string == NULL)
	{
		return;
	}
	int nowmystringlength = mystrlen(string->p);//��ȡ��ǰ����
	int addstringlength = mystrlen(str);//Ҫ���ӵĳ���
	if (nowmystringlength + addstringlength + 1 > string->reallength)//�ж��Ƿ�Խ��
	{
		int needaddlength = nowmystringlength + addstringlength + 1 - (string->reallength);
		//printf("%d", needaddlength);
		string->p = (char*)realloc(string->p, string->reallength + needaddlength);//�����ַ�������
		string->reallength += needaddlength;//���ӳ���

		//���ƶ����ٿ���
		int nowlength = mystrlen(string->p);//�����ǰ����
		int movelength = mystrlen(pos);//�������Ҫ�ƶ��ĳ���
		int insertlength = strlen(str);//Ҫ�������ĳ���

		for (int i = nowlength; i >= nowlength - movelength; i--)
		{
			string->p[i + insertlength] = string->p[i];//�ַ��ƶ�
		}
		for (int j = 0; j < insertlength; j++)
		{
			string->p[nowlength - movelength + j] = str[j];//��ֵ����
		}

	}
	else
	{
		int nowlength = mystrlen(string->p);//�����ǰ����
		int movelength = mystrlen(pos);//�������Ҫ�ƶ��ĳ���
		int insertlength = strlen(str);//Ҫ�������ĳ���
		for (int i = nowlength; i >= nowlength - movelength; i--)
		{
			string->p[i + insertlength] = string->p[i];//�ַ��ƶ�
		}
		for (int j = 0; j < insertlength; j++)
		{
			string->p[nowlength - movelength + j] = str[j];//��ֵ����
		}

		//



	}


}
void  changefirstchar(mystring * string, const char oldchar, const newchar)//�ı��ַ�
{
	char* pstr = string->p;
	while (*pstr != '\0')
	{
		if (*pstr == oldchar)//����
		{
			*pstr = newchar;//��ֵ
			return;
		}
		pstr++;
	}

}
void changefirststring(mystring * string, char* const oldstring, char* const newstring)//�ı��ַ���
{
	char* pfind = findfirststring(string, oldstring);//�ҵ�λ��
	if (pfind != NULL)
	{
		deletefirststring(string, oldstring);//ɾ��
		addstring(string, newstring, pfind);//����
	}


}