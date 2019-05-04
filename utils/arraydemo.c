#include"arraydemo.h"
#include "pch.h"
void init(struct data* pdata) //ʹ��֮ǰ��ʼ��
{
	pdata->p = NULL;//��ζ�Ż�û�г�ʼ��
	pdata->length = 0;//����Ϊ0��
	pdata->stat = 0;//��������
	pdata->reallength = 0;//ʵ�ʳ���
}

void  reinit(struct data* pdata)//ʹ��֮��
{
	if (pdata->p == NULL)
	{
		return;
	}
	else
	{
		free(pdata->p);//�ͷ��ڴ�
		pdata->p = NULL;//��ζ�Ż�û�г�ʼ��
		pdata->length = 0;//����Ϊ0��
		pdata->stat = 0;//��������
		pdata->reallength = 0;//ʵ�ʳ���
	}

}

//����һ������
void  addobject(struct data* pdata, int num)
{
	if (pdata->p == NULL)
	{
		pdata->p = (int*)malloc(sizeof(int));//����һ��Ԫ��
		pdata->length = 1;//�����ʶ����һ��Ԫ��
		pdata->reallength = 1;//ʵ�ʳ���
		pdata->p[pdata->length - 1] = num;//��ֵ
	}
	else
	{
		if (pdata->length == pdata->reallength)
		{
			pdata->p = (int*)realloc(pdata->p, (pdata->length + 1) * sizeof(int));
			pdata->length += 1;//�����ʶ����һ��Ԫ��
			pdata->reallength += 1;//ʵ�ʳ���
			pdata->p[pdata->length - 1] = num;//��ֵ
		}
		else
		{
			pdata->length += 1;//�����ʶ����һ��Ԫ��
			pdata->p[pdata->length - 1] = num;//��ֵ
		}
	}
}
//����һ������
void  addobjects(struct data* pdata, int* pnum, int n) //������Ϊ�����˻�Ϊָ��
{
	if (pdata->p == NULL)
	{
		pdata->p = (int*)malloc(sizeof(int) * n);//����N��Ԫ��
		pdata->length = n;//�����ʶ����n��Ԫ��
		pdata->reallength = n;//ʵ�ʳ���
		for (int i = 0; i < n; i++)
		{
			pdata->p[i] = pnum[i];//��������
		}
	}
	else
	{
		if (pdata->length + n <= pdata->reallength)
		{
			for (int i = 0; i < n; i++)
			{
				pdata->p[i + pdata->length] = pnum[i];//��������
			}
			pdata->length += n;//�����ʶ����n��Ԫ��
		}
		else
		{
			pdata->p = (int*)realloc(pdata->p, (pdata->length + n) * sizeof(int));//���·����ڴ�

			for (int i = 0; i < n; i++)
			{
				pdata->p[i + pdata->length] = pnum[i];//��������
			}
			pdata->length += n;//�����ʶ����n��Ԫ��
			pdata->reallength += n;//���ӳ���
		}
	}
}


