/**
 * @brief   tokens for translator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "baseDeclarations.h"

//types of token
typedef enum{   
    T_ID,
    T_SUB,
    T_ADD,
    T_DIV,
    T_DIV2,
    T_MUL,
    T_STR_LEN,
    T_ASSIGEN,
    T_EQ,
    T_NOT_EQ,
    T_LT,
    T_LTE,
    T_GT,
    T_GTE,
    T_RBR,
    T_LBR,
    T_COLON,
    T_COMMA,
    T_EOF,
    T_STR,
    T_INT,
    T_DOUBLE,
    T_DOT2,
    T_FUNC_CALL,
    //keywords
    K_DO,
    K_ELSE,
    K_END,
    K_FUNCTION,
    K_GLOBAL,
    K_IF,
    K_LOCAL,
    K_NIL,
    K_READ,
    K_REQUIRE,
    K_RETURN,
    K_THEN,
    K_WHILE,
    K_WRITE,

    K_INTEGER,
    K_STRING,
    K_NUMBER,
    //ostatní
    O_HANDLE,   //začátek handle
    O_DOLAR,
    O_ERR,      //nesmí nastat // ze scenru se nevypíše
    O_UNIMPORTANT,//token nebude zapsán do listu-není důležitý // ze scenru se nevypíše
    S_EXPRESION,
    //neterminály
    N_START,
    N_PROLOG,
    N_PROG,
    N_EXP_OR_FUNC,
    N_FUNC_CALL,
    N_F_ARG,
    N_F_ARG_N,
    N_ID_NEXT,
    N_EXPRESIONS,
    N_WHILE,
    N_IF,
    N_ELSE_M,
    N_FUNCTION,
    N_ARG,
    N_ARGNEXT,
    N_RETURN_D,
    N_RETURN_DN,
    N_RETURN,
    N_RETURN_ARG,
    N_RETURN_ARG_N,
    N_DECLARATION,
    N_DECLARATION_T,
    N_ARG_D,
    N_ARG_DN,
    N_RET_D,
    N_RET_DN,
    N_ASSIGEN_MAY,
    N_TYPE,
    N_RANGE,
}tokenType;


/**
 * returning string name of token for debuging purpose
 * @param type token type for string converzion
 * @return string name of token
*/
char * tokenStr(tokenType type);