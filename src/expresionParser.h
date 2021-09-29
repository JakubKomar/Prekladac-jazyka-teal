/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "./scaner.h"
#include "./baseDeclarations.h"
#include "./library/stack.h"

tokenType expresionDevelop(tokenType actual,scanerData *sData) ;
bool isId(tokenType toCompere)  ;
bool isOperator(tokenType toCompere) ;


void expresionParse(tokenType actual,scanerData *sData);
char getSomething(tokenType actual, tokenType head);
int getOrderInTable(tokenType toDecode);