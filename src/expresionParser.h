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



void destructExpresionData(expresionParserData *data);
void initExpresionData(expresionParserData *data);
token expresionDevelop(token actual,scanerData *sData) ;
bool isId(tokenType toCompere)  ;
bool isOperator(tokenType toCompere) ;
void reduction(stack *s);
void generateExpresion(token id1, token op ,token id2);

void expresionParse(systemData *sData);
char getSymFromPrecTable(tokenType actual, tokenType head);
int  getPosInTable(tokenType toDecode);