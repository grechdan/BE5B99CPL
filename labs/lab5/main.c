#include <stdio.h>

struct person{

	int id;
	char firstName[25];
	char lastName[25];
	int age;

};

int main(){

	FILE *pFile;

    pFile = fopen("myText.txt", "w");
    if(pFile == NULL){
        
        printf("Failed to open file\n");
    
    }

    char fname[25];
    char lname[25];
    int age;

    for(unsigned int i = 1; i <= 2; i++){

    	for(unsigned int j = 0; j < 3; j++){

    		if(j == 0){

    			printf("Write a first name of person:");
    			scanf("%s", fname);

    		} else if(j == 1){

    			printf("Write a last name of person:");
    			scanf("%s", lname);

    		} else if(j == 2){

    			printf("Write an age of person:");
    			scanf("%u", &age);

    		}

    	}
    	struct person finput = {i, fname, lname, age};
    	fwrite(&finput, sizeof(struct person), 1, pFile);
    }

    fclose(pFile);
	return 0;

}