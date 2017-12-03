#include<iostream>
#include<cstdio>
#include<cstring>
#define NoneEdgeNum -1
using namespace std;


#define M 30
#define N  500

int G[M][M];
int n;

struct edgenode
{
	int node1;
	int node2;
	int weight;
}edge[N], result[M];

int adj[M];

int edgesum = 0;  //记录边的总数



void Input()
{
	int i, j;

	cin >> n;

	for (i = 0; i<n; i++)
	for (j = 0; j<n; j++)
		cin >> G[i][j];

}

void Change()
{
	int i, j, k;

	for (i = 0; i<n; i++)
	for (j = i + 1; j<n; j++)
	if (G[i][j] != NoneEdgeNum)
	{

		k = edgesum - 1;  // 最后一个元素所处位置
		while (k >= 0)
		{
			if (edge[k].weight>G[i][j])    //在插入时进行排序
			{
				edge[k + 1] = edge[k];
			}
			else break;
			k--;
		}
		edge[k + 1].weight = G[i][j];
		edge[k + 1].node1 = i;
		edge[k + 1].node2 = j;
		edgesum++;
	}
}



void Krus()
{
	int curnode1, curnode2;
	int k;
	int pos1, pos2;
	int curedge, choose;

	for (k = 0; k<n; k++)
		adj[k] = k;

	curedge = 0;
	choose = 0;
	while (choose<n - 1)
	{
		curnode1 = edge[curedge].node1; curnode2 = edge[curedge].node2;
		pos1 = curnode1;  pos2 = curnode2;
		while (adj[pos1] != pos1) pos1 = adj[pos1];
		while (adj[pos2] != pos2) pos2 = adj[pos2];
		if (pos1 == pos2) { curedge++; continue; }
		adj[pos2] = pos1;
		result[choose].node1 = pos1;
		result[choose].node2 = pos2;
		result[choose].weight = edge[curedge].weight;
		choose++;
		curedge++;
	}
}

void output()
{
	int i;
	int sum=0;
	for (i = 0; i<n - 1; i++)
	{
		sum += result[i].weight;
		//cout << i << ":  (" << result[i].node1 << " ---> " << result[i].node2 << " ) : " << result[i].weight << endl;
	}
	cout << sum<<endl;
}

int main()
{
	while (cin >> n&&n != 0){
		memset(G, NoneEdgeNum, sizeof(G));
		edgesum = 0;
		for (int i = 1; i < n; i++){
			char letter;
			int num;
			cin >> letter >> num;
			for (int j = 0; j < num; j++){
				char letter1;
				int weight;
				cin >> letter1 >> weight;
				G[letter - 65][letter1 - 65] = weight;
				G[letter1 - 65][letter - 65] = weight;
			}	
		}
		Change();
		Krus();
		output();
	}
	//Input();
	return 0;

}