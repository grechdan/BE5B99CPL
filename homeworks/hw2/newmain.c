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


const int ONE_MILLION[] = {0, 0, 0, 0, 0, 0, 1};
const int ONE_HUNDRED_THOUSAND[] = {0, 0, 0, 0, 0, 1};
const int TEN_THOUSAND[] = {0, 0, 0, 0, 1};
const int ONE_THOUSAND[] = {0, 0, 0, 1};
const int ONE_HUNDRED[] = {0, 0, 1};
const int TEN[] = {0, 1};
const int ONE[] = {1};

// INPUT functions declaration

void OPRTR(char buffer[MAXBUFF], int *operator);
void OPRND(char buffer[MAXBUFF], int length, int operand[length]);
void stringToArray(char buffer[MAXBUFF], int length, int operand[length], int startingPosition);

// Calculator functions declaration

void ADDITION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]);
void SUBTRACTION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]);
void MULTIPLICATION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]);
void DIVISION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]);

// Boolean functions

bool isGreater(int lengthFirst, int operandFirst[lengthFirst], int lengthResult, int result[2 * (MAXBUFF - 1)]);
bool isEqual(int lengthFirst, int operandFirst[lengthFirst], int lengthResult, int result[2 * (MAXBUFF - 1)]);

// Error functions declaration

void raiseNUMDIGerror (void);
void raiseOPRTRerror (void);
void raiseOPRNDSerror (void);
void raiseLENGTHerror (void);
void checkNUMDIGerror (int number);
void checkLENGTHerror (int number);


// MAIN with all the main parts of the proram(INPUT, CALCULATION, OUTPUT)

int main(void){

	// five INPUT lines are stored in five varibles via differen functions

    char buffer[MAXBUFF];
    int result[2 * (MAXBUFF - 1)];
	int lengthResult;

    int lengthFirst;
    scanf("%s", buffer);
    lengthFirst = atoi(buffer);
    checkNUMDIGerror (lengthFirst);

    int operandFirst[lengthFirst];
	scanf("%s", buffer);
	OPRND(buffer, lengthFirst, operandFirst);

	int operator;
	scanf("%s", buffer);
	OPRTR(buffer, &operator);

	int lengthSecond;
	scanf("%s", buffer);
	lengthSecond = atoi(buffer);
	checkNUMDIGerror (lengthSecond);

	int operandSecond[lengthSecond];
	scanf("%s", buffer);
	OPRND(buffer, lengthSecond, operandSecond);

	// Begining of the CALCULATION

	switch(operator){

		case 1:	// ADDITION

			ADDITION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);
			break;

		case 2:	// SUBTRACTION

			if(operandSecond[lengthSecond - 1] < 0){

				operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
				ADDITION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);

			} else {

				SUBTRACTION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);

			}

			break;

		case 3: // MULTIPLICATION

			memset(result, 0, lengthResult);

			if(operandSecond[lengthSecond - 1] > 0 && operandFirst[lengthFirst - 1] > 0){

				MULTIPLICATION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);

			} else if(operandSecond[lengthSecond - 1] < 0 && operandFirst[lengthFirst - 1] < 0){
				
				operandFirst[lengthFirst - 1] = -(operandFirst[lengthFirst - 1]);
				operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
				MULTIPLICATION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);
			
			} else {

				if(operandFirst[lengthFirst - 1] < 0){

					operandFirst[lengthFirst - 1] = -(operandFirst[lengthFirst - 1]);
					MULTIPLICATION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);

				} else {

					operandSecond[lengthSecond - 1] = -(operandSecond[lengthSecond - 1]);
					MULTIPLICATION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);
				}

			}

			break;

		case 4:	// DIVISION

			memset(result, 0, sizeof(result));
			DIVISION(lengthFirst, lengthSecond, operandFirst, operandSecond,  &lengthResult, result);
			break;

		default:

			raiseOPRTRerror();

	}

	for (int i = lengthResult - 1; i >= 0; i--){

    	printf ("%i", result[i]);

    }

    printf("\n");

	return 0;
}

// Calculator functions 

void DIVISION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]){

	if(isEqual(lengthFirst, operandFirst, *lengthResult, result) == false) printf("%s", "Fine");
	if(isEqual(lengthFirst, operandFirst, *lengthResult, result) == true) printf("%s", "Fine");
	/* // &(*lengthResult) == &temp_lengthResult yes/no/maybe
	
	int switcher = 2;
	int temp_lengthResult;
	int temp_result[2 * (MAXBUFF - 1)];

	while(isEqual(operandFirst, lengthFirst, result, &temp_lengthResult)  == false){

//		memset(temp_result, 0, sizeof(result));

		switch(switcher){

			case 7:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, ONE_MILLION, *lengthResult, 7, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, ONE_MILLION, *lengthResult, 7, result, &(*lengthResult));
					switcher--;

				}

				break;

			case 6:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, ONE_HUNDRED_THOUSAND, *lengthResult, 6, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, ONE_HUNDRED_THOUSAND, *lengthResult, 6, result, &(*lengthResult));
					switcher--;

				}

				break;

			case 5:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, TEN_THOUSAND, *lengthResult, 5, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, TEN_THOUSAND, *lengthResult, 5, result, &(*lengthResult));
					switcher--;

				}

				break;

			case 4:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, ONE_THOUSAND, *lengthResult, 4, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, ONE_THOUSAND, *lengthResult, 4, result, &(*lengthResult));
					switcher--;

				}

				break;

			case 3:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, ONE_HUNDRED, *lengthResult, 3, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, ONE_HUNDRED, *lengthResult, 3, result, &(*lengthResult));
					switcher--;

				}

				break;
			
			case 2:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, TEN, *lengthResult, 2, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, TEN, *lengthResult, 2, result, &(*lengthResult));
					switcher--;

				}

				break;

			case 1:

				if(isGreater(operandFirst, lengthFirst, temp_result, &temp_lengthResult)){

					ADDITION(result, ONE, *lengthResult, 1, result, &(*lengthResult));
					MULTIPLICATION(result, operandSecond, *lengthResult, lengthSecond, temp_result, &temp_lengthResult);

				} else {

					SUBTRACTION(result, ONE, *lengthResult, 1, result, &(*lengthResult));
					switcher--;

				}

				break;
		
		}

	}*/

}

bool isEqual(int lengthFirst, int operandFirst[], int lengthResult, int result[]){

	if(lengthFirst == lengthResult){

		for(int i = lengthFirst - 1; i >= 0;){

			if(operandFirst[i] == result[i]){

				i--;

			} else {

				return false;

			}

		}

		return true;

	} else {

		return false;

	}

}

bool isGreater(int lengthFirst, int operandFirst[], int lengthResult, int result[]){

	if(lengthFirst > lengthResult){

		return true;

	} else if(lengthFirst == lengthResult){

		for(int i = lengthFirst - 1; i >= 0;){

			if(operandFirst[i] == result[i]){

				i--;

			} else if(operandFirst[i] > result[i]){

				return true;

			} else {

				return false;

			}

		}

	} else {

		return false;

	}

}

void MULTIPLICATION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]){

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

void SUBTRACTION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]){

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

	for(*lengthResult = k - 1; *lengthResult >= 0; (*lengthResult)--){

    	if(result[*lengthResult] > 0) break;
    
    }
 	
    (*lengthResult)++;

}

// function which sums up two operands

void ADDITION(int lengthFirst, int lengthSecond, int operandFirst[lengthFirst], int operandSecond[lengthSecond], int *lengthResult, int result[2 * (MAXBUFF - 1)]){

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


// INPUT functions declaration

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

// function which fills operand array

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