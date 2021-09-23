/**
 * @brief   tokens for translator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "baseDeclarations.h"
typedef enum{   //typy tokenů
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
    //neterminály
    N_START,
    //ostatní
    O_HANDLE,   //začátek handle
    O_DOLAR,
    O_ERR,      //nesmí nastat // ze scenru se nevypíše
    O_UNIMPORTANT,//token nebude zapsán do listu-není důležitý // ze scenru se nevypíše
}tokenType;

char * tokenStr(tokenType type);