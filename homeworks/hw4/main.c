//	Libraries C
	
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
//#include <string.h>
int main()
{
  int size = 10;
 
  /* Stored in heap segment like other dynamically allocated things */
  char *str1 = (char *)malloc(sizeof(char)*size);
  *(str1+0) = 'a';
  *(str1+1) = 'b'; 
  *(str1+2) = 'c'; 
  *(str1+3) = '?';
  *(str1+4) = '?'; 
  *(str1+9) = 'f'; 
  *(str1+5) = '?';     
  *(str1+6) = '?';
  *(str1+7) = '2'; 
  *(str1+8) = '$';   
  *(str1+10) = '\0'; 
  char *str2 = (char *)malloc(sizeof(char)*size);
  *(str2+0) = 'q';
  *(str2+1) = 'w'; 
  *(str2+2) = 'g'; 
  *(str2+3) = 'c';
  *(str2+4) = 'b'; 
  *(str2+5) = '?';
  *(str2+6) = '?'; 
  *(str2+7) = '?'; 
  *(str2+8) = 'o';
  *(str2+9) = 'p'; 
  *(str2+10) = '\0'; 

  printf("\n\n");
  
  printf("strlen = %lu \n", my_strlen(str1));
  
  printf("\n\n");

  unsigned long spn = my_strspn(str1, str2);
  printf("%s\n%s\n", str1, str1+spn);
  printf("strspn = %lu \n", spn);

  printf("\n\n");

  char str[] ="What?????????a?fuck?isthis?";
  char * tok = my_strtok(str,"?");

  while (tok != NULL)
  {
    
    printf ("%s\n",tok);
    tok = my_strtok(NULL, "?");

  }

  printf("\n\n");

  my_strcat(&str1, str2);
  printf("%s\n", str1);

  printf("\n\n");

  printf("\n\n");
  free(str1);
  free(str2);
  return 0;
} 




