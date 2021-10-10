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
#include "programData.h"

/**
 * inicialization function for parser data
 * @param *data data to incializate
*/ 
void systemDataInit(systemData * data);
/**
 * destruction function for parser data
 * @param *data data to destruction
*/ 
void systemDataDestruct(systemData * data);
/**
 * main part of parsing program
 * @param *data data set for parser
*/ 
void parserMain(systemData * data);
/**
 * simulating LL(1)table for parsing
 * @param *actualToken actual token on input 
 * @param *stack stack from parser to operate whith
*/ 
void useLLtable(token actualToken,stack *stack);
/**
 * error handeling from "useLLtable" function
 */
void LLerr();
void LLif(systemData *d);
void LLelse(systemData *d);
void LLreturn(systemData *d);
void LLreturnArgN(systemData *d);
void LLdeclaration(systemData *d);
void LLfuncDecParam(systemData *d);
void LLfuncDecNParam(systemData *d);
void LLfuncDecNRet(systemData *d);
void LLfuncDecNParam(systemData *d);

void LLwhile(systemData *d);
void LLfuncCall(systemData *d);
void LLprolog(systemData * d);
void LLprog(systemData * d);
void LLid(systemData *d);
void LLid_next(systemData * d);
void LLexp_or_func(systemData *d);
void LLfArg(systemData *d);
void LLfArgN(systemData *d);
void LLexpresionN(systemData *d);
token next(systemData *d);