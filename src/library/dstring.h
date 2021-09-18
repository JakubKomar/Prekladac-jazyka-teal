/**
 * @brief   Dynamic string libary
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "./../baseDeclarations.h"

#define STR_BASE_LEN 8   //base size memory alocation of string


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
void strInit(string *s);
/**
 * string destruction
 */
void strFree(string *s);
/**
 * realocating string 2 size of previus
 * @param *s-string to realocate
 * @return 0-success,1-error
 */ 
int realocate(string *s);
/**
 * hardcopy of string
 * @param string to clearing
 */ 
void strCopyString(string *s1, string *s2);
/**
 * clear string
 * @param string to clearing
 */ 
void strClear(string *s);
/**
 * add one charakter to end of string
 * @param *s1-string for clearing
 * @param c-charakter to add
 */ 
void strAddChar(string *s1, char c);
/**
 * add string to end of string
 * @param *s1-string for modification
 * @param *s2-string which will be added to end
 */ 
void strAddString(string *s1, char *s2);

