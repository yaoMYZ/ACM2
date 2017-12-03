#include<iostream>
#include<cstdio>
#define  MAXINT  32767
#define MAXNUM  210

using namespace std;

double min(double a, double b){
	if (a < b)
		return a;
	else
		return b;
}


double max(double a, double b){
	if (a > b)
		return a;
	else
		return b;
}

double edge[MAXNUM][MAXNUM];
int coordinate[MAXNUM][2];
int n;

void Floyd(){
	for (int k = 0; k < n; k++){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				edge[i][j] = min(edge[i][j], max(edge[i][k], edge[k][j]));
			}
		}
	}
}


int main(){
	
	int k = 1;
	//ÊäÈë
	while (scanf_s("%d", &n) != EOF){
		for (int i = 0; i < n; i++){
			scanf_s("%d%d", &coordinate[i][0], &coordinate[i][1]);
			for (int j = 0; j<i; j++){
				double temp = (coordinate[i][0] - coordinate[j][0])*(coordinate[i][0] - coordinate[j][0]) + (coordinate[i][1] - coordinate[j][1])*(coordinate[i][1] - coordinate[j][1]);
				edge[i][j] = edge[j][i] = sqrt(temp);
			}
			edge[i][i] = MAXINT;
		}
		Floyd();
		//Êä³ö
		printf_s("Scenario #%d\n", k++);
		printf_s("Frog Distance = %.3lf\n\n", edge[0][1]);
	}
	return 0;
}