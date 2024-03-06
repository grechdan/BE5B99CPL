#include <stdio.h>


int main(){
	
	int total = 0;
	printf("Enter the number:");
	int number;
	scanf("%d", &number);

	total= total + number;

	while(number != 0){

		printf("%d",total);
		scanf("%d", &number);
		total= total + number;
	}

	return 0;
}