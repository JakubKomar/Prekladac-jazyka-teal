/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "./scaner.h"
#include "./baseDeclarations.h"
#include "./stack.h"

tokenType expresionDevelop(tokenType actual,scanerData *sData) ;
bool isId(tokenType toCompere)  ;
bool isOperator(tokenType toCompere) ;
void reduction(stack *s);
void generateExpresion(tokenType id1, tokenType op ,tokenType id2);

void expresionParse(tokenType actual,scanerData *sData);
char getSymFromPrecTable(tokenType actual, tokenType head);
int  getPosInTable(tokenType toDecode);