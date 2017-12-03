#include<iostream>
#define MAX 100000
#define Size 100
using namespace std;

struct linknode{
	int data;
	linknode* next = NULL;
};

struct node{
	linknode* head = NULL;
}A[Size];


int visit[Size];
int pre[Size];
int nmap[Size][Size];

char map[Size][Size];
int R, C;//行列机器人可摆放位置的数量
int col[Size][Size], row[Size][Size];


void add(int u, int v)
{
	nmap[u][v+u] = 1;
	nmap[v + u][u] = 1;
}


bool dfs(int start){
	int i, temp;
	for (int i = 0; i < Size; i++){//逐个带你进行分析，分析能否匹配
		if (nmap[start][i] == 1 && visit[i] == 0){
			//有边相连且未被访问过
			visit[i] = 1;
			temp = pre[i];//保留当前的匹配情况
			pre[i] = start;//尝试填写新的匹配关系
			if (temp = -1 || dfs(temp)){//分析这个新的匹配是否有效
				return true;
			}
			pre[i] = temp;//新匹配尝试失败，填回以前的匹配
		}
	}
	return false;
}

void Init(){
	memset(col, 0, sizeof(col));
	memset(row, 0, sizeof(row));
	memset(pre, -1, sizeof(pre));
	memset(nmap, 0, sizeof(nmap));
}

int main()
{

	int T;
	cin >> T;
	int n, m;
	for (int tt = 1; tt <= T;tt++)
	{
		Init();
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> map[i][j];
		R = C = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (map[i][j] != '#' && row[i][j] == 0)
				{
					for (int k = j; map[i][k] != '#' && k <= m; k++)
						row[i][k] = R;
					++R;
				}
				if (map[i][j] != '#' && col[i][j] == 0)
				{
					for (int k = i; map[k][j] != '#' && k <= n; k++)
						col[k][j] = C;
					++C;
				}
			}
		}
		for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		if (map[i][j] == 'o' && row[i][j] != 0 && col[i][j] != 0)
			add(row[i][j], col[i][j]);
		cout << "Case :" << tt<<endl;
		for (int i = 0; i < R + C; i++){
			memset(visit, 0, sizeof(visit));
			dfs(i);
		}
		int num = 0;
		for (int i = 0; i < R + C;i++)
		if (pre[i] != -1)
			num++;
		cout << num / 2 << endl;
	}
	system("pause");
	return 0;
}