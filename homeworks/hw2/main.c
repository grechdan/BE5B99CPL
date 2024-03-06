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

// Powers of TEN as arrays

/*static int ONE_MILLION[] = {0, 0, 0, 0, 0, 0, 1};
static int ONE_HUNDRED_THOUSAND[] = {0, 0, 0, 0, 0, 1};
static int TEN_THOUSAND[] = {0, 0, 0, 0, 1};
static int ONE_THOUSAND[] = {0, 0, 0, 1};
static int ONE_HUNDRED[] = {0, 0, 1};
static int TEN[] = {0, 1};*/
static int ONE[] = {1};

// INPUT functions declaration

void OPRTR(char buffer[], int *operator);
void OPRND(char buffer[], int length, int operand[]);
void stringToArray(char buffer[], int length, int operand[], int startingPosition);

// Calculator functions declaration

void ADDITION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult);
void SUBTRACTION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult);
void MULTIPLICATION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult);
//void DIVISION_small(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond);
void DIVISION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult);

// Boolean functions declaration

int isEqual(int operandFirst[], int lengthFirst, int operandSecond[], int lengthSecond);

// Error functions declaration

void raiseNUMDIGerror(void);
void raiseOPRTRerror(void);
void raiseOPRNDSerror(void);
void raiseLENGTHerror(void);
void checkNUMDIGerror(int number);
void checkLENGTHerror(int number);

// MAIN with all the main parts of the proram(INPUT, CALCULATION, OUTPUT)

int main(void){

	
	int result[2 * (MAXBUFF - 1)];
	int lengthResult;
    char buffer[MAXBUFF];
   	
    // INPUT into buffer and each line stores to it variable

	scanf("%s", buffer);
	int lengthFirst = atoi(buffer);
	checkNUMDIGerror (lengthFirst);

	scanf("%s", buffer);
	int operandFirst[lengthFirst];
	OPRND(buffer, lengthFirst, operandFirst);
    
    int operator = 0;
	scanf("%s", buffer);
	OPRTR(buffer, &operator);

	scanf("%s", buffer);
	int lengthSecond = atoi(buffer);
	checkNUMDIGerror (lengthSecond);

	scanf("%s", buffer);
	int operandSecond[lengthSecond];
	OPRND(buffer, lengthSecond, operandSecond);

	switch(operator){

		case 1:	// ADDITION

			ADDITION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
			break;

		case 2:	// SUBTRACTION

			if(operandSecond[lengthSecond - 1] < 0){

				operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
				ADDITION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

			} else {

				SUBTRACTION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

			}

			break;

		case 3: // MULTIPLICATION

			memset(result, 0, sizeof(result));

			if(operandSecond[lengthSecond - 1] > 0 && operandFirst[lengthFirst - 1] > 0){

				MULTIPLICATION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

			} else if(operandSecond[lengthSecond - 1] < 0 && operandFirst[lengthFirst - 1] < 0){

				operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
				operandFirst[lengthFirst - 1] = -(operandFirst[lengthFirst - 1]);
				MULTIPLICATION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

			} else {

				if(operandSecond[lengthSecond - 1] < 0){

					operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
					MULTIPLICATION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
					result[lengthResult - 1] = -(result[lengthResult - 1]);

				} else {

					operandFirst[lengthFirst - 1] = -(operandFirst[lengthFirst - 1]);
					MULTIPLICATION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
					result[lengthResult - 1] = -(result[lengthResult - 1]);

				}

			}

			break;

		case 4: // DIVISION

			//DIVISION_small(operandFirst, operandSecond, lengthFirst, lengthSecond);

			memset(result, 0, sizeof(result));
			lengthResult = 1;

			if(operandSecond[lengthSecond - 1] > 0 && operandFirst[lengthFirst - 1] > 0){

				DIVISION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

			} else if(operandSecond[lengthSecond - 1] < 0 && operandFirst[lengthFirst - 1] < 0){

				operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
				operandFirst[lengthFirst - 1] = -(operandFirst[lengthFirst - 1]);
				DIVISION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

			} else {

				if(operandSecond[lengthSecond - 1] < 0){

					operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
					DIVISION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
					result[lengthResult - 1] = -(result[lengthResult - 1]);

				} else {

					operandFirst[lengthFirst - 1] = -(operandFirst[lengthFirst - 1]);
					DIVISION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
					result[lengthResult - 1] = -(result[lengthResult - 1]);

				}

			}
			
			break;

		default:

			raiseOPRTRerror();

	}

	// OUTPUT of the result

	for (int i = lengthResult - 1; i >= 0; i--){

    	printf ("%i", result[i]);

    }

    printf("\n");

	return 0;
}

