#include <stdio.h>
#include <stdlib.h>

//function with recursevly searches greates common divisor

int gcd(int firstNumber, int secondNumber){
    
    //if second number equals 0 then return first number as a result

    if (secondNumber == 0){
        
        return firstNumber;    

   //otherwise function calls itself and cheks other values

    } else {
        
        return gcd(secondNumber, firstNumber % secondNumber);
        
    }
   
}

//main function contains input and output of data with several checkup conditions

int main(){
    
    static int numerator;
    static int denominator;
    static char sign;
    static char divisionSign = '/';
    
    scanf("%i %c %i", &numerator, &sign, &denominator);
    
    // Zero division condition 
    
    if (denominator == 0){
    
    	printf("Zero division error!\n");
    	exit(EXIT_FAILURE);
    
    }
    
    // Wrong sign condition
    
    if (sign != divisionSign){
    
    	printf("Wrong sign error!\n");
    	exit(EXIT_FAILURE);
    
    }
    		
    int greatestCommonDivisor = gcd(numerator, denominator);
    printf("%i %c %i\n", numerator / greatestCommonDivisor, sign, denominator / greatestCommonDivisor);

    return 0;
}
