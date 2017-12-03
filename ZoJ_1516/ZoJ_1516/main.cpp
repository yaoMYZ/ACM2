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

int ground[Size][Size];//��¼���������1Ϊ������0Ϊ�յ�


int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

bool dfs(int start,linknode* p){
	int i, temp;
	p = A[start].head;//pָ��start����Ӧ�ڽӱ����ͷ
	while (p != NULL){//����ڽӽ����з����������Ƿ���ƥ��
		i = p->data;//ȡ���ڽӽ��i
		if (visit[i] == 0){
			visit[i] = 1;
			temp = pre[i];//������ǰ��ƥ�����
			pre[i] = start;//������д�µ�ƥ���ϵ
			if (temp == -1 || dfs(temp,p)){//��������µ�ƥ���Ƿ���Ч
				return true;
			}
			pre[i] = temp;//��ƥ�䳢��ʧ�ܣ������ǰ��ƥ��
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
	//��ground���ĸ��߽��ʼ��Ϊ1
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
		init(n,m);//��ʼ��
		int k;
		cin >> k;
		for (int i = 0; i < k; i++){
			int x, y;
			cin >> x >> y;
			ground[x][y] = 1;//�ĸ��߽�ճ��������д���
		}
		//����߹�ϵ
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (ground[i][j] != 1){
					for (int d = 0; d < 4; d++){
						int dx = i + dir[d][0];
						int dy = j + dir[d][1];
						if (ground[dx][dy] != 1){
							linknode* newNode = new linknode;
							newNode->data = dx*dy;
							//����ͷ����
							linknode *p = A[i*j].head;
							A[i*j].head = newNode;
							newNode->next = p;
						}
					}
				}
			}
		}
		//���ж���ͼƥ��
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