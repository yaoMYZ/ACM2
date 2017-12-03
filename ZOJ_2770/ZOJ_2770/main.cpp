#include<iostream>
#include<string.h>
#include<cmath>
#include<cstdio>
#define  INF 0x7ffffff
#define MaxNum 30000
using namespace std;

int dist[MaxNum];
int c[MaxNum];//ÿ����Ӫ�����ʿ������
int d[MaxNum];//�ӵ�һ����Ӫ����i����Ӫ�����ʿ������������
int edgeNum;
int n, m;

struct  edges
{
	int from;
	int to;
	int  weight;
}edge[MaxNum];

void init()
{
	edgeNum = 0;
	int i;
	for (i = 0; i <= n; i++)
	{
		dist[i] = INF;
	}
	d[0] = 0;//��һ����
	dist[n] = 0;//�����
}

bool bellman()
{

	int i, k, t;
	for (i = 0; i<n; i++)
	{
		for (k = 0; k<edgeNum; k++)
		{
			t = dist[edge[k].from] + edge[k].weight;
			if (dist[edge[k].from] != INF&&t<dist[edge[k].to])
			{
				dist[edge[k].to] = t;
			}
		}

	}
	//n�α����������������ۼ�Ȩ�ر�С��������и���Ȩ��
	for (k = 0; k<edgeNum; k++)//�ж��ǲ����и�Ȩ��·
	{
		if (dist[edge[k].from] != INF&&dist[edge[k].from] + edge[k].weight<dist[edge[k].to])
			return false;
	}
	return true;
}
int main()
{
	while (scanf("%d%d", &n, &m) != EOF)
	{
		init();
		int i, from, to, weight;
		for (i = 1; i <= n; i++)//һЩ����ʽ
		{
			scanf("%d", &c[i]);
			edge[edgeNum].from = i - 1;
			edge[edgeNum].to = i;
			edge[edgeNum].weight = c[i];
			edgeNum++;
			edge[edgeNum].from = i;
			edge[edgeNum].to = i - 1;
			edge[edgeNum].weight = 0;
			edgeNum++;
			d[i] = c[i] + d[i - 1];
		}
		for (i = 0; i<m; i++)
		{
			scanf("%d%d%d", &from, &to, &weight);
			edge[edgeNum].from = to;
			edge[edgeNum].to = from - 1;
			edge[edgeNum].weight = -weight;
			edgeNum++;
			edge[edgeNum].from = from - 1;
			edge[edgeNum].to = to;
			edge[edgeNum].weight = d[to] - d[from - 1];
			edgeNum++;
		}
		if (!bellman())
			printf("Bad Estimations\n");
		else
			printf("%d\n", dist[n] - dist[0]);
	}
	return 0;
}