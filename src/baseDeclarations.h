/**
 * Implementace překladače imperativního jazyka IFJ21
 * @brief  basic declaration for all part of program + error handeling functions
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <setjmp.h>

#define INPUT stdin

jmp_buf errorHandelingJump; /** jump for error handeling-part of simulated try catch block **/

/**
 * @brief bassic error massege-description from code, after report exit
 * @param code error code
*/
void error(int code);

/**
 * @brief error massege whith additon description -description from code after report exit
 * @param code error code
 * @param *description aditional description of error
*/
void errorD(int code,char * description);

/**
 * @brief from code printing error massege
 * @param code error code
*/
void printError(int code);


//začátek převzaté části 

//debugovací makro získáno z https://stackoverflow.com/questions/1644868/define-macro-for-debug-printing-in-c 
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

/*konec převzaté části*/