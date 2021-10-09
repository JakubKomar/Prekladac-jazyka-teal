/**
 * @brief  basic declaration for all part of program + error handeling functions
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
#include <setjmp.h>
#include <io.h>

FILE *fp;
#ifdef VCODE
#define INPUT fp
#else
#define INPUT stdin
#endif

jmp_buf errorHandelingJump; /** jump for error handeling-part of simulated try catch block **/

/** začátek převzaté části 
 *  debugovací makro získáno z https://stackoverflow.com/questions/1644868/define-macro-for-debug-printing-in-c */
#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif
/*debuging makro fprintf whith aditional parameters*/
#define debug(fmt, ...) \
    do { if (DEBUG_TEST) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
/*debuging makro fprintf whithout aditional parameters*/
#define debugS(fmt) \
    do { if (DEBUG_TEST) fprintf(stderr, fmt); } while (0)
/**konec převzaté části**/


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