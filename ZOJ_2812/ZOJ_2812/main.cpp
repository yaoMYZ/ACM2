#include"stdio.h"

int main()
{
	char input;
	while ((input = getchar()) != EOF&&input!='#'){
		int account = 1;
		int sum = 0;
		if (input != ' ')
			sum = account*(input - 64);
		account++;
		while ((input = getchar()) != EOF&&input != '\n'){
			if (input != ' ')
				sum+= account*(input - 64);
			account++;
		}
		printf("%d\n", sum);
	}
	return 0;
}
