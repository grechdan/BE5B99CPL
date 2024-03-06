#include <stdio.h>
#include <stdlib.h>

struct LTI{

	int index;
	int amount;

};

int compare(const void *x, const void *y){

	struct LTI a = *(struct LTI *)x;
	struct LTI b = *(struct LTI *)y;

	return b.amount - a.amount;
}

int main(int argc, char *argv[]){



	if(argc == 2){

		printf("%s", argv[1]);
		
		FILE *fp = fopen(argv[1], "r");
		
		struct LTI lti[256];
		int ch;


		for(int i = 0; i < 256; i++){

			lti[i].index = i;
			lti[i].amount = 0;

		}

		while((ch = getc(fp)) != EOF){

			char x = ch;

			if(x >= 'a' && x <= 'z') lti[ch].amount++;

		}

		qsort(lti, 256, sizeof(struct LTI), compare);


		for(int i = 0; i < 256; i++){

			char x = lti[i].index;
			if(x >= 'a' && x <= 'z') printf("%c", x);

		}

		fclose(fp);
	}


	return 0;
}