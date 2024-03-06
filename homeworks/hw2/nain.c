// Libraries C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Texts of errors

const char ERROR_OPRTR[] = "Error: wrong operator"; //Return value 2
const char ERROR_OPRNDS[] = "Error: wrong operands"; // Return value 3
const char ERROR_NUMDIG[] = "Error: wrong number of digits"; // Return value 4
const char ERROR_LENGTH[] = "Error: wrong length of operands or operator"; // Return value 5

// Calculator functions declaration

void OPRND (int operand[100], char buffer[100], int length);
void ADDITION (int operandFirst[100], int operandSecond[100], int lengthFirst, int lengthSecond, int result[100], int *lengthResult);
void SUBTRACTION (int operandFirst[100], int operandSecond[100], int lengthFirst, int lengthSecond, int result[100], int *lengthResult);
void NEGATION (int operand[100], int length);
void REVERSE(int array[100], int length);
void MULTIPLICATION (int operandFirst[100], int operandSecond[100], int lengthFirst, int lengthSecond, int result[100], int *lengthResult);

// Error functions declaration

void raiseNUMDIGerror (void);
void raiseOPRTRerror (void);
void raiseOPRNDSerror (void);
void raiseLENGTHerror (void);
void checkNUMDIGerror (int number);
void checkLENGTHerror (int number);

// main with all the main parts of the proram(INPUT, CALCULATION, OUTPUT)

int main(void){

	int operator;
	int operandFirst[100], operandSecond[100], result[200];
	int lengthFirst, lengthSecond, lengthResult;
    char buffer[101];
   	
    // INPUT into buffer and each line stores to it variable

    for (int i = 0; i < 5; i++){

    	scanf("%s", buffer);

    	if (i == 0) {

    		lengthFirst = atoi(buffer);
    		checkNUMDIGerror (lengthFirst);

    	} else if (i == 1){

			OPRND(operandFirst, buffer, lengthFirst);

    	} else if (i == 2){

    		operator = buffer[0];
    		checkLENGTHerror (buffer[1]);

    	} else if (i == 3){

    		lengthSecond = atoi(buffer);
    		checkNUMDIGerror (lengthSecond);

    	} else {

    		OPRND(operandSecond, buffer, lengthSecond);

    	}

    }
    // Begining of the CALCULATION

    if (operator == 42){

    	// MULTIPLICATION

    	memset(result, 0, sizeof(result));

    	if (operandFirst[0] > 0 && operandSecond[0] > 0){

    		MULTIPLICATION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

    	} else if (operandFirst[0] < 0 && operandSecond[0] < 0){

    		NEGATION (operandFirst, lengthFirst);
    		NEGATION (operandSecond, lengthSecond);
    		MULTIPLICATION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

    	} else {

    		if (operandFirst[0] < 0){

    			NEGATION (operandFirst, lengthFirst);
    			MULTIPLICATION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);


    		}

    		if (operandSecond[0] < 0){

    			NEGATION (operandSecond, lengthSecond);
				MULTIPLICATION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

    		}

    	}    	

    } else if (operator == 43){

    	// ADDITION

    	if ((operandFirst[0] > 0 && operandSecond[0] > 0) || (operandFirst[0] < 0 && operandSecond[0] < 0)){

  			if (lengthFirst >= lengthSecond){

    			ADDITION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);

    		} else {

    			ADDITION (operandSecond, operandFirst, lengthSecond, lengthFirst, result, &lengthResult);
    		}

    	} else {

    		if (operandFirst[0] < 0){

    			NEGATION (operandFirst, lengthFirst);
    			SUBTRACTION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
    			result[lengthResult - 1] = - result[lengthResult - 1];

    		}

    		if (operandSecond[0] < 0){

    			NEGATION (operandSecond, lengthSecond);
    			SUBTRACTION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
    			result[lengthResult - 1] = - result[lengthResult - 1];

    		}

    	}

    } else if (operator == 45){

    	// SUBTRACTION

    	if (operandFirst[0] > 0 && operandSecond[0] > 0){

    		if (lengthFirst > lengthSecond){

				SUBTRACTION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
    		
    		} else {

    			SUBTRACTION (operandSecond, operandFirst, lengthSecond, lengthFirst, result, &lengthResult);

    		}

    	} else if (operandFirst[0] < 0 && operandSecond[0] < 0){

    		NEGATION (operandFirst, lengthFirst);

    		NEGATION (operandSecond, lengthSecond);


    		if (lengthFirst > lengthSecond){

				SUBTRACTION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
    		
    		} else {

    			SUBTRACTION (operandSecond, operandFirst, lengthSecond, lengthFirst, result, &lengthResult);

    		}

    	} else {

    		if (operandSecond[0] < 0){

    			NEGATION (operandSecond, lengthSecond);
    			ADDITION (operandSecond, operandFirst, lengthSecond, lengthFirst, result, &lengthResult);
    			
    		}

    		if (operandFirst[0] < 0){

    			NEGATION (operandFirst, lengthFirst);
    			SUBTRACTION (operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
    			result[lengthResult - 1] = - result[lengthResult - 1];
    		}

    	}

    } else if (operator == 47){

    	// DIVISION

    	printf ("%s", "/");
    	
    } else {

    	raiseOPRTRerror ();
    	
    }

    // Result OUTPUT

    for (int i = lengthResult - 1; i >= 0; i--){

    	printf ("%i", result[i]);

    }

    printf("\n");

    return 0;

}

