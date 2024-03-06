#include<stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {

    if (argc < 2) {
    
    	printf("Input_Error\n");
    	
    	return 0;
    }
    else {
    
    	int n = atoi(argv[1]);
    
    	int totnum = (n*n + n)/2;
    
    	int count = 0;
    
    	for(int i = totnum; i > 0; i--) {
    	
            printf("*");
            count += 1;
            if(count == n) {
            
            	printf("\n");
            	n -= 1;
            	count = 0;
            }
    	}
    	return totnum;
    }
}
