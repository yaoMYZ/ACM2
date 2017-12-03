#include <iostream>
#include <string.h>
#include<set>
#include<algorithm>
#include<vector>
#define  maxn 5
using namespace std;

struct myComp
{
	bool operator()(const int &a, const int &b)
	{
		return a<b;
    }
};

struct node
{
	int x;
	int y;
	int key = -1;
};

node seg[4*maxn];
int colorNum[maxn];
set<int, myComp> record;

void buildTree(int index, int a, int b)
{
	//赋值
	seg[index].x = a;
	seg[index].y = b;

	if ((b - a) == 1)
	{
		return;
	}
	int middle = (a + b) / 2;
	buildTree(index * 2 + 1, a, middle);
	buildTree(index * 2 + 2, middle, b);
	return;
}

int findColor(int signal, int index){
	if (seg[index].key == -2){
		findColor(signal, index * 2 + signal);
	}
	else{
		return seg[index].key;
	}
}


void deleteNode(int index){
	if (seg[index].key == -1)
		return;
	if ((seg[index].y - seg[index].x) == 1){
		seg[index].key = -1;
		return;
	}
	deleteNode(index * 2 + 1);
	deleteNode(index * 2 + 2);
}


void insertNode(int a, int b, int index, int color)
{
	if (a <= seg[index].x&&seg[index].y <= b)
	{
		seg[index].key = color;
		//覆盖子树下节点
		if ((seg[index].y - seg[index].x) != 1){
			deleteNode(index * 2 + 1);
			deleteNode(index * 2 + 2);
		}
		return;
	}
	//原本的颜色被分割
	if (seg[index].key > 0){
		seg[index * 2 + 1].key = seg[index].key;
		seg[index * 2 + 2].key = seg[index].key;
	}
	seg[index].key = -2;
	if (a<(seg[index].x + seg[index].y) / 2)
	{
		insertNode(a, b, index * 2 + 1, color);
	}
	if (b>(seg[index].x + seg[index].y) / 2)
	{
		insertNode(a, b, index * 2 + 2, color);
	}

}

void countColor(int index){
	if (seg[index].key == -1)
		return;
	if (seg[index].key>=0){
		colorNum[seg[index].key]++;
		record.insert(seg[index].key);
		return;
	}
	else{
		int lkey = findColor(2, index * 2 + 1);
		int rkey = findColor(1, index * 2 + 2);
		if (lkey == rkey&&lkey != -1)
			colorNum[lkey]--;
		countColor(index * 2 + 1);
		countColor(index * 2 + 2);
	}

}

//preorder
void preorder(int i, int &c)//i means index, c means previous color
{
	if (seg[i].key == -1){
		if (c == -1)
			return;
		else{
			colorNum[c]++;
			record.insert(c);
			c = -1;
			return;
		}//end else
	}//endif
	else if (seg[i].key == -2){//has branches
		preorder(2 * i+1, c);
		preorder(2 * i + 2, c);
	}//end else if
	else {//has color
		if (c == seg[i].key)//same
			return;
		else {//different color
			if (c != -1){
				colorNum[c]++;
				record.insert(c);
			}	
			c = seg[i].key;
		}
	}//end else
	return;
}


int main()
{
	int n;
	while (cin >> n)
	{
		buildTree(0, 0, maxn);
		memset(colorNum, 0, sizeof(colorNum));
		record.clear();
		for (int i = 0; i<n; i++)
		{
			int a, b, c;
			cin >> a >> b >> c;
			insertNode(a, b, 0, c);
		}
		//countColor(0);
		int cc = -1;
		preorder(0,cc);
		set<int>::iterator it;
		for (it = record.begin(); it != record.end(); it++){
			if (colorNum[*it]>0)
				cout << *it << " " << colorNum[*it] << endl;
		}
		cout << endl;
	}
	return 0;
}