// Calculator functions 

// function which multiplies one operand by another one 

void MULTIPLICATION (int operandFirst[100], int operandSecond[100], int lengthFirst, int lengthSecond, int result[100], int *lengthResult){

	/*REVERSE (operandFirst, lengthFirst);
    REVERSE (operandSecond, lengthSecond);

	int i = 0;
	int j = 0;
	int carry = 0;

	for(i = 0;i < lengthSecond;i++){

        for(j = 0;j < lengthFirst;j++){

            result[i+j] += operandSecond[i] * operandFirst[j];
        }
    }

    for(i = 0;i < lengthFirst+lengthSecond;i++){

        carry = result[i] / 10;
        result[i] = result[i] % 10;
        result[i+1] = result[i+1] + carry;
    
    }
	*/
    
    int i = lengthSecond - 1;
	int j = lengthFirst - 1;
	int carry = 0;

	for(;i >= 0;i--){

        for(;j >= 0;j--){

            result[i+j] += operandSecond[i]*operandFirst[j];

        }

    }
    for(i = lengthFirst+lengthSecond;i > 0 ;i--){

        result[i] = (result[i] + carry) % 10;
        carry = result[i] / 10;
        
    }
 
 
    *lengthResult = lengthSecond + lengthFirst;

    //REVERSE (result, *lengthResult);

}

// function to reverse array

void REVERSE(int array[100], int length){

    int tempArray[100];
 
    for (int i = 0; i < length; i++) {

        tempArray[length - 1 - i] = array[i];
    
    }
 
    for (int i = 0; i < length; i++) {

        array[i] = tempArray[i];
    
	}
}

// function which changes all values of array to opposite 

void NEGATION (int operand[100], int length){

	for (int i = 0; i < length; i++){

		operand[i] = -operand[i];

	}

}

// function which substracts two operands

void SUBTRACTION (int operandFirst[100], int operandSecond[100], int lengthFirst, int lengthSecond, int result[100], int *lengthResult){

	int i = lengthFirst - 1;
	int j = lengthSecond - 1;
	int k = 0;
	int carry = 0;

	for (; i >= 0; i--, j--, k++){

		if (j >= 0){

			if ((operandFirst[i] - operandSecond[j] + carry) < 0){

				result[k] = (10 + operandFirst[i] - operandSecond[j] + carry) % 10;
				carry = -1;

			} else {

				result[k] = (operandFirst[i] - operandSecond[j] + carry) % 10;
				carry = 0;

			}

		} else {

			if ((operandFirst[i] + carry) < 0){

				result[k] = (10 + operandFirst[i] + carry) % 10;
				carry = -1;

			} else {

				result[k] = (operandFirst[i] + carry) % 10;
				carry = 0;

			}
		}

	}

	if (carry < 0){

		result[k] = -result[k];

	}

	*lengthResult = k; 

}

// function which sums up two operands 

