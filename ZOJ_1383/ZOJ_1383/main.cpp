#include"stdio.h"
#include"stdlib.h"

int main()
{
	int lines=0;
	scanf_s("%d", &lines);
	for (size_t i = 0; i < lines; i++)
	{
		int input=0;
		int account = 0;
		scanf_s("%d", &input);
		while (input>0){
			int remainder = input % 2;
			input /= 2;
			if (remainder == 1)
				printf("%d ", account);
			account++;
		}
		printf("\n");
	}
	system("pause");
	return 0;
}