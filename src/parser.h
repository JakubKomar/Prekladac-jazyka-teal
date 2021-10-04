/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include "baseDeclarations.h"
#include "scaner.h"
#include "expresionParser.h"
#include "stack.h"

typedef struct {
    stack stack;
    token actualToken;   
}parserData;


typedef struct {
    scanerData sData;
    parserData pData;
    expresionParserData epData;
    //memory model
}systemData;



void systemDataInit(systemData * data);
void LLTableErr();
void parserMain();
void useLLtable(token actualToken,stack *stack);