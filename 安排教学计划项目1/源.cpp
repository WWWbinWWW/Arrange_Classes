#include<stdio.h>
#include<stdlib.h>
#include<string>
#define N 5//N为停车场容量大小
typedef struct//结构体指针表示每一辆停车场的车的情况
{
	char Numb[6];//车牌号码
	int Time[4];//进入停车场的时间
}Rec;
typedef Rec *RecPointer;

typedef struct//停车场车辆情况
{
	RecPointer base;
	RecPointer top;
	int stacksize;
}SqStack;

int InitStack(SqStack &S)//栈（停车场）的初始化
{
	S.base = (RecPointer)malloc(N * sizeof(Rec));
	if (!S.base)
		exit(-1);
	S.top = S.base;
	S.stacksize = N;
	return 1;
}

int Pop(SqStack &S, char *e, int T[])//出栈（停车场）
{
	if (S.top == S.base)
		return 0;
	else
	{
		S.top--;//top指针下移一位，指向顶层元素
		strcpy(e, S.top->Numb);
		T[0] = S.top->Time[0];
		T[1] = S.top->Time[1];
		T[2] = S.top->Time[2];
		T[3] = S.top->Time[3];
		return 1;
	}
}

int TravelS(SqStack S)//遍历栈（停车场）
{
	RecPointer p;
	int i = 1;
	p = S.base;
	if (S.base == S.top)
		return 0;
	while (p != S.top)
	{
		printf("********************************************\n");
		printf("%d号停车位：已停车，车辆牌照为%s，入场时间为%d年%d月%d日%d点         *\n", i, p->Numb, p->Time[0], p->Time[1], p->Time[2], p->Time[3]);
		i++;
		p++;
	}
	while (i <= N)
	{
		printf("********************************************\n");
		printf("%d号停车位：未停车                          *\n", i);
		i++;
	}
	printf("********************************************\n");
	return 1;
}

int Push(SqStack &S, char *e1, int T1[])//入栈（停车场）
{
	if (S.top - S.base >= N)//停车场满了
		return 0;
	strcpy(S.top->Numb, e1);//车牌号
	S.top->Time[0] = T1[0];//入场时间
	S.top->Time[1] = T1[1];
	S.top->Time[2] = T1[2];
	S.top->Time[3] = T1[3];
	S.top++;
	return 1;
}

typedef struct QNode//队列（便道）定义
{
	char data[5];//储存车牌号
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue *Q)//队列（便道）初始化
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(Q->front))
		exit(1);
	Q->front->next = 0;
}

void EnQueue(LinkQueue *Q, char *e3)//队列（便道）插入操作
{
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
		exit(1);
	strcpy(p->data, e3);
	p->next = 0;
	Q->rear->next = p;
	Q->rear = p;
}

int TravelQ(LinkQueue *Q)//队列（便道）遍历
{
	QNode *p;
	int i = 1;
	if (Q->front == Q->rear)
		return 0;
	p = Q->front->next;
	while (p != Q->rear)
	{
		printf("便道%d号位：已停车，车辆牌照为%s         *\n", i, p->data);
		printf("********************************************\n");
		p = p->next;
		i++;
	}
	printf("便道%d号位：已停车，车辆牌照为%s         *\n", i, p->data);
	printf("********************************************\n");
	return 1;
}

int DeQueue(LinkQueue *Q, char *e4)//出队列（便道）
{
	QNode *p;
	if (Q->front == Q->rear)
		return 0;
	p = Q->front->next;
	strcpy(e4, p->data);
	Q->front->next = p->next;
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return 1;
}

int  DayofYear(int year, int month, int day) {
	int i, mm, days = 0;
	int a[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	/*判断是否为闰年*/
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		mm = 1;
	}
	else
	{
		mm = 0;
	}

	/*如果为闰年，则改变二月份的天数*/
	if (mm == 1)
	{
		a[1] = 29;
	}

	/*因为数组第一个是由0开始，并由month-1个月遍历，所以为month-2*/
	for (i = month - 2;i >= 0;i--)
	{
		days += day;
		days += a[i];
	}
	return days;
}

