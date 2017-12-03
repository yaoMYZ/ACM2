#include <iostream>
#include <string.h>
#include<set>
#include<algorithm>
#include<vector>
#define  maxn 50000
#define  MAX  100000
using namespace std;


struct node
{
	int l;
	int r;
	int key = MAX;
};

node tree[4 * maxn];

void buildTree(int index, int a, int b)
{
	//赋值
	tree[index].l = a;
	tree[index].r = b;
	if (a == 1)
		tree[index].key = 0;
	if (b == a)
		return;
	int middle = (a + b) / 2;
	buildTree(index * 2 , a, middle);
	buildTree(index * 2 + 1, middle+1, b);
}

int findMinKey(int i, int a, int b){
	if (a <= tree[i].l&&b >= tree[i].r){
		return tree[i].key;
	}
	int min1 = MAX;
	int min2 = MAX;
	if (a <= (tree[i].l+tree[i].r)/2)
		min1 = findMinKey(2 * i, a, b);
	if (b >(tree[i].l + tree[i].r) / 2)
		min2 = findMinKey(2 * i + 1, a, b);
	if (min1 < min2)
		return min1;
	else
		return min2;
}


void resetKey(int i,int a,int b,int key){
	if (a <= tree[i].l&&b >= tree[i].r){
		if (tree[i].key < key)
			tree[i].key = key;
		return;
	}
	if (a <= (tree[i].l + tree[i].r) / 2)
		resetKey(2 * i, a, b,key);
	if (b >(tree[i].l + tree[i].r) / 2)
		resetKey(2 * i+1, a, b, key);
}


int findIndex(int i,int b){
	if (tree[i].l == b&&tree[i].r == b){//找到边界点
		return i;
	}
	else{
		int middle = (tree[i].l + tree[i].r) / 2;
		if (middle < b)
			findIndex(2 * i + 1,  b);
		else
			findIndex(2 * i,  b);
	}
}

void paint(int a, int b){
	int index = findIndex(1, b);
	int subMinKey = findMinKey(1, a, b - 1);
	if (tree[index].key > subMinKey+1){
		tree[index].key = subMinKey + 1;
		//重新设置最小键值
		resetKey(1, a + 1, b, tree[index].key);
	}
}



int main(){
	int n, m;
	while (cin >> n >> m){
		buildTree(1, 1, n);
		int a, b;
		for (int i = 0; i < m; i++){
			cin >> a >> b;
			paint(a, b);
		}
		int index = findIndex(1, n);
		cout << tree[index].key << endl;
	}
}