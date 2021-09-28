/**
 * @brief  basic declaration for all part of program
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#include "library/dstring.h"
#include "tokens.h"
#define INPUT stdin

//začátek převzaté části 
//debugovací makro získáno z https://stackoverflow.com/questions/1644868/define-macro-for-debug-printing-in-c 
#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif
#define debug(fmt, ...) \
            do { if (DEBUG_TEST) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
#define debugS(fmt) \
            do { if (DEBUG_TEST) fprintf(stderr, fmt); } while (0)
//konec převzaté části



/**
 * bassic error massege-description from code, after report exit
 * @param code error code
*/
void error(int code);
/**
 *  error massege whith additon description -description from code after report exit
 * @param code error code
 * @param *description aditional description of error
*/
void errorD(int code,char * description);
/**
 *  from code printing error massege
 * @param code error code
*/
void printError(int code);