#include<iostream>
#include<stack>
#include<cmath>
#include<time.h>
#include<string>
#include<fstream>
#include<queue>
#define INPUT
#define Size 33
#define Max 300
using namespace std;

struct pBound{
	int minw = Max;
	int maxw = -1;
	int minh = Max;
	int maxh = -1;
}example;

int h, w;

int G[Size][Size];
int degree[Size];
priority_queue<int> ZeroDegree;
int result[Size];

char window[Size][Size];
pBound pbArray[Size];
string parray[Size][Size];
int pNumber = 0;

//void input(){
//	//设置初始值为0
//	memset(G, 0, sizeof(G));
//	memset(degree, 0, sizeof(degree));
//	memset(result, -1, sizeof(result));
//	//随机设置邻接矩阵
//	srand(time(0));
//	for (int i = 0; i < Size; i++){
//		for (int j = 0; j < Size; j++){
//			double ran = rand();
//			if (ran < 0.5&&i!=j){
//				G[i][j] = 1;
//				degree[j]++;//邻接点入度加一
//			}	
//		}
//	}
//	//初始化入度为零的点
//	for (int i = 0; i < Size; i++){
//		if (degree[i] == 0)
//			ZeroDegree.push(i);
//	}
//}

void showReslut(int index){
	if (index != pNumber)
		cout << "该图有环";
	else{
		for (int i = index-1; i >=0; i--)
			cout << char(result[i]+65);
	}
	cout << endl;
}

void deal(int index,int dealNode){
	//int index = 0;
	bool ifHaveZero = false;
	result[index++] = dealNode;

	for (int i = 0; i < pNumber; i++){
		int thedegree = G[dealNode][i];
		while (G[dealNode][i] > 0){//默认有平行边存在，所以要注意这种情况
			G[dealNode][i]--;
			degree[i]--;			
		}
		if (degree[i] == 0&&thedegree>0){
			ZeroDegree.push(i);
			ifHaveZero = true;
		}
	}
	while (!ZeroDegree.empty()){
		int zero = ZeroDegree.top();
		ZeroDegree.pop();
		deal(index, zero);
	}
	if (!ifHaveZero){//没有0度边输出
		showReslut(index);
	}
	////若该图无环则可以遍历所有点
	//if (index != pNumber)
	//	return false;
	//else
	//   return true;
}



pBound checkBound(int i, int j){
	pBound original = pbArray[window[i][j] - 'A'];
	if (i < original.minh)
		original.minh = i;
	if (i>original.maxh)
		original.maxh = i;
	if (j < original.minw)
		original.minw = j;
	if (j>original.maxw)
		original.maxw = j;
	return original;
}


void paintWindow(){
	for (int i = 0; i < pNumber; i++){
		//只要该图片覆盖在该格子中就添加该字符在该格子中
		for (int j = pbArray[i].minh; j <= pbArray[i].maxh; j++){
			parray[j][pbArray[i].maxw] += i + 'A';
			parray[j][pbArray[i].minw] += i + 'A';
		}
		for (int k = pbArray[i].minw+1; k <= pbArray[i].maxw-1; k++){
			parray[pbArray[i].maxh][k] += i + 'A';
			parray[pbArray[i].minh][k] += i + 'A';
		}
	}
}

void dealG(){
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (window[i][j] != '.'){
				int len = parray[i][j].length();//'.'位置的字符长度为0
				for (int k = 0; k < len; ++k){
					if (parray[i][j][k] != window[i][j]){
						G[window[i][j] - 'A'][parray[i][j][k] - 'A'] ++;
						degree[parray[i][j][k] - 'A']++;
					}
				}
			}
		}
	}
	//初始化入度为零的点
	for (int i = 0; i < pNumber; i++){
		if (degree[i] == 0)
			ZeroDegree.push(i);
	}
}

void InitValue(){
	//设置初始值
	ZeroDegree = priority_queue<int>();
	pNumber = 0;
	memset(G, 0, sizeof(G));
	memset(degree, 0, sizeof(degree));
	memset(result, -1, sizeof(result));
	for (int i = 0; i < Size; i++){//先选择列再选择行
		pbArray[i] = example;
		for (int j = 0; j < Size; j++){
			parray[i][j] = "";
		}
	}
}

void InitG(){
	paintWindow();
	dealG();
}

int main()
{
	//while (cin >> h >> w){
	//	for (int i = 0; i < h; i++){
	//		for (int j = 0; j < w; j++){
	//			cin >> window[i][j];
	//			//判断该图片的边界，若是'.'则忽略
	//			if (window[i][j] != '.')
	//				pbArray[window[i][j] - 'A'] = checkBound(i,j);
	//		}
	//	}
	//}
#ifdef INPUT
	ifstream in("data.txt", ios::in);
	while (in >> h >> w){
		InitValue();
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				in >> window[i][j];
				//判断该图片的边界，若是'.'则忽略
				if (window[i][j] != '.'){
					pbArray[window[i][j] - 'A'] = checkBound(i, j);
					if (window[i][j] - 'A' + 1>pNumber)//判断有多少图片
						pNumber = window[i][j] - 'A' + 1;
				}
			}
		}
		InitG();
		while (!ZeroDegree.empty()){
			int zero = ZeroDegree.top();
			ZeroDegree.pop();
			deal(0, zero);
		}
	}
	in.close();
#endif
	system("pause");
	return 0;
}
