#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXNODE 20
typedef struct {
	int vertex;//�洢data
	int indegree;//�洢���
	int S;//�ж��Ƿ����������ʼ��1Ϊδ���
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
		printf(" %d", G.vexs[i].vertex);//�������������
	}
	printf("\n ARCS:\n");
	for (i = 0;i < num; i++)
	{
		for (j = 0;j < num; j++)
		{
			printf(" %d", G.arcs[i][j].adj);//����ڽӾ���
		}
		printf("\n");
	}
}
//��Ӷ���
void addVexs(Graph* G, int vex)
{
	G->m_NumOfVexs++;
	G->vexs[G->m_NumOfVexs].vertex = vex;
	G->vexs[G->m_NumOfVexs].S = 1;
	G->vexs[G->m_NumOfVexs].indegree = 0;
}
//��ӱ�
void addArcs(Graph* G, int Start, int End)
{
	int px = MFind(Start, G->vexs);//����ʼ��
	int py = MFind(End, G->vexs);//�ҽ�����
	G->arcs[px][py].adj = 1;//�߹�ϵ��ֵΪ1
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
		InDegree += G->arcs[i][j].adj;//�����
	return InDegree;
}

int End(Graph *G)//�ж��Ƿ�ȫ�����
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
	printf("�밴˳������γ̱�ţ�");
	scanf("%d", &ch);
	while (ch != -1)
	{
		addVexs(&G, ch);
		scanf("%d", &ch);
	}
	for (int i = 0;i < G.m_NumOfVexs+1;i++)
	{
		printf("������γ�%d�����޿γ̱�ţ�",i+1);
		scanf("%d", &ch1);
		while (ch1 != -1)
		{
			j = FindVex(G, ch1);
			if(j != -1)
				G.arcs[i][j].adj = 1;//���ӱ�
			else
				scanf("%d", &ch1);
		}//�����ڽӱ�
	}
	for (int i = 0;i < G.m_NumOfVexs+1;i++)
		G.vexs[i].indegree = GetInDegree(i,&G);//��������
		printf("��%d�����޵Ŀγ����£�\n", p);
		for (int i = 0;i < G.m_NumOfVexs+1;i++)
		{
			if (G.vexs[i].indegree == 0)
			{
				printf("%d_", G.vexs[i].vertex);
				G.vexs[i].S = 0;//���Ϊ�����
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
		}//�����γ�
		system("pause");
}