void  printfall(struct data* pdata) //��ӡ���е�����
{
	for (int i = 0; i < pdata->length; i++)
	{
		printf("%d\n", pdata->p[i]);//���һ������
	}
}
void  sort(struct data* pdata, int obj)//obj=0,��С�󵽣������da��С
{
	if (obj == 0)
	{
		for (int i = 0; i < pdata->length - 1; i++)
		{
			for (int j = 0; j < pdata->length - i - 1; j++)
			{
				if (pdata->p[j] > pdata->p[j + 1])// j >j+1  
				{
					int temp = pdata->p[j]; //��������
					pdata->p[j] = pdata->p[j + 1];
					pdata->p[j + 1] = temp;
				}
			}
		}
		pdata->stat = 1;//�����С����
	}
	else
	{
		for (int i = 0; i < pdata->length - 1; i++)
		{
			for (int j = 0; j < pdata->length - i - 1; j++)//ð��ûѭ��һ�Σ�����һ����ֵ
			{
				if (pdata->p[j] < pdata->p[j + 1])// j <j+1  
				{
					//int temp = pdata->p[j]; //��������
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
		pdata->stat = 2;//����Ӵ�С
	}
}


int* finddata(struct data* pdata, int num)
{

	if (pdata->stat == 0)
	{
		for (int i = 0; i < pdata->length; i++)//˳��ѭ��
		{
			printf("���ҵ�%d��\n", i);
			if (num == pdata->p[i])//�ж��Ƿ����
			{
				return  &pdata->p[i];//����һ����ַ
				break;//����ѭ��
			}
		}
		return NULL;
	}
	else if (pdata->stat == 1) //���ֲ��ҷ�//��С��da
	{
		int  shang = 0;//shang
		int xia = pdata->length - 1;//��
		while (shang <= xia)//ѭ����ֹ����, 
		{
			int zhong = (shang + xia) / 2;
			printf("%d,%d,%d\n", shang, zhong, xia);
			if (pdata->p[zhong] == num)
			{
				return  &pdata->p[zhong];//���ص�ַ
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
		int xia = pdata->length - 1;//��

		while (shang <= xia)//ѭ����ֹ����, 
		{
			int zhong = (shang + xia) / 2;
			printf("%d,%d,%d\n", shang, zhong, xia);
			if (pdata->p[zhong] == num)
			{
				return  &pdata->p[zhong];//���ص�ַ
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
void  change(struct data* pdata, int oldnum, int newnum)//ʵ���޸�
{

	int* p = finddata(pdata, oldnum);
	if (p == NULL)
	{
		printf("�޸�ʧ�ܣ�û���ҵ�");
		return;
	}
	else
	{
		*p = newnum;//�޸�����
	}

}
////1����ǰ����룬0����������
void  insert(struct data* pdata, int num, int insertnum, int headback)//���ݲ���
{
	int* p = finddata(pdata, num);//��������
	if (p == NULL)
	{
		return NULL;//û���ҵ�
	}
	else
	{
		//�ҵ�,ǰ����� ������������
		if (headback == 1)
		{

			if (pdata->length < pdata->reallength)//����Ҫ����
			{
				int  curr = p - pdata->p;//��ȡҪ����λ�õ��±�
				for (int i = pdata->length - 1; i >= curr; i--)
				{
					pdata->p[i + 1] = pdata->p[i];//�Ӻ���ǰ�ƶ�
				}
				pdata->p[curr] = insertnum;//ʵ�ֲ��룬ǰ�����
				pdata->length++;//���ȼ�1
			}
			else
			{
				int  curr = p - pdata->p;//��ȡҪ����λ�õ��±�
				pdata->p = (int*)realloc(pdata->p, (pdata->length + 1) * sizeof(int));//���ӷ����ڴ�
				pdata->reallength++;//ʵ�ʳ���+1��
				for (int i = pdata->length - 1; i >= curr; i--)
				{
					pdata->p[i + 1] = pdata->p[i];//�Ӻ���ǰ�ƶ�
				}
				pdata->p[curr] = insertnum;//ʵ�ֲ��룬ǰ�����
				pdata->length++;//���ȼ�1
			}
		}
		else
		{

			if (pdata->length < pdata->reallength)//����Ҫ����
			{
				int  curr = p - pdata->p;//��ȡҪ����λ�õ��±�

				for (int i = pdata->length - 1; i > curr; i--)//ʵ���ƶ�
				{
					pdata->p[i + 1] = pdata->p[i];//�Ӻ���ǰ�ƶ�
				}
				pdata->p[curr + 1] = insertnum;//ʵ�ֲ��룬hou����
				pdata->length++;//���ȼ�1
			}
			else
			{
				int  curr = p - pdata->p;//��ȡҪ����λ�õ��±�
				pdata->p = (int*)realloc(pdata->p, (pdata->length + 1) * sizeof(int));//���ӷ����ڴ�
				pdata->reallength++;//ʵ�ʳ���+1��

				for (int i = pdata->length - 1; i > curr; i--)//ʵ���ƶ�
				{
					pdata->p[i + 1] = pdata->p[i];//�Ӻ���ǰ�ƶ�
				}
				pdata->p[curr + 1] = insertnum;//ʵ�ֲ��룬hou����
				pdata->length++;//���ȼ�1
			}
		}
	}
}

//ɾ��
void  deleteone(struct data* pdata, int num)
{

	int* p = finddata(pdata, num);//��������
	if (p == NULL)
	{
		return NULL;//û���ҵ�,ɾ����
	}
	else
	{
		int  curr = p - pdata->p;//cur����Ҫɾ�����±�
		//printf("\n%d,%p", *p, p);
		//printf("\n%d,%p", pdata->p[curr], &pdata->p[curr]);//�������
		for (int i = curr; i < pdata->length - 1; i++)
		{
			pdata->p[i] = pdata->p[i + 1];//�Ӻ���ǰ�ƶ�
		}
		pdata->length -= 1;//����Ԫ�ؼ�ȥ1
	}
}

//ɾ��ȫ��
void  deleteall(struct data* pdata, int num) //ɾ���������ҵ�������
{
	for (int* p = finddata(pdata, num); p != NULL; p = finddata(pdata, num))
	{
		int  curr = p - pdata->p;//cur����Ҫɾ�����±�
		//printf("\n%d,%p", *p, p);
		//printf("\n%d,%p", pdata->p[curr], &pdata->p[curr]);//�������
		for (int i = curr; i < pdata->length - 1; i++)
		{
			pdata->p[i] = pdata->p[i + 1];//�Ӻ���ǰ�ƶ�
		}
		pdata->length -= 1;//����Ԫ�ؼ�ȥ1
	}
}
int* find(int* p, int num, int n)//��һ����ַ��ʼ��N����Χ֮���ҵ�
{
	for (int i = 0; i < n; i++)//ѭ��
	{
		if (p[i] == num)//�ж�
		{

			return p + i;//�����ҵ��ĵ�ַ
			break;
		}
	}
	return NULL;//����û���ҵ�
}

struct findres findadlldata(struct data* pdata, int num)
{
	struct findres  res1;//�����ṹ�����

	int i = 0; //ͳ���ҵ����ٸ���
	for (int* p = find(pdata->p, num, pdata->length - 1); p != NULL; p = find(p + 1, num, (pdata->length - 1) - (p - pdata->p)))
	{
		i++;
	}
	res1.n = i;//����
	int** pint = (int*)malloc(sizeof(int*) * i);//ָ������
	res1.pp = pint;
	for (int* p = find(pdata->p, num, pdata->length - 1), j = 0; p != NULL; j++, p = find(p + 1, num, (pdata->length - 1) - (p - pdata->p)))
	{
		pint[j] = p;//ѭ����ֵ
		//printf("\n%p,%d\n", pint[j], *pint[j]);
	}
	return res1;
}

void testUtils() {
	printf("test just test");
}
