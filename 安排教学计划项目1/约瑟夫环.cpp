#include<stdio.h>
#include<stdlib.h>
#define N 100
typedef struct LNode	/* ������Ͷ��� */
{
	int data;//�洢����
	int num;//�洢λ��
	struct LNode *next;
}LNode, *LinkList;

void CreateLinkList(LinkList &L, int n, int M[])//m[]���ڴ���ÿ���˵����룬nΪ��Ϸ����,β�巨������ѭ������
{
	L = new LNode;
	L->next = L;
	struct LNode *r = L;
	for (int i = 0;i < n;i++) {
		struct LNode *p;
		p = new LNode;
		p->num = i + 1;//�洢λ��
		p->data = M[i];//�洢����
		p->next = L;//�½����ָ��ͷ���
		r->next = p;//�����½����
		r = p;//r����
	}
}

void Yuesefuhuan(LinkList &L, int m,int n)
{
	n = n + 1;//����ͷ���
	int k = n;
	struct LNode *p = L,*r;
	printf("*********************\nԼɪ�򻷳���˳�����£�\n*********************\n");
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
		if (p->next != L) {//ͷ��㲻������Ϸ
			r = p->next;//rָ���ɾ�����
			p->next = r->next;
		}
		else {
			r = L->next;
			L->next = r->next;
		}
		if (p->next == L)
			p = L;
		printf("��%dλ�����ߵ�λ���ǣ�%d,��Я��������Ϊ:%d\n", k - n + 1, r->num, r->data);
		m = r->data;//m��Ϊ������
		delete r;
		n--;
	}
}

void main()
{
	int i,n, m, M[N];
	LinkList L = new LNode;
	printf("��������Ϸ����:");
	scanf("%d", &n);
	printf("*********************\n");
	for (i = 0; i < n;i++) {
		printf("�������%d���˵�����:", i + 1);
		scanf("%d", &M[i]);
	}
	printf("*********************\n�������ʼ����:");
	scanf("%d", &m);
	CreateLinkList(L, n, M);
	Yuesefuhuan(L, m, n);
	system("pause");
}