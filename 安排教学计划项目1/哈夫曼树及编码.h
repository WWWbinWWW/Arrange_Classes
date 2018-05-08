#pragma once
#ifndef _HuffmanTree_
#define _HuffmanTree_
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;
#define max 10000
 // !_HuffmanTree_

//哈夫曼树结点结构
struct HTnode {
	char ch;
	int weight, parent, lchild, rchild;
};

//哈夫曼树结构
struct HuffmanTree {
	HTnode* ht;
	int htsize;
};

//字符编码
struct HTCode {
	char ch;//存储字符
	char *cstring;//字符串指针，存储对应编码
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
	char *cd = new char[HC.hcsize];//编码串长度一定小于编码字符数量
	cd[HC.hcsize - 1] = '\0';//末尾结束符
	cout << "各字符的哈夫曼编码:" << endl << endl;
	for (i = 0;i < HC.hcsize; i++)
	{
		start = HC.hcsize - 1;
		HC.hc[i].ch = HT.ht[i].ch;//对应字符存入字符编码数组
		for (n = i,m = HT.ht[i].parent; m != -1;)//找双亲结点，判断此结点是双亲结点的左孩子还是右孩子，重复此操作到树顶
		{
			if (HT.ht[m].lchild == n)
				cd[--start] = '0';//若为左孩子，编码0
			else
				cd[--start] = '1';//若为右孩子，编码1
			n = m;//n变为双亲结点序号
			m = HT.ht[m].parent;//m再次变为n的双亲结点，直到n不存在双亲结点，到达树顶
		}//for
		HC.hc[i].cstring = new char[HC.hcsize - start];//第i个字符的编码串，根据编码长度分配空间
		cout << "第" << i + 1 << "个字符" << HT.ht[i].ch << "的编码是:  ";
		for (j = start; j < HC.hcsize; j++)//从start处开始输出字符到结束
		{
			cout << cd[j];
			HC.hc[i].cstring[j - start] = cd[j];//将每个对应编码存入字符中编码
		}//for
		cout << endl;
	}//for
	cout << endl;
	delete[] cd;//释放工作空间
}

//哈夫曼树初始化
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
			min = HT.ht[j].weight;//寻找权值最小的叶子结点的序号
			k = j;
		}//if
	}//for
	HT.ht[k].parent = max;//防止下一次再次进入选择
	return k;
}

void Selectmin(HuffmanTree &HT, int i, int &min1, int &min2)
{
	int temp;
	min1 = Min(HT, i);
	min2 = Min(HT, i);
	if (min1 > min2)//min1作为左孩子，min2作为右孩子
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
			HT.ht[i].lchild = m1;//左孩子权值较小
			HT.ht[i].rchild = m2;//右孩子权值较大
			HT.ht[i].weight = HT.ht[m1].weight + HT.ht[m2].weight;
			HT.ht[i].parent = -1;
			HT.ht[i].ch = ' ';
		}
	}
	else
	{
		printf("叶子节点数量过少，无法建造哈夫曼树！");
	}
	printf("哈夫曼树成功创建！");
}

void Display(HuffmanTree HT)
{
	int i;
	cout << "哈夫曼静态链表如下:" << endl << endl;
	cout << "下标位置" << "  字符  " << " 权值 " << " 左孩子 " << " 右孩子 "
		<< " 双亲 " << endl;
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
			if (ch[i] == HC.hc[j].ch)//寻找输入字符串每个字符与编码中的对应字符
			{
				for (int k = 0;HC.hc[j].cstring[k];k++)//直到HC.hc[j].cstring[k]为'\0'，结束输出
				{
					cout << HC.hc[j].cstring[k];//依次输出对应字符的编码
				}
				break;
			}
	cout << endl;
}

void DeCoder(HuffmanTree &HT)
{
	char ch[256];
	int j = 0, i = 0, m, n, r = HT.htsize - 1;//r等于顶部结点序号
	cout << "请输入需译码的二进制电文：" << endl;
	getchar();//读取字符串
	while ((ch[j] = getchar()) != '\n')
	{
		j++;
	}
	ch[j] = '\0';//以'\0'作为结束标识符
	cout << "译码结果：" << endl;
	n = -1;
	m = r;
	while (i < strlen(ch))
	{
		while (m != -1)
		{
			if (ch[i] == '0')
			{
				n = m;
				m = HT.ht[m].lchild;//变为左孩子结点
			}
			else
			{
				n = m;
				m = HT.ht[m].rchild;//变为右孩子结点
			}
			i++;
		}
		cout << HT.ht[n].ch;
		i--;
		n = -1;
		m = r;//重新开始寻找
	}
	cout << endl;
}

#endif