#include<iostream>
#include"SpanningTree.h"
#include<time.h>
#define Size 10000
#define Max 1000000
using namespace std;

int randomValue(double ran){
	return ran / time(0)*Max;
}

int main()
{
	srand(time(0));
	int T = randomValue(rand());//第一天销售额
	spanningTree st;
	st.insert(T);
	for (int i = 1; i < Size; i++){
		int value = randomValue(rand());
		st.insert(value);
		T += st.calT();
	}
	cout << T << endl;
	system("pause");
	return 0;
}