/**
 * @brief   data structures for mains part of program
 *
 * @authors Jakub Komárek (xkomar33)
 */


#pragma once
#include "baseDeclarations.h"
#include "scaner.h"
#include "stack.h"
#include "dstring.h"

typedef struct {
    token actualToken;   
    frameStack dataModel;
}parserData;

typedef struct
{
    stack stack;
}expresionParserData;

typedef struct {
    scanerData sData;
    parserData pData;
    expresionParserData epData;
    STSymbolPtr symTable;
}systemData;

