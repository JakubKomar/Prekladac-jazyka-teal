/**
 * @brief   Expresion parsing
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "programData.h"

#include "./scaner.h"
#include "./baseDeclarations.h"
#include "./stack.h"

/**
 * main part of expresion parser
 * @param *sData data to operat whith
 */
tokenType expresionParse(systemData *sData,bool ignor);
/**
 * returning symbol from precedence table 
 * @param actual actual token on input
 * @param head top of stack
 */
char getSymFromPrecTable(tokenType actual, tokenType head);
/**
 * returning number of colm/line in prec. table
 * @param toDecode token to decode
 * @return number of colm/line in prec. table
 */
int  getPosInTable(tokenType toDecode);
/**
 * init data used by expresion parser
 * @param *data data to init
 */
void initExpresionData(expresionParserData *data);
/**
 * destruct data used by expresion parser
 * @param *data data to destruct
 */
void destructExpresionData(expresionParserData *data);
/**
 * returning next token from imput for use in expresion parser
 * @param separatorF 
 * @param *data eParser data
 * @return token for use in expresion parser
 */
token nextTokenExpParser(bool * separatorF,systemData * sData,bool firstT);
/**
 * checking if token is id or constant
 * @param *toCompere tokentype to kompre
 * @return true-if is ID,int,string,... false if isnt
 */
bool isConstant(tokenType toCompere);
/**
 * checking if token is operant
 * @param *data data to destruct
 * @return true-if is operator, false-if isnt
 */
bool isOperator(tokenType toCompere);
/**
 * reuduction of expresion
 * @param *s stack to operate whith
 */
void reduction(stack *s,bool ignor);
/**
 * generating expresion - WIP
 */
tokenType generateExpresion(token id1, token op ,token id2);