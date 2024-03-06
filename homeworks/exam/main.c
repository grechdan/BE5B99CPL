#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	if(argc == 4){
		
		char *line = NULL;
		size_t len = 0;
		int i = 0;
		int nread;
		int array_perm[20];
		printf("%s, %s, %s\n", argv[1], argv[2], argv[3]);
		
		FILE *PERMfp = fopen(argv[1], "r");
		
		while((nread = getline(&line, &len, PERMfp)) != 4){
		
               array_perm[i] = atoi(line);
               i++;
               
          }
          
          for(i = 0; i < 20; i++){
          		
          	printf("%i\n", array_perm[i]);// First permutation output
          	
          }
          
          printf("\n\n\n");
          
          char array_encr[140][20];
          FILE *ENCRfp = fopen(argv[2], "r");
          i = 0;
          int len_line = 0;
          
          while((nread = getline(&line, &len, ENCRfp)) != -1){
          		
          	if(nread > 1){	
          	
		     	for(int j = 0; j < nread - 1; j++){
		     	
		     		array_encr[i][j] = line[j];// Encrypted file input
		     	
		     	}
		    	
		    		i++;
		    		len_line = nread - 1;
          	
          	}
          	
          }
 
          int len_file = i;
          
          for(i = 0; i < len_file; i++){
          
          	for(int j = 0, k = 0; j < len_line; j++){
          	
          		if(array_encr[i][array_perm[j]] != 32){
          			
          			
          			printf("%c", array_encr[i][array_perm[j]]); // // Decrypted file input
          			k++;
          		}	
          		
          	}
          		
 			printf("\n");         	
 
          }
          
          int ch;
          char lang_word[20];
          i = 0;
          
          FILE *LANGfp = fopen(argv[3], "r");
          
          while((ch = getc(LANGfp)) != EOF){
          	
          	if(ch == 32){
          		
          		for(int j = 0; j < len_file; j++){
          		
          			//printf("fff");
          		
          		}
          		
          		i = 0;
          		char lang_word[20];
          		
          	
          	} else {
          		
          		lang_word[i] = ch;
          		i++;	
          	
          	}
          	
          
          
          } 
          
         
          
		fclose(PERMfp);
		fclose(ENCRfp);
		fclose(LANGfp);
		
		
	} else {
	
		printf("Error: wrong number of files");
		exit(1);	
		
	}
	
	return 0;
	
}
