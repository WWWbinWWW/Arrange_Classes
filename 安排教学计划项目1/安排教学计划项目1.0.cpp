#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNUM	20
typedef struct ArcNode//弧指针
{
	int vexnum;//弧指向的结点序号
	struct ArcNode *next;
}ArcNode;
typedef struct//头结点
{
	char data;//课程代号
	int indegree;//入度
	ArcNode *firstarc;//指向弧指针
}VNode,AdjList[MAXNUM];
typedef struct//邻接表定义
{
	AdjList vex;//头结点数组
	int vexnum, arcnum;
}ALGraph;
typedef struct//存放入度为0的课程
{
	ArcNode *base;
	ArcNode *top;
	int stacksize;
}SqStack;

int InitALGraph(ALGraph *A)//有向图的初始化，分配存储空间
{
	for (int i = 0;i < MAXNUM;i++)
	{
		A->vex[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
		A->vex[i].data = '\0';
		A->vex[i].indegree = 0;
		A->vex[i].firstarc->next = NULL;
		A->vex[i].firstarc->vexnum = i;
	}
	A->arcnum = 0;//结点数和弧数初始化为0
	A->vexnum = 0;
	return 1;
}
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
	S.top->vexnum = m1->vexnum;//存储头结点的序号，方便输出课程代号
	S.top->next = m1->next;//指向头结点邻接的第一条弧
	return 1;
}
int Pop(SqStack &S,ArcNode *m2)//课程出栈
{
	if (S.top == S.base)
		return 0;
	else
	{
		m2->vexnum = S.top->vexnum;//存储课程头结点序号，方便输出课程代号
		m2->next = S.top->next;//指向头结点的第一条邻接弧
		S.top--;//top指针下移一位，指向顶层元素
		return 1;
	}
}
int EmptyStack(SqStack S)//栈的判空
{
	if (S.top == S.base)
		return 1;
	else
		return 0;
}
int LocateVex(ALGraph *A, char ch)//通过课程代号定位相应头结点序号
{
	int i;
	for (i = 0;i < A->vexnum;i++)
	{
		if (ch == A->vex[i].data)
			break;
	}
	return i;//顶点存在返回顶点序号，否则返回顶点数目
}
void GraphDisplay(ALGraph *A)//有向图邻接表的输出
{
	int i;
	ArcNode *p;
	printf("*************************************************\n");
	printf("有向图的邻接表如下：\n");
	printf("有向图的弧数为：%d\n有向图如下：\n",A->arcnum);
	for (i = 0;i < A->vexnum;i++)
	{
		printf("邻接表头结点%c:", A->vex[i].data);
		p = A->vex[i].firstarc->next;
		while (p != NULL)
		{
			printf("%c-", A->vex[p->vexnum].data);
			p = p->next;
		}
		printf("*****该头结点的入度为%d\n",A->vex[i].indegree);
	}
}
int CreateALGraph(ALGraph *A)//建立邻接表表头数组
{
	printf("请输入课程数目：");
	scanf("%d", &A->vexnum);
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("请输入第%d门课程代号：", i + 1);
		getchar();
		A->vex[i].data = getchar();//存放课程代号
		A->vex[i].firstarc->vexnum = i;//存放头结点序号
	}//for
	return 1;
}
int CreateALGraphList(ALGraph *A)//建立邻接表
{
	char ch;
	int T;//T作为定位先修课程序号的变量
	printf("*************************************************\n");
	for (int i = 0;i < A->vexnum;i++)
	{
		printf("请输入第%d门课程的先修课程代号（*作为结束符）：", i + 1);
		getchar();
		while ((ch = getchar()) != '*')
		{
			A->arcnum++;//有向图弧数量+1
			A->vex[i].indegree++;//入度+1
			T = LocateVex(A, ch);//找到先修的课程在数组中的序号
			ArcNode *p, *q;
			p = (ArcNode*)malloc(sizeof(ArcNode));//待连接指针
			q = (ArcNode*)malloc(sizeof(ArcNode));//遍历指针
			p->vexnum = i;
			p->next = NULL;
			q = A->vex[T].firstarc;//先修课程的邻接表头指针
			while (q->next != NULL)//找到先修课程的邻接链表末尾
				q = q->next;
			q->next = p;//先修课程链表链接上该结点
		}//while
	}//for
	return 1;
}
int TopSort(ALGraph *A)//有向图的拓扑排序
{
	int count = 1;//count计算排课批次
	SqStack S;//栈用于存放入度为0的头结点
	InitStack(S);
	printf("*************************************************\n");
	while (A->arcnum)//利用弧的数量来判断排序是否结束，结束时剩下入度为0的点未排序
	{
		for (int i = 0;i < A->vexnum;i++)
		{
			if (A->vex[i].indegree == 0)//寻找入度为0的头结点
			{
				A->vex[i].indegree = -1;//下次选择时将该结点排除在外
				Push(S, A->vex[i].firstarc);//将入度为0的结点压入栈中
			}//if
		}//for
		if (EmptyStack(S))//若有向图中还存在弧，且无入度为0的点，则存在环
		{
			printf("有向图中存在环，无法排序。\n");
			printf("*************************************************\n");
			return 0;
		}
		printf("第%d批需要排的课程：", count);
		while (!EmptyStack(S))//栈非空，栈中头结点指针依次出栈
		{
			ArcNode *w;
			w = (ArcNode*)malloc(sizeof(ArcNode));
			Pop(S, w);//头结点出栈
			printf("%c  ", A->vex[w->vexnum].data);
			while (w->next != NULL)//遍历该头结点链表，将链接结点的入度-1，有向图弧的数量-1
			{
				w = w->next;
				A->arcnum--;//弧的数量-1
				A->vex[w->vexnum].indegree--;//相应结点入度-1
			}//while
		}//while
		count++;//排课批次+1
		printf("\n");
	}//while
	printf("第%d批需要排的课程：", count);//将结束时入度为0的结点作为最后一批输出
	for (int i = 0;i < A->vexnum;i++)
	{
		if (A->vex[i].indegree == 0)
		{
			printf("%c  ", A->vex[i].data);
			A->vex[i].indegree = -1;
		}
	}
	printf("\n课程排序已完成\n");
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