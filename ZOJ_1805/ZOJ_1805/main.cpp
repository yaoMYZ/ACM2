#include <iostream>
#include <set>
#include <fstream>
#include <string.h>
#define maxSize 130
#define childNum 4
#define INPUT
using namespace std;


char image[maxSize][maxSize];
set<string> judePath;//��¼����·��

struct Node
{
	char value;
	string path;
	int AllNum;//�������Ľ������
	int AfterDealNum;//��������ѹ����Ľ������
	Node *child[childNum];
	bool deleteFlag;
	Node()
	{
		path = "";
		AllNum = 1;
		AfterDealNum = 1;
		deleteFlag = false;
		for (int i = 0; i<childNum; i++)
		{
			child[i] = NULL;
		}
	}
};

int normalize(int r, int c)
{
	int scale = 2;
	int bigNum = r;
	if (c>r)
		bigNum = c;
	if (bigNum == 1)
		return 1;
	while (scale<bigNum)
		scale *= 2;
	return scale;
}

Node *SquadTrees(int lx, int ly, int rx, int ry)
{
	if (lx >= rx)
	{
		Node *newNode = new Node;
		if (image[lx][ly] == '1')
		{
			newNode->value = '1';
			newNode->path = "1";
		}
		else
		{
			newNode->value = '0';
			newNode->path = "0";
		}
		return newNode;
	}
	else
	{
		Node *newNode = new Node;
		//�����м�����
		int mx = (rx - lx) / 2+lx;
		int my = (ry - ly) / 2+ly;
		newNode->child[0] = SquadTrees(lx, ly, mx, my);
		newNode->child[1] = SquadTrees(lx, my+1, mx, ry);
		newNode->child[2] = SquadTrees(mx+1, ly, rx, my);
		newNode->child[3] = SquadTrees(mx + 1, my + 1, rx, ry);
		//�ж��Ƿ�ȫΪ0
		if (newNode->child[0]->value == '0'&&newNode->child[1]->value == '0'&&newNode->child[2]->value == '0'&&newNode->child[3]->value == '0')
		{
			newNode->value = '0';
			newNode->path = "0";
			//ɾ���ӽڵ�
			for (int i = 0; i < childNum; i++){
				delete newNode->child[i];
				newNode->child[i] = NULL;
			}
			return newNode;
		}
		//�ж��Ƿ�ȫΪ1
		if (newNode->child[0]->value == '1'&&newNode->child[1]->value == '1'&&newNode->child[2]->value == '1'&&newNode->child[3]->value == '1')
		{
			newNode->value = '1';
			newNode->path = "1";
			//ɾ���ӽڵ�
			for (int i = 0; i < childNum; i++){
				delete newNode->child[i];
				newNode->child[i] = NULL;
			}
			return newNode;
		}
		else//��ȫΪ0��Ϊ1
		{
			newNode->value = '2';
			newNode->path = "2";
			//�ж��Ƿ�����ȵ�����
			for (int i = 0; i<childNum; i++)
			{
				if (newNode->child[i]->path.length() != 1){//·����������1�����ǽ�����ж��Ƿ����������
					set<string>::iterator it = judePath.find(newNode->child[i]->path);
					if (it == judePath.end()) //û����ȵ�����
					{
						judePath.insert(newNode->child[i]->path);
						newNode->AfterDealNum += newNode->child[i]->AfterDealNum;
					}
				}
				else{
					newNode->AfterDealNum += newNode->child[i]->AfterDealNum;
				}
				newNode->path += newNode->child[i]->path;//������û����ȵ�����������·����Ҫ����
				newNode->AllNum += newNode->child[i]->AllNum;//������û����ȵ����������н�㶼Ҫ����
			}
			return newNode;
		}

	}

}


int main()
{
#ifdef INPUT
	ifstream in("data.txt", ios::in);
	int r, c;
	while ((in >> r >> c) && r != 0 && c != 0)
	{
		for (int i = 0; i<r; i++)
		{
			for (int j = 0; j<c; j++)
			{
				in >> image[i][j];
			}
		}
		int scale = normalize(r, c);
		//ͼƬ��0
		for (int i = 0; i<scale; i++){
			if (i <= r - 1){
				for (int j = c; j<scale; j++)
					image[i][j] = '0';
			}
			else{
				for (int j = 0; j<scale; j++)
					image[i][j] = '0';
			}
		}
		//�����Ĳ���
		judePath.clear();
		Node *node = SquadTrees(0, 0, scale - 1, scale - 1);
		cout << node->AllNum << " " << node->AfterDealNum << endl;
	}

	in.close();
#endif // IN
	system("pause");
	return 0;
}