// Calculator functions 

// DIVISION

// Please check both versions which I uploaded, because this version will work even for big numbers, but it will take a lot of time
// In previous version I tried to make it a bit faster but it did not work out

void DIVISION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult){

	int temp_lengthResult = 0;
	int temp_result[2 * (MAXBUFF - 1)];

	while(isEqual(operandFirst, lengthFirst, temp_result, temp_lengthResult)  == 0){

		ADDITION(result, ONE, *lengthResult, 1, result, &(*lengthResult));
		memset(temp_result, 0, sizeof(temp_result));
		MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

	}

}

int isEqual(int operandFirst[], int lengthFirst, int operandSecond[], int lengthSecond){

	if(lengthFirst == lengthSecond){

		for(int i = lengthFirst - 1; i >= 0;){

			if(operandFirst[i] == operandSecond[i]){

				i--;

			} else {

				return 0;

			}

		}

		return 1;

	} else {

		return 0;

	}

}

// function which divides only small numbers

void DIVISION_small(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond){

	int powerOfTen = 1;
	int minflag = 1;

	int dividend = 0;

	for(int i = 0; i < lengthFirst; i++){

		if(operandFirst[i] > 0){

			dividend = dividend + (operandFirst[i] * powerOfTen);
			
		} else {

			dividend = dividend + (-(operandFirst[i]) * powerOfTen);
			minflag = -(minflag);

		}
	
		powerOfTen = powerOfTen * 10;
	
	}

	powerOfTen = 1;

	int divisor = 0;

	for(int i = 0; i < lengthSecond; i++){

		if(operandSecond[i] > 0){

			divisor = divisor + (operandSecond[i] * powerOfTen);

		} else {

			divisor = divisor + (-(operandSecond[i]) * powerOfTen);
			minflag = -(minflag);

		}

		powerOfTen = powerOfTen * 10;
	
	}

	int quotient = minflag * dividend / divisor; 

	printf("%i\n", quotient);
	exit(0);

}

// function which multiplies two operands

void MULTIPLICATION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult){

	for(int i = 0; i < lengthSecond; i++){

        for(int j = 0; j < lengthFirst; j++){

            result[i + j] += operandSecond[i] * operandFirst[j];
        
        }
    }

    int carry = 0;

    for(int i = 0; i < lengthFirst + lengthSecond; i++){

        carry = result[i] / 10;
        result[i] = result[i] % 10;
        result[i + 1] = result[i + 1] + carry;
    
    }
 
    for(*lengthResult = lengthFirst + lengthSecond; *lengthResult >= 0; (*lengthResult)--){

    	if(result[*lengthResult] > 0) break;

    }
 	
    (*lengthResult)++;

}

// function which substracts two operands

void SUBTRACTION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult){

	int carry = 0, k = 0;

	for (int i = 0, j = 0; i < lengthFirst || j < lengthSecond; i++, j++, k++){

		if(j >= lengthSecond){

			if ((operandFirst[i] + carry) < 0){

				result[k] = (10 + operandFirst[i] + carry) % 10;
				carry = -1;

			} else {

				result[k] = (operandFirst[i] + carry) % 10;
				carry = 0;

			}

		} else {

			if ((operandFirst[i] - operandSecond[j] + carry) < 0){

				result[k] = (10 + operandFirst[i] - operandSecond[j] + carry) % 10;
				carry = -1;

			} else {

				result[k] = (operandFirst[i] - operandSecond[j] + carry) % 10;
				carry = 0;

			}

		}

	}

	*lengthResult = k; 

}

// function which sums up two operands

void ADDITION(int operandFirst[], int operandSecond[], int lengthFirst, int lengthSecond, int result[], int *lengthResult){

	int carry = 0, k = 0;

	for(int i = 0, j = 0; i < lengthFirst || j < lengthSecond; i++, j++, k++){

		if(i >= lengthFirst){

			result[k] = (operandSecond[j] + carry) % 10;
			carry = (operandSecond[j] + carry) / 10;


		} else if(j >= lengthSecond){

			result[k] = (operandFirst[i] + carry) % 10;
			carry = (operandFirst[i] + carry) / 10;

		} else {

			result[k] = (operandFirst[i] + operandSecond[j] + carry) % 10;
			carry = (operandFirst[i] + operandSecond[j] + carry) / 10;

		}
	}

	if(carry > 0){

		result[k++] = carry;

	}

	*lengthResult = k;

}

// function which makes operator from string

void OPRTR(char buffer[], int *operator){

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

void OPRND(char buffer[], int length, int operand[]){

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

void stringToArray(char buffer[], int length, int operand[], int startingPosition){

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