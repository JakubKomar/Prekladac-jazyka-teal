/**
 * @brief   Dynamic string libary
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include <string.h>
#include <malloc.h>
typedef struct
{
  char* str;		// misto pro dany retezec ukonceny znakem '\0'
  int length;		// skutecna delka retezce
  int allocSize;	// velikost alokovane pameti
} string;

/**
 * string creation
 * @return 0-success,1-error
 */
int strInit(string *s);

/**
 * string destruction
 */
void strFree(string *s);

/**
 * hardcopy of string
 * @param string to clearing
 * @return 0-success,1-error
 */ 
int strCopyString(string *s1, string *s2);

/**
 * clear string
 * @param string to clearing
 */ 
void strClear(string *s);

/**
 * add one charakter to end of string
 * @param *s1-string for modification
 * @param c-charakter to add
 */ 
int strAddChar(string *s1, char c);

/**
 * add string to end of string
 * @param *s1-string for modification
 * @param *s2-string which will be added to end
 */ 
int strAddString(string *s1, char *s2);

