#include<iostream>
#include<string.h>
#include<cmath>
#include<cstdio>
#define  INF 0x7ffffff
#define MaxNum 30000
using namespace std;

int dist[MaxNum];
int c[MaxNum];//每个军营的最大士兵容量
int d[MaxNum];//从第一个军营到第i个军营的最大士兵容量的总数
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
	d[0] = 0;//第一个点
	dist[n] = 0;//额外点
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
	//n次遍历结束，若还有累计权重变小的则表明有负数权重
	for (k = 0; k<edgeNum; k++)//判断是不是有负权回路
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
		for (i = 1; i <= n; i++)//一些不等式
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