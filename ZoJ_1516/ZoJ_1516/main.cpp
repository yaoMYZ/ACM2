#include<iostream>
#define Size 110
using namespace std;

struct linknode{
	int data;
	linknode* next = NULL;
};

struct node{
	linknode* head=NULL;
}A[Size*Size];



int visit[Size*Size];
int pre[Size*Size];

int ground[Size][Size];//记录土地情况，1为池塘，0为空地


int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

bool dfs(int start,linknode* p){
	int i, temp;
	p = A[start].head;//p指向start结点对应邻接表的链头
	while (p != NULL){//逐个邻接结点进行分析，分析是否能匹配
		i = p->data;//取出邻接结点i
		if (visit[i] == 0){
			visit[i] = 1;
			temp = pre[i];//保留当前的匹配情况
			pre[i] = start;//尝试填写新的匹配关系
			if (temp == -1 || dfs(temp,p)){//分析这个新的匹配是否有效
				return true;
			}
			pre[i] = temp;//新匹配尝试失败，填回以前的匹配
		}
		p = p->next;
	}
	return false;
}

void ClearLink(){
	for (int i = 0; i < Size*Size; i++){
		linknode* p = A[i].head;
		while (p != NULL){
			linknode* del = p->next;
			p = p->next;
			delete del;
		}
		A[i].head = NULL;
	}
}

void init(int n,int m){
	ClearLink();
	memset(pre, -1, sizeof(pre));
	memset(ground, 0, sizeof(ground));
	//将ground的四个边界初始化为1
	for (int i = 0; i <= m + 1; i++){
		ground[0][i] = 1;
		ground[n + 1][i] = 1;
	}
	for (int i = 1; i <= n; i++){
		ground[i][0] = 1;
		ground[i][m + 1] = 1;
	}
}

int main()
{
	int n, m;
	while (cin >> n >> m && (n != 0 && m != 0)){
		init(n,m);//初始化
		int k;
		cin >> k;
		for (int i = 0; i < k; i++){
			int x, y;
			cin >> x >> y;
			ground[x][y] = 1;//四个边界空出，不进行处理
		}
		//处理边关系
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (ground[i][j] != 1){
					for (int d = 0; d < 4; d++){
						int dx = i + dir[d][0];
						int dy = j + dir[d][1];
						if (ground[dx][dy] != 1){
							linknode* newNode = new linknode;
							newNode->data = dx*dy;
							//进行头插入
							linknode *p = A[i*j].head;
							A[i*j].head = newNode;
							newNode->next = p;
						}
					}
				}
			}
		}
		//进行二部图匹配
		for (int i = 1; i <= n*m; i++){
			memset(visit, 0, sizeof(visit));
			linknode *p=NULL;
			dfs(i,p);
		}
		int num = 0;
		for (int i = 1; i <= n*m; i++){
			if (pre[i] != -1)
				num++;
		}
		cout << num / 2 << endl;
	}
	return 0;
}