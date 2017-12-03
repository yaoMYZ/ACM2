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
//	//���ó�ʼֵΪ0
//	memset(G, 0, sizeof(G));
//	memset(degree, 0, sizeof(degree));
//	memset(result, -1, sizeof(result));
//	//��������ڽӾ���
//	srand(time(0));
//	for (int i = 0; i < Size; i++){
//		for (int j = 0; j < Size; j++){
//			double ran = rand();
//			if (ran < 0.5&&i!=j){
//				G[i][j] = 1;
//				degree[j]++;//�ڽӵ���ȼ�һ
//			}	
//		}
//	}
//	//��ʼ�����Ϊ��ĵ�
//	for (int i = 0; i < Size; i++){
//		if (degree[i] == 0)
//			ZeroDegree.push(i);
//	}
//}

void showReslut(int index){
	if (index != pNumber)
		cout << "��ͼ�л�";
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
		while (G[dealNode][i] > 0){//Ĭ����ƽ�бߴ��ڣ�����Ҫע���������
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
	if (!ifHaveZero){//û��0�ȱ����
		showReslut(index);
	}
	////����ͼ�޻�����Ա������е�
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
		//ֻҪ��ͼƬ�����ڸø����о���Ӹ��ַ��ڸø�����
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
				int len = parray[i][j].length();//'.'λ�õ��ַ�����Ϊ0
				for (int k = 0; k < len; ++k){
					if (parray[i][j][k] != window[i][j]){
						G[window[i][j] - 'A'][parray[i][j][k] - 'A'] ++;
						degree[parray[i][j][k] - 'A']++;
					}
				}
			}
		}
	}
	//��ʼ�����Ϊ��ĵ�
	for (int i = 0; i < pNumber; i++){
		if (degree[i] == 0)
			ZeroDegree.push(i);
	}
}

void InitValue(){
	//���ó�ʼֵ
	ZeroDegree = priority_queue<int>();
	pNumber = 0;
	memset(G, 0, sizeof(G));
	memset(degree, 0, sizeof(degree));
	memset(result, -1, sizeof(result));
	for (int i = 0; i < Size; i++){//��ѡ������ѡ����
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
	//			//�жϸ�ͼƬ�ı߽磬����'.'�����
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
				//�жϸ�ͼƬ�ı߽磬����'.'�����
				if (window[i][j] != '.'){
					pbArray[window[i][j] - 'A'] = checkBound(i, j);
					if (window[i][j] - 'A' + 1>pNumber)//�ж��ж���ͼƬ
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
