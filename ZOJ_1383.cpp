#include"stdio.h"

int main()
{
	int lines=0;
	scanf("%d", &lines);
	while(lines--)
	{
		long input=0;
		int account = 0;
		int flag=0;
		scanf("%d", &input);
		while (input>0){
			int remainder = input % 2;
			input /= 2;
			if (remainder == 1){
                if(flag==0){
                    printf("%d", account);
                    flag++;
                }else{
                    printf(" %d", account);
                }
			}
			account++;
		}
		printf("\n");
	}
	return 0;
}
