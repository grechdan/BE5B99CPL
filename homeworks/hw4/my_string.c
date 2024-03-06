//  null-terminated byte string = NTBS

#include "my_string.h"

/// Length null-terminated byte string
/**
  Function gets the pointer to the first byte of NTBS
  and iterates it in the loop with the counter, 
  till the value of pointer equals to the NT character.
  Function returns counter as the output of the function.

  \param[in] str    pointer to NTBS
  \return  The length of NTBS str on success, zero if str is a null pointer.
*/
unsigned long my_strlen(const char *str){

  unsigned long len;

  for(len = 0; *(str + len) != '\0'; len++);

  return len;

}

/// Length of the maximum initial segment
/**
  Function gets two pointers, which are address to the first bytes of NTBS.
  In the first loop, the flag is set to 0 in the begining of every itteration.
  In the second loop, the equality of the values of pointers is checked,
  if they are equal, then the value of flag is set to 1 and the cycle breaks.
  After iteration of the second loop, the value of flag is checked, 
  if the flag is set to 1, the leght of span increases, otherwise the first cycle breaks.
 
  \param[in] dest    pointer to NTBS to be analyzed
  \param[in] src     pointer to NTBS that contains the characters to search for
  \return The length of the maximum initial segment that contains only characters from NTBS pointed to by src.
*/
unsigned long my_strspn(const char *dest, const char *src){

  unsigned long lenSpan = 0;
 
  for(unsigned long i = 0; *(dest + i) != '\0'; i++){
 
    unsigned flag = 0;
 
    for(unsigned long j = 0; *(src + j) != '\0'; j++){
 
      if(*(dest + i) == *(src + j)){
 
        flag = 1;
        break;
 
      }
 
    }
 
    if(flag == 1){
 
      lenSpan++;
 
    } else {
 
      break;
 
    }
 
  }
 
  return lenSpan;

}

/// Finds the next token in a byte string
/**
  Function gets two pointers, which are address to the first bytes of NTBS.
  First of all, the value of str is stored to the buffer,
  the the first byte of the buffer is checked not to be NT, otherwise function returns NULL.
  The value of buffer is stored to token. The first loop iterates pointers of buffer.
  In the second loop, the second pointer is iterated and checked if is equals to the value of buffer.
    
  \param[in] str    pointer to NTBS to tokenize
  \param[in] delim         pointer to NTBS to copy from
  \return Returns pointer to the beginning of the next token or a null pointer if there are no more tokens.
*/
char *my_strtok(char *str, const char *delim){

  static char* buffer;

  if(str != NULL){

    buffer = str;

  }

  if(buffer[0] == '\0'){

    return NULL;

  }

  char* token = buffer;

  for(char* b = buffer; *b !='\0'; b++){
    
    for(unsigned long i = 0; *(delim + i) != '\0'; i++){
    
      if(*b == *(delim + i)) {
    
        *b = '\0';
        buffer = b+1;

        if(b != token){

          return token;

        } else {

          token++;

        }

      }
    
    }

  }

  return token;

}

/// String concatenation
/**
  Function gets two pointers, which are address to the first bytes of NTBS.
  With the help of the function my_strlen() lengths of dest and src are stored into two unsigned long integers.
  After dest is reallocated to the new size of memory, sum of two lengths.
  And second NTBS is appended to the first in the cycle.
 
  \param[in,out] dest    pointer to NTBS to append to
  \param[in] src         pointer to NTBS identifying delimiters
*/
void my_strcat(char **dest, const char *src){
  
  unsigned long lenDest = my_strlen(*dest);
  unsigned long lenSrc = my_strlen(src);
  *dest = (char *)realloc(*dest, (lenDest + lenSrc + 1) * sizeof(char));

  for(unsigned long i = 0; *(src + i) != '\0'; i++){

    *(*dest + lenDest + i) = *(src + i);

  }

  *(*dest + lenDest + lenSrc + 1) = '\0';

}

unsigned long my_strstr_match(const char *str, const char *substr, const char **begin){

  // TODO

}


  