void ADDITION (int operandFirst[100], int operandSecond[100], int lengthFirst, int lengthSecond, int result[100], int *lengthResult){

	int i = lengthFirst - 1;
	int j = lengthSecond - 1;
	int k = 0;
	int carry = 0;

	for (; i >= 0; i--, j--, k++){

		if (j >= 0){


			result[k] = (operandFirst[i] + operandSecond[j] + carry) % 10;
			carry = (operandFirst[i] + operandSecond[j] + carry) / 10;


		} else {

			result[k] = (operandFirst[i] + carry) % 10;
			carry = (operandFirst[i] + carry) / 10;

		}
	}
	if (carry > 0){

		result[k++] = carry;

	}

	*lengthResult = k;

}

// function which converts operand from char to int and stores in array

void OPRND (int operand[100], char buffer[100], int length){

	int k = 0;

	if (buffer[0] == 45){


    	for(int i = 1; i <= length; i++, k++){

    		if (-(buffer[i] - 48) >= -9 && -(buffer[i] - 48) <= 0){

    			operand[k] = -(buffer[i] - 48);

    		} else {

    			raiseOPRNDSerror ();
    		}
    	}

    	//checkLENGTHerror(buffer[length + 1]);

    } else {

	    for(int i = 0; i < length; i++, k++){

	    	if ((buffer[i] - 48) >= 0 && (buffer[i] - 48) <= 9){

    			operand[k] = buffer[i] - 48;
    			

    		} else {

    			raiseOPRNDSerror ();
    		}

	    }

		//checkLENGTHerror(buffer[length]);

	}


}

// Error functions

void checkNUMDIGerror(int number){

	if (number == 0) raiseNUMDIGerror();

}

void checkLENGTHerror(int number){

	if (number != 0 ) raiseLENGTHerror();

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



// New Version of the same shit(save)


// Libraries C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Calculator functions declaration

void ADDITION (int operandFirst[MAXBUFF - 1], int operandSecond[MAXBUFF - 1], int lengthFirst, int lengthSecond, int result[2 * (MAXBUFF - 1)], int *lengthResult);
void SUBTRACTION (int operandFirst[MAXBUFF - 1], int operandSecond[MAXBUFF - 1], int lengthFirst, int lengthSecond, int result[2 * (MAXBUFF - 1)], int *lengthResult);
void MULTIPLICATION (int operandFirst[MAXBUFF - 1], int operandSecond[MAXBUFF - 1], int lengthFirst, int lengthSecond, int result[2 * (MAXBUFF - 1)], int *lengthResult);


// Error functions declaration

void raiseNUMDIGerror (void);
void raiseOPRTRerror (void);
void raiseOPRNDSerror (void);
void raiseLENGTHerror (void);
void checkNUMDIGerror (int number);
void checkLENGTHerror (int number);



// MAIN with all the main parts of the proram(INPUT, CALCULATION, OUTPUT)

int main(void){

	int operator = 0;
	int operandFirst[MAXBUFF - 1], operandSecond[MAXBUFF - 1], result[2 * (MAXBUFF - 1)];
	int lengthFirst, lengthSecond, lengthResult;
    char buffer[MAXBUFF];
   	
    // INPUT into buffer and each line stores to it variable

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

	// OUTPUT of INPUT(to check)
	
	printf ("%i\n", lengthFirst);	
	
	for(int i = 0; i < lengthFirst; i++){

		printf ("%i", operandFirst[i]);

	}
	
	printf ("\n");	
	printf ("%i\n", operator);
	printf ("%i\n", lengthSecond);

	for(int i = 0; i < lengthSecond; i++){

		printf("%i", operandSecond[i]);

	}
	printf ("\n");

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
			MULTIPLICATION(operandFirst, operandSecond, lengthFirst, lengthSecond, result, &lengthResult);
			break;

		case 4:

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

void MULTIPLICATION(int operandFirst[MAXBUFF - 1], int operandSecond[MAXBUFF - 1], int lengthFirst, int lengthSecond, int result[2 * (MAXBUFF - 1)], int *lengthResult){

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
 
    *lengthResult = lengthSecond + lengthFirst;

}

// function which substracts two operands

void SUBTRACTION(int operandFirst[MAXBUFF - 1], int operandSecond[MAXBUFF - 1], int lengthFirst, int lengthSecond, int result[2 * (MAXBUFF - 1)], int *lengthResult){

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

void ADDITION(int operandFirst[MAXBUFF - 1], int operandSecond[MAXBUFF - 1], int lengthFirst, int lengthSecond, int result[2 * (MAXBUFF - 1)], int *lengthResult){

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

