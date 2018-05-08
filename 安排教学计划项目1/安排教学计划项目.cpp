#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM	20
#define N 20
typedef struct ArcNode//��ָ��
{
	int vexnum;
	struct ArcNode *next;
}ArcNode;
typedef struct//ͷ���
{
	char data;//����
	int indegree;//���
	ArcNode *firstarc;//ָ��ָ��
}VNode,AdjList[MAXNUM];
typedef struct//�ڽӱ���
{
	AdjList vex;//ͷ�������
	int vexnum, arcnum;
}ALGraph;

int InitALGraph(ALGraph *A)
{
	for (int i = 0;i < MAXNUM;i++)
	{
		A->vex[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		A->vex[i].data = '\0';
		A->vex[i].indegree = 0;
		A->vex[i].firstarc->next = NULL;
		A->vex[i].firstarc->vexnum = i;
	}
	A->arcnum = 0;
	A->vexnum = 0;
	return 1;
}
typedef struct//������Ϊ0�Ŀγ�
{
	ArcNode *base;
	ArcNode *top;
	int stacksize;
}SqStack;
int InitStack(SqStack &S)//��ʼ��
{
	S.base = (ArcNode*)malloc(MAXNUM * sizeof(ArcNode));
	if (!S.base)
		exit(-1);
	S.base->next = NULL;
	S.base->vexnum = -1;
	S.top = S.base;
	S.stacksize = MAXNUM;
	return 1;
}
int Push(SqStack &S,ArcNode *m1)//�γ���ջ
{
	if (S.top - S.base >= MAXNUM)
		return 0;
	S.top++;
	S.top->next = m1->next;//�����ӵ�һ���ڽӵ�
	S.top->vexnum = m1->vexnum;//�����ڽ�ͷ������ţ���������γ�
	return 1;
}
int Pop(SqStack &S,ArcNode *m2)//�γ̳�ջ
{
	if (S.top == S.base)
		return 0;
	else
	{
		m2->vexnum = S.top->vexnum;
		m2->next = S.top->next;
		S.top--;//topָ������һλ��ָ�򶥲�Ԫ��
		return 1;
	}
}
int EmptyStack(SqStack S)
{
	if (S.top == S.base)
		return 1;
	else
		return 0;
}
int LocateVex(ALGraph *A, char ch)
{
	int i;
	for (i = 0;i < A->vexnum;i++)
	{
		if (ch == A->vex[i].data)
			break;
	}
	return i;//������ڷ��ض�����ţ����򷵻ض�����Ŀ
}

int VexOver(ALGraph *A)
{
	int flag = 0;
	for (int i = 0;i < A->vexnum;i++)
	{
		if (A->vex[i].indegree >= 0)//������ȴ��ڵ���0�Ľ��������δ����
		{
			flag = 1;
			break;
		}
	}
	return flag;
}
void GraphDisplay(ALGraph *A)
{
	int i;
	ArcNode *p;
	printf("����ͼ���£�\n");
	for (i = 0;i < A->vexnum;i++)
	{
		printf("%c:", A->vex[i].data);
		p = A->vex[i].firstarc->next;
		while (p != NULL)
		{
			printf("%c-", A->vex[p->vexnum].data);
			p = p->next;
		}
		printf("*****�õ����Ϊ%d\n",A->vex[i].indegree);
	}
}

int main()
{
	char ch;
	int T,count=1;//T��Ϊ��λ���޿γ���ŵı�����count�����ſ�����
	ALGraph *A;
	A = (ALGraph*)malloc(MAXNUM*sizeof(ALGraph));
	SqStack S;
	InitStack(S);
	InitALGraph(A);
	printf("������γ���Ŀ��");
	scanf("%d", &A->vexnum);
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("�������%d�ſγ̴��ţ�", i+1);
		getchar();
		A->vex[i].data = getchar();
		A->vex[i].firstarc->vexnum = i;
	}//for
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("�������%d�ſγ̵����޿γ̴��ţ�*��Ϊ����������",i+1);
		getchar();
		while ((ch = getchar()) != '*')
		{
			A->arcnum++;//�ڽӱ�Ļ�����+1����Ϊ�ж��Ƿ�������ɵı�־
			A->vex[i].indegree++;//���+1
			T = LocateVex(A, ch);//�ҵ����޵Ŀγ��������е����
			ArcNode *p, *q;
			p = (ArcNode*)malloc(sizeof(ArcNode));
			q = (ArcNode*)malloc(sizeof(ArcNode));
			p->vexnum = i;
			p->next = NULL;
			q = A->vex[T].firstarc;
			while (q->next != NULL)
				q = q->next;
			q->next = p;//�����ϸý��
		}//while
	}//for
	printf("����ͼ���ڽӱ����£�\n");
	GraphDisplay(A);
	while (A->arcnum)//����������Ϊ��ʱ����ʾʣ�µ�δ����γ���ȶ�Ϊ0������һ���������
	{
		for (int i = 0;i < A->vexnum;i++)
		{
			if (A->vex[i].indegree == 0)
			{
				A->vex[i].indegree = -1;//�´�ѡ��ʱ���ý���ų�����
				Push(S, A->vex[i].firstarc);//�����Ϊ0�Ľ��ѹ��ջ��
			}//if
		}//for
		if (EmptyStack(S))
		{
			printf("����ͼ���ڻ����޷�����");
			break;
		}
		printf("��%d����Ҫ�ŵĿγ̣�", count);
		while (!EmptyStack(S))//ջ�ǿ�
		{
			ArcNode *w;
			w = (ArcNode*)malloc(sizeof(ArcNode));
			Pop(S, w);
			printf("%c", A->vex[w->vexnum].data);

			while (w->next != NULL)//�����ý����ڽӽ��
			{
				w = w->next;
				if (A->vex[w->vexnum].indegree <= 0)//�õ��Ѿ���ȥ������ڻ�
				{
					printf("���ڻ����޷�����");
					return 0;
				}//if
				else
				{
					A->vex[w->vexnum].indegree--;//��Ӧ������-1
					A->arcnum--;//ÿ����һ���ߣ���������-1
				}
			}//while
		}//while
		count++;
		InitStack(S);
		printf("\n");
	}//while
	system("pause");
}