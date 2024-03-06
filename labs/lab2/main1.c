#include <stdio.h>


int main(){
	
	int total = 0;
	printf("Enter the number:");
	int number;
	scanf("%d", &number);

	total= total + number;

	do{

		printf("%d",total);
		scanf("%d", &number);
		total= total + number;
		
	}while(total <= 25);

	return 0;
}