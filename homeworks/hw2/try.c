// Libraries C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXBUFF 101



// Texts of errors

const char ERROR_OPRTR[] = "Error: wrong operator"; //Return value 2
const char ERROR_OPRNDS[] = "Error: wrong operands"; // Return value 3
const char ERROR_NUMDIG[] = "Error: wrong number of digits"; // Return value 4
const char ERROR_LENGTH[] = "Error: wrong length of operands or operator"; // Return value 5


// INPUT functions declaration

void OPRTR(char buffer[MAXBUFF], int *operator);
void OPRND(char buffer[MAXBUFF], int length, int operand[length]);
void stringToArray(char buffer[MAXBUFF], int length, int operand[length], int startingPosition);


int isEqual(int operandFirst[MAXBUFF - 1], int lengthFirst,  int operandSecond[MAXBUFF - 1], int *lengthSecond);

const int ONE_MILLION[] = {0, 0, 0, 0, 0, 0, 1};
void raiseNUMDIGerror (void);
void raiseOPRTRerror (void);
void raiseOPRNDSerror (void);
void raiseLENGTHerror (void);
void checkNUMDIGerror (int number);
void checkLENGTHerror (int number);




int main(void){

	int operator = 0;
	int operandFirst[MAXBUFF - 1], operandSecond[MAXBUFF - 1];
	int lengthFirst, lengthSecond;
	char buffer[MAXBUFF];


	for(int i = 0; i < 5; i++){

    	scanf("%s", buffer);

    	if(i == 0) {

    		lengthFirst = atoi(buffer);
    		checkNUMDIGerror (lengthFirst);

    	} else if(i == 1){

			//operandFirst[lengthFirst];
			OPRND(buffer, lengthFirst, operandFirst);
		
    	} else if(i == 2){

    		OPRTR(buffer, &operator);

    	} else if(i == 3){

    		lengthSecond = atoi(buffer);
    		checkNUMDIGerror (lengthSecond);


    	} else if(i == 4){

    		//operandSecond[lengthSecond];
    		OPRND(buffer, lengthSecond, operandSecond);

    	}

	}

	if(isEqual(operandFirst, lengthFirst, operandSecond, &lengthSecond)){

		printf("%s", "TRUE");
		printf("%li", sizeof(ONE_MILLION));


	} else {

		printf("%s", "False");

	}
	
	return 0;

}



int isEqual(int operandFirst[MAXBUFF - 1], int lengthFirst, int operandSecond[MAXBUFF - 1], int *lengthSecond){

	if(lengthFirst > *lengthSecond){

		return 1;

	} else if(lengthFirst == *lengthSecond){

		for(int i = lengthFirst - 1; i >= 0;){

			if(operandFirst[i] == operandSecond[i]){

				i--;

			} else if(operandFirst[i] > operandSecond[i]){

				return 1;

			} else {

				return 0;

			}

		}

	} else {

		return 0;

	}
	
	return 0;

}























// function which makes operator from string

void OPRTR(char buffer[MAXBUFF], int *operator){

    checkLENGTHerror(buffer[1]);

    if(buffer[0] == 42){

    	*operator = 3;	// MULTIPLICATION

    } else if (buffer[0] == 43){

    	*operator = 1;	// ADDITION

    } else if (buffer[0] == 45){

		*operator = 2;	// SUBTRACTION    	

    } else if (buffer[0] == 47){

    	*operator = 4; // SUBTRACTION
    	
    } else {

    	raiseOPRTRerror();
    	
    }

}

// function which makes operand array

void OPRND(char buffer[MAXBUFF], int length, int operand[length]){

	int startingPosition = 0;

	if (buffer[0] == 45){

		checkLENGTHerror(buffer[length + 1]);
		startingPosition = 1;
    	stringToArray(buffer, length, operand, startingPosition);
    	operand[length - 1] = -(operand[length - 1]);

    } else {

    	checkLENGTHerror(buffer[length]);
	    stringToArray(buffer, length, operand, startingPosition);

	}

}

// function which converts string into operand written backwards and stores as array of ints

void stringToArray(char buffer[MAXBUFF], int length, int operand[length], int startingPosition){

	int j = 0;

	for (int i = length + startingPosition - 1; i >=  startingPosition; i--, j++){

    	if((buffer[i] - 48) >= 0 && (buffer[i] - 48) <= 9){

			operand[j] = buffer[i] - 48;

		} else {

			raiseOPRNDSerror();
		}

	}

}



// Error functions

void checkNUMDIGerror(int number){

	if(number == 0) raiseNUMDIGerror();

}

void checkLENGTHerror(int number){

	if(number != 0) raiseLENGTHerror();

}

void raiseNUMDIGerror(void){

	printf("%s\n", ERROR_NUMDIG);
   	exit(4);

}

void raiseOPRNDSerror(void){

	printf("%s\n", ERROR_OPRNDS);
   	exit(3);

}

void raiseOPRTRerror(void){

	printf("%s\n", ERROR_OPRTR);
	exit(2);

}

void raiseLENGTHerror(void){

	printf("%s\n", ERROR_LENGTH);
	exit(5);

}
