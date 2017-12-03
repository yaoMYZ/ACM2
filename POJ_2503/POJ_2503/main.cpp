#include <iostream>
#include <string>
#include <cstdio>
#include <map>
using namespace std;



int main()
{
	char jude;
	char *firstWord = NULL;
	char *secondWord = NULL;
	//ÉùÃ÷Í¼
	map<string, string> wordMap;
	while ((jude = getchar()) != '\n'){
		firstWord=new char[11];
		secondWord=new char[11];

		firstWord[0] = jude;
		int reg1 = 1;
		while ((jude = getchar()) != ' '){
			firstWord[reg1++] = jude;
		}
		firstWord[reg1] = '\0';
		int reg2 = 0;
		while ((jude = getchar()) != '\n'){
			secondWord[reg2++] = jude;
		}
		secondWord[reg2] = '\0';
		wordMap.insert(make_pair(secondWord, firstWord));

	}
	char findWord[11];
	while (cin>>findWord){
		map<string, string>::iterator mi = wordMap.find(findWord);
		if (mi!=wordMap.end()){
			cout << mi->second << endl;
		}
		else
		{
			printf("eh\n");
		}


	}
	
	system("pause");
	return 0;
}
