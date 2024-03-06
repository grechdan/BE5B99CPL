//	Libraries C
	
#include <stdio.h>
#include <stdlib.h>

// Errors texts

const char ERROR_MALLOC[] = "Error: memory not allocated.\n"; //Return value 2

// Structure for stor

typedef struct word{
	
	int* start;
	int length;

}word; 

// Program functions

void sort(struct word *words,unsigned int wordsCounter);
void swap(struct word *words, unsigned int i, unsigned int j);

// Error functions declaration

void checkMALLOCerror(void* ptr);
void raiseMALLOCerror (void);

// MAIN

int main(){

	// Input of first line with number of characters

	unsigned int numberOfChars;
	scanf("%u\n", &numberOfChars);

	// Allocation of memory for array of characters and for array which will hold stuctures of words

	int *string = (int*)malloc(numberOfChars * sizeof(int));
	checkMALLOCerror(string);
	struct word *words = (struct word*)malloc(sizeof(word));
	checkMALLOCerror(words);
	unsigned int wordsCounter = 1, length = 0;

	// INPUT

	// Input of characters into allocated memory one by one and at the same time filling array of stuctures
	// Array of stuctures holds pointers to the beginning of words and their lengths 

	for(unsigned int i = 0, j = 0; i <= numberOfChars; i++){

		string[i] = getchar();
		length++;

		if(i == 0){

			words[j].start = &string[i];

		} else if(string[i] == 32){

			wordsCounter++;
			words[j].length = length - 1;
			words = realloc(words, wordsCounter * sizeof(struct word));
			length = 0;
			j++;

		} else if(string[i - 1] == 32){

			words[j].start = &string[i];


		} else if(string[i] == 10){

			words[j].length = length - 1;

		}

	}

	// SORTING

	sort(words, wordsCounter);

	// OUTPUT

	for(unsigned int i = 0; i < wordsCounter; i++){

		for(unsigned int j = 0; j < words[i].length; j++){

			printf("%c", *(words[i].start + j));

		}
		printf("\n");

	}

	// freeing allocated memory

	free(words);
	free(string);

	return 0;

}

// Sorting function

void sort(struct word *words,unsigned int wordsCounter){

	for(unsigned int i = 0; i < wordsCounter - 1; i++){

		for(unsigned int j = i + 1; j < wordsCounter; j++){

			if(*(words[i].start) > *(words[j].start)){

				swap(words, i, j);

			} else if(*(words[i].start) == *(words[j].start)){

				for(unsigned int x = 1, y = 1; x < words[i].length || y < words[j].length;){

					if(x == words[i].length){

						break;

					} else if(y == words[j].length){

						swap(words, i, j);
						break;

					} else {

						if(*(words[i].start + x) > *(words[j].start + y)){

							swap(words, i, j);
							break;


						} else if(*(words[i].start + x) < *(words[j].start + y)){

							break;

						} else {

							x++;
							y++;

						}

					}

				}

			}

		}

	}

}

// Swapping function

void swap(struct word *words, unsigned int i, unsigned int j){

	int* tempstart = words[i].start;
	int templength = words[i].length;
	words[i].start = words[j].start;
	words[i].length = words[j].length;
	words[j].start = tempstart;
	words[j].length = templength;

}

// Error functions

void checkMALLOCerror(void* ptr){

	if(ptr == NULL) raiseMALLOCerror();

}


void raiseMALLOCerror(void){

	printf("%s\n", ERROR_MALLOC);
	exit(2);

}
