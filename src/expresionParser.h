/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "./scaner.h"
#include "./baseDeclarations.h"
#include "./stack.h"

typedef struct
{
    stack stack;
}expresionParserData;





token expresionDevelop(token actual,scanerData *sData) ;
bool isId(tokenType toCompere)  ;
bool isOperator(tokenType toCompere) ;
void reduction(stack *s);
void generateExpresion(token id1, token op ,token id2);

void expresionParse(token actual,scanerData *sData);
char getSymFromPrecTable(tokenType actual, tokenType head);
int  getPosInTable(tokenType toDecode);