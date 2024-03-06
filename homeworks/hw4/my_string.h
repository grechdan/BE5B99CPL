//----------------------------------------------------------------------------------------
/**
 * \file       my_string.h
 * \author     Daniil Grechany
 * \date       2022/11/05
 * \brief      Simplified string library.
 *
 *  Simplified string library. Only a selected subset of string manipulation functions.
 *  They differ from the standard in certain parts like return vals and mutability of args.
 *	
 *	null-terminated byte string = NTBS
 *
*/
//----------------------------------------------------------------------------------------

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h>

/// Length null-terminated byte string
/**
  Returns the length of the given null-terminated byte string, that is,
  the number of characters in a character array whose first element is pointed to by str up to and not including the first null character.
 
  \param[in] str    pointer to NTBS
  \return  The length of NTBS str on success, zero if str is a null pointer.
*/
unsigned long my_strlen(const char *str);

/// Length of the maximum initial segment
/**
  Returns the length of the maximum initial segment (span) of NTBS pointed to by dest,
  that consists of only the characters found in NTBS pointed to by src.
 
  \param[in] dest    pointer to NTBS to be analyzed
  \param[in] src     pointer to NTBS that contains the characters to search for
  \return The length of the maximum initial segment that contains only characters from NTBS pointed to by src.
*/
unsigned long my_strspn(const char *dest, const char *src);

/// Finds the next token in a byte string
/**
  Finds the next token in a null-terminated byte string pointed to by str. The separator characters are identified by null-terminated byte string
  pointed to by delim. This function is designed to be called multiple times to obtain successive tokens from the same string.
 
    - If str is not a null pointer, the call is treated as the first call to strtok for this particular string.
      The function searches for the first character which is not contained in delim. 
      - If no such character was found, there are no tokens in str at all, and the function returns a null pointer.
        If such character was found, it is the beginning of the token. The function then searches from that point on
        for the first character that is contained in delim. 
        - If no such character was found, str has only one token, and future calls to strtok will return a null pointer
        - If such character was found, it is replaced by the null character '\0' and the pointer to the following character
          is stored in a static location for subsequent invocations. 
      - The function then returns the pointer to the beginning of the token 
 
    - If str is a null pointer, the call is treated as a subsequent call to strtok: the function continues from where it left
      in previous invocation. The behavior is the same as if the previously stored pointer is passed as str. 
 
  \param[in] str    pointer to NTBS to tokenize
  \param[in] delim         pointer to NTBS to copy from
  \return Returns pointer to the beginning of the next token or a null pointer if there are no more tokens.
*/
char *my_strtok(char *str, const char *delim);

/// String concatenation
/**
  Appends a copy of NTBS pointed to by src to the end of NTBS pointed to by dest.
  The character src[0] replaces the null terminator at the end of dest. The resulting byte string is null-terminated.
  The dest string will be reallocated if needed to fit the src string.
 
  \param[in,out] dest    pointer to NTBS to append to
  \param[in] src         pointer to NTBS identifying delimiters
*/
void my_strcat(char **dest, const char *src);

/// Substring matching
/**
  Finds the first occurrence of NTBS pointed to by substr in NTBS pointed to by str.
  The terminating null characters are not compared. The substr may contain the following subset of the regex syntax:
    []        - character groups
    [^]       - group prohibition
 
  \param[in] str         pointer to NTBS to examine
  \param[in] substr      pointer to NTBS to search for
  \param[out] begin      pointer to the beginning of the found substring or null pointer if not found
  \return The length of the found substring segment.
*/
unsigned long my_strstr_match(const char *str, const char *substr, const char **begin);

#endif // MY_STRING_H
