/** 
 * Implementace překladače imperativního jazyka IFJ21
 * @brief   Expresion parsing
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "programData.h"

#include "./scaner.h"
#include "./generator.h"
#include "./baseDeclarations.h"
#include "./stack.h"

/**
 * @brief main part of expresion parser
 * @param *sData data to operat whith
 * @param ignor true-will not be generated, false-will be generated
 * @return type of resulting the expresion -INT,NUMBER,STRING...
 */
tokenType expresionParse(systemData *sData);

/**
 * @brief returning symbol from precedence table 
 * @param actual actual token on input
 * @param head top of stack
 * @return symbol from table
 */
char getSymFromPrecTable(tokenType actual, tokenType head);

/**
 * @briefreturning number of colm/line in prec. table
 * @param toDecode token to decode
 * @return number of colm/line in prec. table
 */
int  getPosInTable(tokenType toDecode);

/**
 * @brief init data used by expresion parser
 * @param *data data to init
 */
void initExpresionData(expresionParserData *data);

/**
 * @brief destruct data used by expresion parser
 * @param *data data to destruct
 */
void destructExpresionData(expresionParserData *data);

/**
 * @brief returning next token from imput for use in expresion parser
 * @param separatorF aux var for recognizing end of expresion
 * @param *data eParser data
 * @return token for use in expresion parser
 */
token nextTokenExpParser(bool * separatorF,systemData * sData,bool firstT);

/**
 * @brief checking if token is id or constant
 * @param *toCompere tokentype to kompre
 * @return true-if is ID,int,string,... false if isnt
 */
bool isConstant(tokenType toCompere);

/**
 * @brief checking if token is operant
 * @param *data data to destruct
 * @return true-if is operator, false-if isnt
 */
bool isOperator(tokenType toCompere);

/**
 * @brief reuduction of expresion
 * @param ignor true-will not be generated, false-will be generated
 * @param *s stack to operate whith
 */
void reduction(stack *s);

/**
 * @brief generating expresion - for example id2+id1
 * @param id1 first value
 * @param op1 operation
 * @param id2 second value
 * @return type of resulting the expresion -INT,NUMBER,STRING...
 */
tokenType generateExpresion(token id1, token op ,token id2);