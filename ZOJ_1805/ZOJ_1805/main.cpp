#include <iostream>
#include <set>
#include <fstream>
#include <string.h>
#define maxSize 130
#define childNum 4
#define INPUT
using namespace std;


char image[maxSize][maxSize];
set<string> judePath;//记录子树路径

struct Node
{
	char value;
	string path;
	int AllNum;//该子树的结点总数
	int AfterDealNum;//该子树经压缩后的结点总数
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
		//计算中间坐标
		int mx = (rx - lx) / 2+lx;
		int my = (ry - ly) / 2+ly;
		newNode->child[0] = SquadTrees(lx, ly, mx, my);
		newNode->child[1] = SquadTrees(lx, my+1, mx, ry);
		newNode->child[2] = SquadTrees(mx+1, ly, rx, my);
		newNode->child[3] = SquadTrees(mx + 1, my + 1, rx, ry);
		//判断是否全为0
		if (newNode->child[0]->value == '0'&&newNode->child[1]->value == '0'&&newNode->child[2]->value == '0'&&newNode->child[3]->value == '0')
		{
			newNode->value = '0';
			newNode->path = "0";
			//删除子节点
			for (int i = 0; i < childNum; i++){
				delete newNode->child[i];
				newNode->child[i] = NULL;
			}
			return newNode;
		}
		//判断是否全为1
		if (newNode->child[0]->value == '1'&&newNode->child[1]->value == '1'&&newNode->child[2]->value == '1'&&newNode->child[3]->value == '1')
		{
			newNode->value = '1';
			newNode->path = "1";
			//删除子节点
			for (int i = 0; i < childNum; i++){
				delete newNode->child[i];
				newNode->child[i] = NULL;
			}
			return newNode;
		}
		else//不全为0或为1
		{
			newNode->value = '2';
			newNode->path = "2";
			//判断是否有相等的子树
			for (int i = 0; i<childNum; i++)
			{
				if (newNode->child[i]->path.length() != 1){//路径长不等于1即不是结点再判断是否有子树相等
					set<string>::iterator it = judePath.find(newNode->child[i]->path);
					if (it == judePath.end()) //没有相等的子树
					{
						judePath.insert(newNode->child[i]->path);
						newNode->AfterDealNum += newNode->child[i]->AfterDealNum;
					}
				}
				else{
					newNode->AfterDealNum += newNode->child[i]->AfterDealNum;
				}
				newNode->path += newNode->child[i]->path;//无论有没有相等的子树，所有路径都要计算
				newNode->AllNum += newNode->child[i]->AllNum;//无论有没有相等的子树，所有结点都要计算
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
		//图片补0
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
		//构建四叉树
		judePath.clear();
		Node *node = SquadTrees(0, 0, scale - 1, scale - 1);
		cout << node->AllNum << " " << node->AfterDealNum << endl;
	}

	in.close();
#endif // IN
	system("pause");
	return 0;
}