int Coming_Car(SqStack &S, LinkQueue *Q, char *Num, int Time1[])
{
	if (!(Push(S, Num, Time1)))//停车场满了,进入便道
	{
		Time1[0] = 0;
		Time1[1] = 0;
		Time1[2] = 0;
		Time1[3] = 0;
		EnQueue(Q, Num);
		printf("********************************************\n");
		printf("停车场已满，进入便道                       *\n");
		printf("********************************************\n");
	}
	else
	{
		printf("********************************************\n");
		printf("车牌号为%s的车进入停车场，停在%d号车位，入场时间为%d年%d月%d日%d点   *\n", Num, S.top - S.base, Time1[0], Time1[1], Time1[2], Time1[3]);
		printf("********************************************\n");
	}
	return 1;
}

int Leaving_Car(SqStack &S, LinkQueue *Q, int Loc, int Time2[])
{
	int Y, M, D, H, Charge;
	int D1;
	int DL, DC;
	DL = DayofYear(Time2[0], Time2[1], Time2[2]);
	RecPointer p;
	int i;
	p = S.base;
	for (i = 1;i < Loc;i++)//找到出停车场的车所在位置，接着判断时间输入是否正确。
		p++;
	DC = DayofYear(p->Time[0], p->Time[1], p->Time[2]);
	if (Time2[0] < p->Time[0])
	{
		printf("离开时间有误");
		return 0;
	}
	else if (Time2[0] > p->Time[0])//如果离开时年份都大于入场时刻
	{
		Y = Time2[0] - p->Time[0];
		if (Time2[1] < p->Time[1])
		{
			Y--;
			M = Time2[1] + 12 - p->Time[1];
			D = Time2[2] - p->Time[2] + M * 30;
			if (Time2[3] >= p->Time[3])
				H = Time2[3] - p->Time[3];
			else
			{
				H = Time2[3] + 24 - p->Time[3];
				D--;
			}
		}
		else if (Time2[3] >= p->Time[3])//小时大于
		{
			H = Time2[3] - p->Time[3];
		}
		else if (Time2[3] < p->Time[3])
		{
			D--;
			H = Time2[3] - p->Time[3] + 24;
		}
		else
		{
			printf("离开时刻有误");
			return 0;
		}
	}
	else if (Time2[0] = p->Time[0])//年份相等
	{
		if (Time2[1] < p->Time[1])//月份小于
		{
			printf("离开时间有误");
			return 0;
		}
		else if (Time2[1] >= p->Time[1])
		{
			if (Time2[3] < p->Time[3])//小时小于
			{
				D = (DL - DC) / 11 - 1;
				H = Time2[3] + 24 - p->Time[3];
				Y = 0;
				M = 0;
				if (D < 0 || H < 0)
				{
					printf("离开时间有误");
					return 0;
				}
			}
			else if (Time2[3] >= p->Time[3])
			{
				D = (DL - DC) / 11;
				H = Time2[3] - p->Time[3];
				Y = 0;
				M = 0;
				if (D < 0 || H < 0)
				{
					printf("离开时间有误");
					return 0;
				}
			}
		}
	}
	if (Loc > S.top - S.base)
	{
		printf("********************************************\n");
		printf("该处未停车，请输入序号3查看停车情况\n");
		printf("********************************************\n");
		return 0;
	}
	char *E1 = (char*)malloc(5);
	char *E2 = (char*)malloc(5);
	int T1[4], T2[4];
	SqStack S1;
	InitStack(S1);
	while (S.top - S.base - Loc > 0)
	{
		Pop(S, E1, T1);
		Push(S1, E1, T1);
	}
	Pop(S, E1, T1);
	Charge = (Y * 365 * 24 + D * 24 + H) * 20;
	printf("********************************************\n");
	printf("车牌号为%s的车在停车场停留%d年%d天%d小时,应缴纳%d元\n", E1, Y, D, H, Charge);
	printf("********************************************\n");
	while (S1.top - S1.base > 0)
	{
		Pop(S1, E2, T2);
		Push(S, E2, T2);
	}
	if (DeQueue(Q, E1))//判断便道上是否有车
	{
		Push(S, E1, Time2);//便道上第一辆车进入停车场
		printf("车牌号为%s的车进入停车场，停在%d号车位，入场时间为%d年%d月%d日%d点\n", E1, S.top - S.base, Time2[0], Time2[1], Time2[2], Time2[3]);
		printf("*******************************************\n");
	}
	return 1;
}

