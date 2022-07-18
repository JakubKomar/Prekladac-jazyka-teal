/**
 * Implementace překladače imperativního jazyka IFJ21
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
 * @brief string creation
 * @param *s string to init
 */
void stringInit(string *s);

/**
 * @brief string destruction
 * @param *s string to destruction
 */
void stringDestruct(string *s);

/**
 * @brief realocating string to biger size  
 * @param *s string to realocate
 */ 
void stringRealoc(string *s);

/**
 * @brief hardcopy of string
 * @param *s1 string to copy
 * @param *s2 target string
 */ 
void stringCopy(string *s1, string *s2);

/**
 * @brief clear string
 * @param *s1 to clearing
 */ 
void stringClear(string *s);

/**
 * @brief add one charakter to end of string
 * @param *s1 string for clearing
 * @param c charakter to add
 */ 
void stringAddChar(string *s1, char c);

/**
 * @brief add end character to string
 * @param *s string to end
 */ 
void addEnd(string *s);

/**
 * @brief checking if string is full
 * @param *s string to check
 * @return true-is full false-not full
 */ 
bool stringFull(string *s1);

/**
 * @brief copy Dstring whith malloc
 * @param *s Dstring to copy
 * @return pointer to allocated string
 */ 
char* stringCpyToChPtr(string *s);

/**
 * @brief copy string whith malloc
 * @param *s string to copy
 * @return pointer to allocated string
 */ 
char* strdup (const char* s);