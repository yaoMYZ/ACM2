#include<iostream>
#include<cstring>
#include<cstdio>
#define MAX 100000
#define Size 25
using namespace std;


int map[Size][Size];

void floyd(){
	for (int k = 0; k < 20; k++){
		for (int i = 0; i < 20; i++){
			for (int j = 0; j < 20; j++){
				if (map[i][j]>map[i][k] + map[k][j])
					map[i][j] = map[i][k] + map[k][j];
			}
		}
	}
	
}

int main(){

	int n, m,x,y;
	int cas = 1;
	while (scanf_s("%d",&n)!=EOF){
		for (int i = 0; i < 20; i++){
			for (int j = 0; j < 20; j++){
				map[i][j] = MAX;
			}
		}

		for (int j = 0; j < n; j++){
			scanf_s("%d", &m);
			map[0][m-1]=map[m-1][0] = 1;
		}
		for (int i = 1; i < 19; i++){
			scanf_s("%d",&n);
			for (int j = 0; j < n; j++){
				scanf_s("%d", &m);
				map[i][m-1] =map[m-1][i]= 1;
			}
		}
		floyd();
		printf_s("Test Set #%d\n", cas++);
		scanf_s("%d", &n);
		while (n--)
		{
			scanf_s("%d%d", &x, &y);
			printf_s("%d to %d: %d\n", x, y, map[x-1][y-1]);
		}
		printf_s("\n");
	}

	return 0;
}