int Checking_Car(SqStack &S, LinkQueue *Q)
{
	if (TravelS(S))
		;
	else
	{
		int i = 1;
		while (i <= N)
		{
			printf("********************************************\n");
			printf("%d号停车位：未停车                          *\n", i);
			i++;
		}
		printf("********************************************\n");
	}
	if (TravelQ(Q))
		;
	else
	{
		printf("便道未停车                                 *\n");
		printf("********************************************\n");
	}
	return 1;
}

int main()
{
	int Choice;//Choice表示选择的操作序号，i,j用于表示1，2操作的牌照号（停车场位置）及到达（离开）时间
	char Lic[6];
	int time[4];
	int Loc1;
	int Flag1;
	SqStack S;
	LinkQueue Q;
	InitStack(S);
	InitQueue(&Q);
	printf("****************************\n");
	printf("*欢迎使用停车场管理系统:   *\n");
	printf("*1:车辆到达                *\n");
	printf("*2:车辆离开                *\n");
	printf("*3:显示停车情况            *\n");
	printf("*4:退出系统                *\n");
	printf("*停车场车位数：%d           *\n", N);
	printf("****************************\n");
	printf("请输入操作序号：");
	scanf("%d", &Choice);
	if (Choice == 1)
	{
		Flag1 = 1;
		printf("****************************\n");
		printf("请输入车牌：");
		scanf("%s", Lic);
		printf("****************************\n");
		printf("请输入到达时刻：");
		while (Flag1)
		{
			scanf("%d%d%d%d", &time[0], &time[1], &time[2], &time[3]);
			if (time[3] == 24)
			{
				time[3] = 0;
				time[2]++;
			}
			if (time[1] > 12)
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入到达时刻：");
			}
			else if (time[3] > 24)
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入到达时刻：");
			}
			else if (time[2] > 30 && (time[1] == 2 || time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11))//2、4、6、9、11月份天数应不大于30
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入到达时刻：");
			}
			else if (time[2] > 31)
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入到达时刻：");
			}
			else if (time[1] == 2)
			{
				if ((time[0] % 4 == 0) && (time[0] % 100 != 0) || (time[0] % 400 == 0))//为闰年
				{
					if (time[2] > 29)
					{
						printf("时间输入有误，请重新操作\n");
						printf("请输入到达时刻：");
					}
					else
						Flag1 = 0;
				}
				else
				{
					if (time[2] > 28)
					{
						printf("时间输入有误，请重新操作\n");
						printf("请输入到达时刻：");
					}
					else
						Flag1 = 0;
				}
			}
			else
				Flag1 = 0;
		}
	}
	else if (Choice == 2)
	{
		Flag1 = 1;
		printf("****************************\n");
		printf("请输入车辆位置：");
		scanf("%d", &Loc1);
		printf("****************************\n");
		printf("请输入离开时刻：");
		while (Flag1)
		{
			scanf("%d%d%d%d", &time[0], &time[1], &time[2], &time[3]);
			if (time[3] == 24)
			{
				time[3] = 0;
				time[2]++;
			}
			if (time[1] > 12)
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入离开时刻：");
			}
			else if (time[3] > 24)
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入离开时刻：");
			}
			else if (time[2] > 30 && (time[1] == 2 || time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11))//2、4、6、9、11月份天数应不大于30
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入离开时刻：");
			}
			else if (time[2] > 31)
			{
				printf("时间输入有误，请重新操作\n");
				printf("请输入离开时刻：");
			}
			else if (time[1] == 2)
			{
				if ((time[0] % 4 == 0) && (time[0] % 100 != 0) || (time[0] % 400 == 0))//为闰年
				{
					if (time[2] > 29)
					{
						printf("时间输入有误，请重新操作\n");
						printf("请输入离开时刻：");
					}
					else
						Flag1 = 0;
				}
				else
				{
					if (time[2] > 28)
					{
						printf("时间输入有误，请重新操作\n");
						printf("请输入离开时刻：");
					}
					else
						Flag1 = 0;
				}
			}
			else
				Flag1 = 0;
		}
	}
	while (Choice != 4)
	{
		switch (Choice)
		{
		case 1: {
			Coming_Car(S, &Q, Lic, time);
		}
				break;
		case 2: {
			Leaving_Car(S, &Q, Loc1, time);
		}
				break;
		case 3:Checking_Car(S, &Q);
			break;
		default:printf("输入有误!\n");
			break;
		}
		printf("请输入操作序号：");
		scanf("%d", &Choice);
		if (Choice == 1)
		{
			Flag1 = 1;
			printf("****************************\n");
			printf("请输入车牌：");
			scanf("%s", Lic);
			printf("****************************\n");
			printf("请输入到达时刻：");
			while (Flag1)
			{
				scanf("%d%d%d%d", &time[0], &time[1], &time[2], &time[3]);
				if (time[3] == 24)
				{
					time[3] = 0;
					time[2]++;
				}
				if (time[1] > 12)
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入到达时刻：");
				}
				else if (time[3] > 24)
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入到达时刻：");
				}
				else if (time[2] > 30 && (time[1] == 2 || time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11))//2、4、6、9、11月份天数应不大于30
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入到达时刻：");
				}
				else if (time[2] > 31)
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入到达时刻：");
				}
				else if (time[1] == 2)
				{
					if ((time[0] % 4 == 0) && (time[0] % 100 != 0) || (time[0] % 400 == 0))//为闰年
					{
						if (time[2] > 29)
						{
							printf("时间输入有误，请重新操作\n");
							printf("请输入到达时刻：");
						}
						else
							Flag1 = 0;
					}
					else
					{
						if (time[2] > 28)
						{
							printf("时间输入有误，请重新操作\n");
							printf("请输入到达时刻：");
						}
						else
							Flag1 = 0;
					}
				}
				else
					Flag1 = 0;
			}
		}
		else if (Choice == 2)
		{
			Flag1 = 1;
			printf("****************************\n");
			printf("请输入车辆位置：");
			scanf("%d", &Loc1);
			printf("****************************\n");
			printf("请输入离开时刻：");
			while (Flag1)
			{
				scanf("%d%d%d%d", &time[0], &time[1], &time[2], &time[3]);
				if (time[3] == 24)
				{
					time[3] = 0;
					time[2]++;
				}
				if (time[1] > 12)
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入离开时刻：");
				}
				else if (time[3] > 24)
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入离开时刻：");
				}
				else if (time[2] > 30 && (time[1] == 2 || time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11))//2、4、6、9、11月份天数应不大于30
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入离开时刻：");
				}
				else if (time[2] > 31)
				{
					printf("时间输入有误，请重新操作\n");
					printf("请输入离开时刻：");
				}
				else if (time[1] == 2)
				{
					if ((time[0] % 4 == 0) && (time[0] % 100 != 0) || (time[0] % 400 == 0))//为闰年
					{
						if (time[2] > 29)
						{
							printf("时间输入有误，请重新操作\n");
							printf("请输入离开时刻：");
						}
						else
							Flag1 = 0;
					}
					else
					{
						if (time[2] > 28)
						{
							printf("时间输入有误，请重新操作\n");
							printf("请输入离开时刻：");
						}
						else
							Flag1 = 0;
					}
				}
				else
					Flag1 = 0;
			}
		}
	}
	printf("*****************************\n");
	printf("退出系统，欢迎您的下次使用！*\n");
	printf("*****************************\n");
	system("pause");
}