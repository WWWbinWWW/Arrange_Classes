#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNODE 20
typedef struct {
	int vertex;//存储data
	int indegree;//存储入度
	int S;//判断是否已输出，初始化1为未输出
}VerNode;
typedef struct {
	int adj;
}Arc;
typedef struct {
	VerNode vexs[MAXNODE];
	Arc arcs[MAXNODE][MAXNODE];
	int m_NumOfVexs;
}Graph;

int MFind(int aim, VerNode* arry)
{
	int pos = -1;
	int i = 0;
	for (i = 0;i < MAXNODE; i++)
	{
		if (aim == arry[i].vertex)
		{
			pos = i;
			return pos;
		}
	}
	return pos;
}

int FindVex(Graph G, int ch)
{
	int F = -1;
	for (int i = 0;i < G.m_NumOfVexs+1;i++)
	{
		if (ch == G.vexs[i].vertex)
		{
			F = i;
			break;
		}
	}
	return F;
}
void showGraph(Graph G, int num)
{
	int i = 0;
	int j = 0;
	printf("\n NODES:\n");
	for (i = 0;i < num; i++)
	{
		printf(" %d", G.vexs[i].vertex);//输出各顶点数据
	}
	printf("\n ARCS:\n");
	for (i = 0;i < num; i++)
	{
		for (j = 0;j < num; j++)
		{
			printf(" %d", G.arcs[i][j].adj);//输出邻接矩阵
		}
		printf("\n");
	}
}
//添加顶点
void addVexs(Graph* G, int vex)
{
	G->m_NumOfVexs++;
	G->vexs[G->m_NumOfVexs].vertex = vex;
	G->vexs[G->m_NumOfVexs].S = 1;
	G->vexs[G->m_NumOfVexs].indegree = 0;
}
//添加边
void addArcs(Graph* G, int Start, int End)
{
	int px = MFind(Start, G->vexs);//找起始边
	int py = MFind(End, G->vexs);//找结束边
	G->arcs[px][py].adj = 1;//边关系赋值为1
}

void InitGraph(Graph* G)
{
	int i = 0;
	int j = 0;
	G->m_NumOfVexs = -1;
	for (i = 0; i < MAXNODE; i++)
	{
		for (j = 0; j < MAXNODE; j++)
			G->arcs[i][j].adj = 0;
	}
}

int GetInDegree(int i, Graph* G)
{
	int InDegree = 0;
	int j = 0;
	for (j = 0; j < MAXNODE; j++)
		InDegree += G->arcs[i][j].adj;//求入度
	return InDegree;
}

int End(Graph *G)//判断是否全部输出
{
	for (int i = 0;i <= G->m_NumOfVexs;i++)
	{
		if (G->vexs[i].S == 1)
			return 1;
	}
	return 0;
}

int main()
{
	Graph G;
	InitGraph(&G);
	int ch, ch1;
	int j;
	int p = 1;
	printf("请按顺序输入课程编号：");
	scanf("%d", &ch);
	while (ch != -1)
	{
		addVexs(&G, ch);
		scanf("%d", &ch);
	}
	for (int i = 0;i < G.m_NumOfVexs+1;i++)
	{
		printf("请输入课程%d的先修课程编号：",i+1);
		scanf("%d", &ch1);
		while (ch1 != -1)
		{
			j = FindVex(G, ch1);
			if(j != -1)
				G.arcs[i][j].adj = 1;//增加边
			else
				scanf("%d", &ch1);
		}//构造邻接表
	}
	for (int i = 0;i < G.m_NumOfVexs+1;i++)
		G.vexs[i].indegree = GetInDegree(i,&G);//求各边入度
		printf("第%d批先修的课程如下：\n", p);
		for (int i = 0;i < G.m_NumOfVexs+1;i++)
		{
			if (G.vexs[i].indegree == 0)
			{
				printf("%d_", G.vexs[i].vertex);
				G.vexs[i].S = 0;//标记为已输出
			}
		}
		printf("\n");
		for (int i = 0;i < G.m_NumOfVexs+1;i++)
		{
			if (G.vexs[i].S == 0)
				for (int j = i, m = 0;m < G.m_NumOfVexs + 1;m++)
				{
					if (G.arcs[m][j].adj == 1)
						G.vexs[m].indegree--;
				}
		}//调整课程
		system("pause");
}