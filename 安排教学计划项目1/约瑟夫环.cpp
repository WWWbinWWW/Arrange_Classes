#include<stdio.h>
#include<stdlib.h>
#define N 100
typedef struct LNode	/* 结点类型定义 */
{
	int data;//存储密码
	int num;//存储位序
	struct LNode *next;
}LNode, *LinkList;

void CreateLinkList(LinkList &L, int n, int M[])//m[]用于传递每个人的密码，n为游戏人数,尾插法建立单循环链表
{
	L = new LNode;
	L->next = L;
	struct LNode *r = L;
	for (int i = 0;i < n;i++) {
		struct LNode *p;
		p = new LNode;
		p->num = i + 1;//存储位序
		p->data = M[i];//存储密码
		p->next = L;//新建结点指向头结点
		r->next = p;//连接新建结点
		r = p;//r后移
	}
}

void Yuesefuhuan(LinkList &L, int m,int n)
{
	n = n + 1;//包括头结点
	int k = n;
	struct LNode *p = L,*r;
	printf("*********************\n约瑟夫环出环顺序如下：\n*********************\n");
	while (n > 1) {
		m = m % (n-1);
		if (m == 0)
			m = n-1;
		for (int i = 1;i < m;i++) {
			if (p->next != L)
				p = p->next;
			else
				p = L->next;
		}
		if (p->next != L) {//头结点不参与游戏
			r = p->next;//r指向待删除结点
			p->next = r->next;
		}
		else {
			r = L->next;
			L->next = r->next;
		}
		if (p->next == L)
			p = L;
		printf("第%d位出列者的位序是：%d,其携带的密码为:%d\n", k - n + 1, r->num, r->data);
		m = r->data;//m变为新密码
		delete r;
		n--;
	}
}

void main()
{
	int i,n, m, M[N];
	LinkList L = new LNode;
	printf("请输入游戏人数:");
	scanf("%d", &n);
	printf("*********************\n");
	for (i = 0; i < n;i++) {
		printf("请输入第%d个人的密码:", i + 1);
		scanf("%d", &M[i]);
	}
	printf("*********************\n请输入初始密码:");
	scanf("%d", &m);
	CreateLinkList(L, n, M);
	Yuesefuhuan(L, m, n);
	system("pause");
}