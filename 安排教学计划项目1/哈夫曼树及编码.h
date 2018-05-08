#pragma once
#ifndef _HuffmanTree_
#define _HuffmanTree_
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;
#define max 10000
 // !_HuffmanTree_

//�����������ṹ
struct HTnode {
	char ch;
	int weight, parent, lchild, rchild;
};

//���������ṹ
struct HuffmanTree {
	HTnode* ht;
	int htsize;
};

//�ַ�����
struct HTCode {
	char ch;//�洢�ַ�
	char *cstring;//�ַ���ָ�룬�洢��Ӧ����
};

struct HuffmanCode {
	HTCode *hc;
	int hcsize;
};

void InitHuffmanCode(HuffmanCode &HC, int n)
{
	HC.hc = new HTCode[n];
	HC.hcsize = n;
}

void CreateHuffmanCode(HuffmanCode &HC, HuffmanTree &HT)
{
	int i, j, n, m, start;
	char *cd = new char[HC.hcsize];//���봮����һ��С�ڱ����ַ�����
	cd[HC.hcsize - 1] = '\0';//ĩβ������
	cout << "���ַ��Ĺ���������:" << endl << endl;
	for (i = 0;i < HC.hcsize; i++)
	{
		start = HC.hcsize - 1;
		HC.hc[i].ch = HT.ht[i].ch;//��Ӧ�ַ������ַ���������
		for (n = i,m = HT.ht[i].parent; m != -1;)//��˫�׽�㣬�жϴ˽����˫�׽������ӻ����Һ��ӣ��ظ��˲���������
		{
			if (HT.ht[m].lchild == n)
				cd[--start] = '0';//��Ϊ���ӣ�����0
			else
				cd[--start] = '1';//��Ϊ�Һ��ӣ�����1
			n = m;//n��Ϊ˫�׽�����
			m = HT.ht[m].parent;//m�ٴα�Ϊn��˫�׽�㣬ֱ��n������˫�׽�㣬��������
		}//for
		HC.hc[i].cstring = new char[HC.hcsize - start];//��i���ַ��ı��봮�����ݱ��볤�ȷ���ռ�
		cout << "��" << i + 1 << "���ַ�" << HT.ht[i].ch << "�ı�����:  ";
		for (j = start; j < HC.hcsize; j++)//��start����ʼ����ַ�������
		{
			cout << cd[j];
			HC.hc[i].cstring[j - start] = cd[j];//��ÿ����Ӧ��������ַ��б���
		}//for
		cout << endl;
	}//for
	cout << endl;
	delete[] cd;//�ͷŹ����ռ�
}

//����������ʼ��
void InitHuffmanTree(HuffmanTree &HT, int n)
{
	HT.ht = new HTnode[2 * n - 1];
	HT.htsize = 2 * n - 1;
}

int Min(HuffmanTree &HT, int i)
{
	int j, k, min = max;
	for (j = 0;j < i;j++)
	{
		if (HT.ht[j].parent == -1 && HT.ht[j].weight < min)
		{
			min = HT.ht[j].weight;//Ѱ��Ȩֵ��С��Ҷ�ӽ������
			k = j;
		}//if
	}//for
	HT.ht[k].parent = max;//��ֹ��һ���ٴν���ѡ��
	return k;
}

void Selectmin(HuffmanTree &HT, int i, int &min1, int &min2)
{
	int temp;
	min1 = Min(HT, i);
	min2 = Min(HT, i);
	if (min1 > min2)//min1��Ϊ���ӣ�min2��Ϊ�Һ���
	{
		temp = min1;
		min1 = min2;
		min2 = temp;
	}
}

void CreateHuffmanTree(HuffmanTree &HT, int n, char ch[], int wei[])
{
	int i, m1, m2;
	if (n > 1)
	{
		for (i = 0;i < n;i++)
		{
			HT.ht[i].ch = ch[i];
			HT.ht[i].weight = wei[i];
			HT.ht[i].parent = -1;
			HT.ht[i].lchild = -1;
			HT.ht[i].rchild = -1;
		}
		for (; i < HT.htsize; i++)
		{
			Selectmin(HT, i, m1, m2);
			HT.ht[m1].parent = HT.ht[m2].parent = i;
			HT.ht[i].lchild = m1;//����Ȩֵ��С
			HT.ht[i].rchild = m2;//�Һ���Ȩֵ�ϴ�
			HT.ht[i].weight = HT.ht[m1].weight + HT.ht[m2].weight;
			HT.ht[i].parent = -1;
			HT.ht[i].ch = ' ';
		}
	}
	else
	{
		printf("Ҷ�ӽڵ��������٣��޷��������������");
	}
	printf("���������ɹ�������");
}

void Display(HuffmanTree HT)
{
	int i;
	cout << "��������̬��������:" << endl << endl;
	cout << "�±�λ��" << "  �ַ�  " << " Ȩֵ " << " ���� " << " �Һ��� "
		<< " ˫�� " << endl;
	for (i = 0;i < HT.htsize;i++)
	{
		cout << setw(6) << i << setw(6) << HT.ht[i].ch
			<< setw(8) << HT.ht[i].weight << setw(9) << HT.ht[i].lchild
			<< setw(8) << HT.ht[i].rchild << setw(6) << HT.ht[i].parent << endl;
	}
	cout << endl;
}

void Coder(HuffmanCode &HC, char ch[])
{
	for (int i = 0;i < strlen(ch);i++)
		for (int j = 0;j < HC.hcsize;j++)
			if (ch[i] == HC.hc[j].ch)//Ѱ�������ַ���ÿ���ַ�������еĶ�Ӧ�ַ�
			{
				for (int k = 0;HC.hc[j].cstring[k];k++)//ֱ��HC.hc[j].cstring[k]Ϊ'\0'���������
				{
					cout << HC.hc[j].cstring[k];//���������Ӧ�ַ��ı���
				}
				break;
			}
	cout << endl;
}

void DeCoder(HuffmanTree &HT)
{
	char ch[256];
	int j = 0, i = 0, m, n, r = HT.htsize - 1;//r���ڶ���������
	cout << "������������Ķ����Ƶ��ģ�" << endl;
	getchar();//��ȡ�ַ���
	while ((ch[j] = getchar()) != '\n')
	{
		j++;
	}
	ch[j] = '\0';//��'\0'��Ϊ������ʶ��
	cout << "��������" << endl;
	n = -1;
	m = r;
	while (i < strlen(ch))
	{
		while (m != -1)
		{
			if (ch[i] == '0')
			{
				n = m;
				m = HT.ht[m].lchild;//��Ϊ���ӽ��
			}
			else
			{
				n = m;
				m = HT.ht[m].rchild;//��Ϊ�Һ��ӽ��
			}
			i++;
		}
		cout << HT.ht[n].ch;
		i--;
		n = -1;
		m = r;//���¿�ʼѰ��
	}
	cout << endl;
}

#endif