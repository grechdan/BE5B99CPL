
#include <stdio.h>
#include <stdlib.h>

int main(){

	FILE *language, *encoded;
	int LTIlanguage[256], LTIencoded[256];
	int ch;

	language = fopen("/home/grechdan/Documents/CPL2/labs/test_prep/language.txt", "r");
	encoded = fopen("/home/grechdan/Documents/CPL2/labs/test_prep/encoded.txt", "r");

	printf("%i\n", LTIlanguage[1]++);
	printf("%i\n", LTIlanguage[2]);
	printf("%i\n", LTIlanguage[3]);

	for(int i = 0; i < 256; i++){

		LTIlanguage[i] = 0;

	}
	
	while((ch = getc(language)) != EOF){

		
		LTIlanguage[ch]++;

	}



	



	fclose(language);
	return 0;

}
