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
#include "symtable.h"
#include "programData.h"
#include "generator.h"
#include <string.h>
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
 * simulating nonterminal for function definition
 * @param *d system data
 */
void LLfunction(systemData *d);
/**
 * simulating nonterminal for function N parameter
 * @param *d system data
 */
void LLfuncArgN(systemData *d);
/**
 * simulating nonterminal for function parameter
 * @param *d system data
 */
void LLfuncArg(systemData *d,bool checkOnly,int argNum,STData * Fdata);
/**
 * simulating nonterminal for function return parameters
 * @param *d system data
 */
void LLreturnArg(systemData *d,bool checkOnly,int argNum,STData * Fdata);
/**
 * simulating nonterminal for if/else structure
 * @param *d system data
 */
void LLif(systemData *d,STFuncData *fData);
/**
 * simulating nonterminal for else structure
 * @param *d system data
 */
void LLelse(systemData *d,STFuncData *fData,unsigned long int decorId);
/**
 * simulating nonterminal for return
 * @param *d system data
 */
void LLreturn(systemData *d,STFuncData *fData);
/**
 * simulating nonterminal for N return args
 * @param *d system data
 */
void LLreturnArgN(systemData *d,STFuncData *fData,int order);
/**
 * simulating nonterminal for declaration function/var
 * @param *d system data
 */
void LLdeclaration(systemData *d);
/**
 * simulating nonterminal for declaration arg in fucntion
 * @param *d system data
 */
void LLfuncDecParam(systemData *d,STData *funcData,bool checkOnly);
/**
 * simulating nonterminal for declaration N args in fucntion
 * @param *d system data
 */
void LLfuncDecNParam(systemData *d,STData *funcData,int argNum,bool checkOnly);
/**
 * simulating nonterminal for declaration retrun arg in fucntion
 * @param *d system data
 */
void LLfuncDecNRet(systemData *d,STData *funcData,int argNum,bool checkOnly);
/**
 * simulating nonterminal for while structure
 * @param *d system data
 */
void LLwhile(systemData *d,STFuncData *fData);
/**
 * simulating nonterminal for function call
 * @param *d system data
 */
int LLfuncCall(systemData *d,int numOfAsigens);
/**
 * simulating nonterminal for header of program
 * @param *d system data
 */
void LLprolog(systemData * d);
/**
 * simulating nonterminal for main body of program
 * @param *d system data
 */
void LLprog(systemData * d,STFuncData *fData);
/**
 * simulating nonterminal for id asigen
 * @param *d system data
 */
void LLid(systemData *d);
/**
 * simulating nonterminal for next id asigen
 * @param *d system data
 */
void LLid_next(systemData * d,int order); 
/**
 * simulating nonterminal for asigen behind equlation
 * @param *d system data
 */
void LLexp_or_func(systemData *d,int numOfAsigens);
/**
 * simulating nonterminal for  
 * @param *d system data
 */
void LLfArg(systemData *d);
/**
 * simulating nonterminal for 
 * @param *d system data
 */
void LLfArgN(systemData *d,int order,STData * Fdata);
/**
 * simulating nonterminal for 
 * @param *d system data
 */
void LLexpresionN(systemData *d,int numOfAsigens);
/**
 * simulating nonterminal for 
 * @param *d system data
 */
token next(systemData *d);
/**
 * error handeling from "useLLtable" function
 */
void LLerr();
void changeRangeScope(systemData * d,bool IsFunc);
void decorId(systemData * data,STData * toDecorate);
void assigenCompCheck(tokenType a,tokenType b);