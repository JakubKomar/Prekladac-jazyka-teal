/**
 * @brief   Dynamic string
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "baseDeclarations.h"

#define STRING_BASE_SIZE 16   //base size memory alocation of string

typedef struct
{
  unsigned int length;		// real len of string
  unsigned int capacity;	// alocatede len of string
  char* str;		          // pointer to string ended by '\0'
} string;


/**
 * string creation
 * @param *s string to init
 */
void stringInit(string *s);
/**
 * string destruction
 * @param *s string to destruction
 */
void stringDestruct(string *s);
/**
 * realocating string 2 size of previus
 * @param *s string to realocate
 */ 
void stringRealoc(string *s);
/**
 * hardcopy of string
 * @param *s1 string to copy
 * @param *s2 target string
 */ 
void stringCopy(string *s1, string *s2);
/**
 * clear string
 * @param *s1 to clearing
 */ 
void stringClear(string *s);
/**
 * add one charakter to end of string
 * @param *s1 string for clearing
 * @param c charakter to add
 */ 
void stringAddChar(string *s1, char c);
/**
 * add end character to string
 * @param *s string to end
 */ 
void addEnd(string *s);
/**
 * checking if string is full
 * @param *s string to check
 * @return true-is full false-not full
 */ 
bool stringFull(string *s1);

void stringAddString(string *s1, char *s2);