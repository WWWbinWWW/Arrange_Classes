#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM	20
typedef struct ArcNode//��ָ��
{
	int vexnum;//��ָ��Ľ�����
	struct ArcNode *next;
}ArcNode;
typedef struct//ͷ���
{
	char data;//�γ̴���
	int indegree;//���
	ArcNode *firstarc;//ָ��ָ��
}VNode,AdjList[MAXNUM];
typedef struct//�ڽӱ���
{
	AdjList vex;//ͷ�������
	int vexnum, arcnum;
}ALGraph;
typedef struct//������Ϊ0�Ŀγ�
{
	ArcNode *base;
	ArcNode *top;
	int stacksize;
}SqStack;

int InitALGraph(ALGraph *A)//����ͼ�ĳ�ʼ��������洢�ռ�
{
	for (int i = 0;i < MAXNUM;i++)
	{
		A->vex[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		A->vex[i].data = '\0';
		A->vex[i].indegree = 0;
		A->vex[i].firstarc->next = NULL;
		A->vex[i].firstarc->vexnum = i;
	}
	A->arcnum = 0;//������ͻ�����ʼ��Ϊ0
	A->vexnum = 0;
	return 1;
}
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
	S.top->vexnum = m1->vexnum;//�洢ͷ������ţ���������γ̴���
	S.top->next = m1->next;//ָ��ͷ����ڽӵĵ�һ����
	return 1;
}
int Pop(SqStack &S,ArcNode *m2)//�γ̳�ջ
{
	if (S.top == S.base)
		return 0;
	else
	{
		m2->vexnum = S.top->vexnum;//�洢�γ�ͷ�����ţ���������γ̴���
		m2->next = S.top->next;//ָ��ͷ���ĵ�һ���ڽӻ�
		S.top--;//topָ������һλ��ָ�򶥲�Ԫ��
		return 1;
	}
}
int EmptyStack(SqStack S)//ջ���п�
{
	if (S.top == S.base)
		return 1;
	else
		return 0;
}
int LocateVex(ALGraph *A, char ch)//ͨ���γ̴��Ŷ�λ��Ӧͷ������
{
	int i;
	for (i = 0;i < A->vexnum;i++)
	{
		if (ch == A->vex[i].data)
			break;
	}
	return i;//������ڷ��ض�����ţ����򷵻ض�����Ŀ
}
void GraphDisplay(ALGraph *A)//����ͼ�ڽӱ�����
{
	int i;
	ArcNode *p;
	printf("*************************************************\n");
	printf("����ͼ���ڽӱ����£�\n");
	printf("����ͼ�Ļ���Ϊ��%d\n����ͼ���£�\n",A->arcnum);
	for (i = 0;i < A->vexnum;i++)
	{
		printf("�ڽӱ�ͷ���%c:", A->vex[i].data);
		p = A->vex[i].firstarc->next;
		while (p != NULL)
		{
			printf("%c-", A->vex[p->vexnum].data);
			p = p->next;
		}
		printf("*****��ͷ�������Ϊ%d\n",A->vex[i].indegree);
	}
}
int CreateALGraph(ALGraph *A)//�����ڽӱ��ͷ����
{
	printf("������γ���Ŀ��");
	scanf("%d", &A->vexnum);
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("�������%d�ſγ̴��ţ�", i + 1);
		getchar();
		A->vex[i].data = getchar();//��ſγ̴���
		A->vex[i].firstarc->vexnum = i;//���ͷ������
	}//for
	return 1;
}
int CreateALGraphList(ALGraph *A)//�����ڽӱ�
{
	char ch;
	int T;//T��Ϊ��λ���޿γ���ŵı���
	printf("*************************************************\n");
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("�������%d�ſγ̵����޿γ̴��ţ�*��Ϊ����������", i + 1);
		getchar();
		while ((ch = getchar()) != '*')
		{
			A->arcnum++;//����ͼ������+1
			A->vex[i].indegree++;//���+1
			T = LocateVex(A, ch);//�ҵ����޵Ŀγ��������е����
			ArcNode *p, *q;
			p = (ArcNode*)malloc(sizeof(ArcNode));//������ָ��
			q = (ArcNode*)malloc(sizeof(ArcNode));//����ָ��
			p->vexnum = i;
			p->next = NULL;
			q = A->vex[T].firstarc;//���޿γ̵��ڽӱ�ͷָ��
			while (q->next != NULL)//�ҵ����޿γ̵��ڽ�����ĩβ
				q = q->next;
			q->next = p;//���޿γ����������ϸý��
		}//while
	}//for
	return 1;
}
int TopSort(ALGraph *A)//����ͼ����������
{
	int count = 1;//count�����ſ�����
	SqStack S;//ջ���ڴ�����Ϊ0��ͷ���
	InitStack(S);
	printf("*************************************************\n");
	while (A->arcnum)//���û����������ж������Ƿ����������ʱʣ�����Ϊ0�ĵ�δ����
	{
		for (int i = 0;i < A->vexnum;i++)
		{
			if (A->vex[i].indegree == 0)//Ѱ�����Ϊ0��ͷ���
			{
				A->vex[i].indegree = -1;//�´�ѡ��ʱ���ý���ų�����
				Push(S, A->vex[i].firstarc);//�����Ϊ0�Ľ��ѹ��ջ��
			}//if
		}//for
		if (EmptyStack(S))//������ͼ�л����ڻ����������Ϊ0�ĵ㣬����ڻ�
		{
			printf("����ͼ�д��ڻ����޷�����\n");
			printf("*************************************************\n");
			return 0;
		}
		printf("��%d����Ҫ�ŵĿγ̣�", count);
		while (!EmptyStack(S))//ջ�ǿգ�ջ��ͷ���ָ�����γ�ջ
		{
			ArcNode *w;
			w = (ArcNode*)malloc(sizeof(ArcNode));
			Pop(S, w);//ͷ����ջ
			printf("%c  ", A->vex[w->vexnum].data);
			while (w->next != NULL)//������ͷ������������ӽ������-1������ͼ��������-1
			{
				w = w->next;
				A->arcnum--;//��������-1
				A->vex[w->vexnum].indegree--;//��Ӧ������-1
			}//while
		}//while
		count++;//�ſ�����+1
		printf("\n");
	}//while
	printf("��%d����Ҫ�ŵĿγ̣�", count);//������ʱ���Ϊ0�Ľ����Ϊ���һ�����
	for (int i = 0;i < A->vexnum;i++)
	{
		if (A->vex[i].indegree == 0)
		{
			printf("%c  ", A->vex[i].data);
			A->vex[i].indegree = -1;
		}
	}
	printf("\n�γ����������\n");
	printf("*************************************************\n");
	return 1;
}

int main()
{
	ALGraph *A;
	A = (ALGraph*)malloc(MAXNUM*sizeof(ALGraph));
	InitALGraph(A);
	CreateALGraph(A);
	CreateALGraphList(A);
	GraphDisplay(A);
	TopSort(A);
	system("pause");
}