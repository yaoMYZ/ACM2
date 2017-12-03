#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdio>
using namespace std;

vector<int> number;
map<int, int> numMap;
int tempArray[32];
int theNum;
bool flag = false;

void show(int n, int sum)
{
	cout << tempArray[0];
	for (int i = 1; i<n; i++)
		cout << "+" << tempArray[i];
	cout << "=" << sum << endl;
}

void DFS(int index, int arraySize, int sum, int len)
{

	if (len == 0) //临时数组的元素大于等于2时才判断是否有等式
	{
		map<int, int>::iterator it = numMap.find(sum);
		if (it != numMap.end())
		{
			show(arraySize, sum);
			flag = true;
		}
	}
	else
	{
		for (int i = index; i<theNum - 1; i++)
		{
			if (sum + number[i] <= number[theNum - 1])
			{
				tempArray[arraySize] = number[i];
				DFS(i + 1, arraySize + 1, sum + number[i], len - 1);
			}
			else
			{
				break;
			}
		}
		return;
	}
}


int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i<n; i++)
	{
		int m;
		int num;
		scanf("%d", &m);
		//initailize
		theNum = m;
		number.clear();
		numMap.clear();
		flag = false;
		for (int j = 0; j<m; j++)
		{
			scanf("%d", &num);
			number.push_back(num);
		}
		if (m >= 3)
		{
			sort(number.begin(), number.end());
			for (int j = 0; j<m; j++)
			{
				numMap[number[j]] = j;
			}
			//设定左等式的长度从2到m-1
			for (int i = 2; i < m; i++)
			{
				DFS(0, 0, 0, i);
			}
		}

		if (!flag)
			cout << "Can't find any equations." << endl;
		cout << endl;
	}

	return 0;
}
