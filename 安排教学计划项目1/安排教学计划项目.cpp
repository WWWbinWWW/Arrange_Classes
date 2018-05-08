#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM	20
#define N 20
typedef struct ArcNode//弧指针
{
	int vexnum;
	struct ArcNode *next;
}ArcNode;
typedef struct//头结点
{
	char data;//数据
	int indegree;//入度
	ArcNode *firstarc;//指向弧指针
}VNode,AdjList[MAXNUM];
typedef struct//邻接表定义
{
	AdjList vex;//头结点数组
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
typedef struct//存放入度为0的课程
{
	ArcNode *base;
	ArcNode *top;
	int stacksize;
}SqStack;
int InitStack(SqStack &S)//初始化
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
int Push(SqStack &S,ArcNode *m1)//课程入栈
{
	if (S.top - S.base >= MAXNUM)
		return 0;
	S.top++;
	S.top->next = m1->next;//先链接第一个邻接点
	S.top->vexnum = m1->vexnum;//等于邻接头结点的序号，方便输出课程
	return 1;
}
int Pop(SqStack &S,ArcNode *m2)//课程出栈
{
	if (S.top == S.base)
		return 0;
	else
	{
		m2->vexnum = S.top->vexnum;
		m2->next = S.top->next;
		S.top--;//top指针下移一位，指向顶层元素
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
	return i;//顶点存在返回顶点序号，否则返回顶点数目
}

int VexOver(ALGraph *A)
{
	int flag = 0;
	for (int i = 0;i < A->vexnum;i++)
	{
		if (A->vex[i].indegree >= 0)//存在入度大于等于0的结点则排序未结束
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
	printf("有向图如下：\n");
	for (i = 0;i < A->vexnum;i++)
	{
		printf("%c:", A->vex[i].data);
		p = A->vex[i].firstarc->next;
		while (p != NULL)
		{
			printf("%c-", A->vex[p->vexnum].data);
			p = p->next;
		}
		printf("*****该点入度为%d\n",A->vex[i].indegree);
	}
}

int main()
{
	char ch;
	int T,count=1;//T作为定位先修课程序号的变量，count计算排课批次
	ALGraph *A;
	A = (ALGraph*)malloc(MAXNUM*sizeof(ALGraph));
	SqStack S;
	InitStack(S);
	InitALGraph(A);
	printf("请输入课程数目：");
	scanf("%d", &A->vexnum);
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("请输入第%d门课程代号：", i+1);
		getchar();
		A->vex[i].data = getchar();
		A->vex[i].firstarc->vexnum = i;
	}//for
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("请输入第%d门课程的先修课程代号（*作为结束符）：",i+1);
		getchar();
		while ((ch = getchar()) != '*')
		{
			A->arcnum++;//邻接表的弧数量+1，作为判断是否排序完成的标志
			A->vex[i].indegree++;//入度+1
			T = LocateVex(A, ch);//找到先修的课程在数组中的序号
			ArcNode *p, *q;
			p = (ArcNode*)malloc(sizeof(ArcNode));
			q = (ArcNode*)malloc(sizeof(ArcNode));
			p->vexnum = i;
			p->next = NULL;
			q = A->vex[T].firstarc;
			while (q->next != NULL)
				q = q->next;
			q->next = p;//链接上该结点
		}//while
	}//for
	printf("有向图的邻接表如下：\n");
	GraphDisplay(A);
	while (A->arcnum)//当弧的数量为零时，表示剩下的未排序课程入度都为0，遍历一遍输出即可
	{
		for (int i = 0;i < A->vexnum;i++)
		{
			if (A->vex[i].indegree == 0)
			{
				A->vex[i].indegree = -1;//下次选择时将该结点排除在外
				Push(S, A->vex[i].firstarc);//将入度为0的结点压入栈中
			}//if
		}//for
		if (EmptyStack(S))
		{
			printf("有向图存在环，无法排序。");
			break;
		}
		printf("第%d批需要排的课程：", count);
		while (!EmptyStack(S))//栈非空
		{
			ArcNode *w;
			w = (ArcNode*)malloc(sizeof(ArcNode));
			Pop(S, w);
			printf("%c", A->vex[w->vexnum].data);

			while (w->next != NULL)//遍历该结点的邻接结点
			{
				w = w->next;
				if (A->vex[w->vexnum].indegree <= 0)//该点已经出去，则存在环
				{
					printf("存在环，无法排序");
					return 0;
				}//if
				else
				{
					A->vex[w->vexnum].indegree--;//相应结点入度-1
					A->arcnum--;//每减少一条边，弧的数量-1
				}
			}//while
		}//while
		count++;
		InitStack(S);
		printf("\n");
	}//while
	system("pause");
}