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
    K_BOOL,
    //other
    O_DOLAR,
    O_HANDLE,   //begining of handle
    O_NONE,
    O_ERR,      //error state
    O_UNIMPORTANT,//token isnt importat for function of code
    S_EXPRESION,
    //neterminals for expresion analysis
    NE_EXP,
}tokenType;

#include "symtable.h"
typedef struct {
    char* id;
    unsigned long int decor;
}varId;
typedef struct {
    tokenType type;
    tokenType typeOfValue;  //for usege in expresion part
    varId *id;  //storing whole id 
}token;

/**
 * returning string name of token for debuging purporse
 * @param type token type for string converzion
 * @return string name of token
*/
char * tokenStr(token type);
