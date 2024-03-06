# include <stdio.h>
# include <string.h>

void try(int *a);

int main(){

	int a = 0;

	try(&a);
	try(&a);

	printf("%i\n", a);

}


void try(int *a){
	printf("%p\n", a);
	//*a = 1;
	(*a)++;
	printf("%p\n", a);
	// int i = *a
	// i++;
	// a* = i;

}