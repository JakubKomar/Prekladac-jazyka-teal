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
 * @brief inicialization function for parser data
 * @param *data data to incializate
*/ 
void systemDataInit(systemData * data);

/**
 * @brief destruction function for parser data
 * @param *data data to destruction
*/ 
void systemDataDestruct(systemData * data);

/**
 * @brief main part of parsing program
 * @param *data data for parser
*/ 
void parserMain(systemData * data);

/**
 * @brief definition of function 
 * @param *data data for parser
*/ 
void LLfunction(systemData *d);

/**
 * @brief simulating nonterminal for function N parameter
 * @param *d system data
 * @param checkOnly function is declareted-only check
 * @param argNum pozition of argument
 * @param *Fdata function data from symtable
 */
void LLfuncArg(systemData *d,bool checkOnly,int argNum,STData * Fdata);

/**
 * @brief simulating nonterminal for function N retutn parameter
 * @param *d system data
 * @param checkOnly function is declareted-only check
 * @param argNum pozition of argument
 * @param *Fdata function data from symtable
 */
void LLreturnArg(systemData *d,bool checkOnly,int argNum,STData * Fdata);

/**
 * @brief simulating nonterminal for if/else structure
 * @param *d system data
 * @param *fData data of function in witch is this structure
 */
void LLif(systemData *d,STFuncData *fData);

/**
 * @brief simulating nonterminal for else structure
 * @param *d system data
 * @param *fData data of function in witch is this structure
 * @param decorId decorator form if statement
 */
void LLelse(systemData *d,STFuncData *fData,unsigned long int decorId);

/**
 * @brief simulating nonterminal for return
 * @param *d system data
 * @param *fData data of function in witch is this structure
 */
void LLreturn(systemData *d,STFuncData *fData);

/**
 * @brief simulating nonterminal for N return args
 * @param *d system data
 * @param *fData data of function in witch is this structure
 * @param order pozition of argument
 */
void LLreturnArgN(systemData *d,STFuncData *fData,int order);

/**
 * @brief simulating nonterminal for declaration function/var
 * @param *d system data
 */
void LLdeclaration(systemData *d);

/**
 * @brief simulating nonterminal for declaration arg in fucntion
 * @param *d system data
 * @param *fData data of function in witch is this structure
 * @param checkOnly function is declareted-only check
 */
void LLfuncDecParam(systemData *d,STData *funcData,bool checkOnly);

/**
 * @brief simulating nonterminal for declaration N args in fucntion
 * @param *d system data
 * @param *funcData data of function in witch is this structure
 * @param argNum pozition of argument
 * @param checkOnly function is declareted-only check
 */
void LLfuncDecNParam(systemData *d,STData *funcData,int argNum,bool checkOnly);

/**
 * @brief simulating nonterminal for declaration retrun arg in fucntion
 * @param *d system data
 * @param *funcData data of function in witch is this structure
 * @param argNum pozition of argument
 * @param checkOnly function is declareted-only check
 */
void LLfuncDecNRet(systemData *d,STData *funcData,int argNum,bool checkOnly);

/**
 * @brief simulating nonterminal for while structure
 * @param *d system data
 * @param *funcData data of function in witch is this structure
 */
void LLwhile(systemData *d,STFuncData *fData);

/**
 * @brief simulating nonterminal for function call
 * @param *d system data
 * @param numOfAsigens how much parameters is assigent to this fuction call 0-N
 */
int LLfuncCall(systemData *d,int numOfAsigens);

/**
 * @brief simulating nonterminal for header of program
 * @param *d system data
 */
void LLprolog(systemData * d);

/**
 * @brief simulating nonterminal for main body of program
 * @param *d system data
 * @param *funcData data of function in witch is this structure
 */
void LLprog(systemData * d,STFuncData *fData);

/**
 * @brief simulating nonterminal for id asigen
 * @param *d system data
 */
void LLid(systemData *d);

/**
 * @brief simulating nonterminal for next id asigen
 * @param *d system data
 * @param order pozition of id
 */
void LLid_next(systemData * d,int order); 

/**
 * @brief simulating nonterminal for asigen behind equlation
 * @param *d system data
 * @param numOfAsigens how much parameters is assigent to this fuction call 0-N
 */
void LLexp_or_func(systemData *d,int numOfAsigens);

/**
 * @brief simulating nonterminal for  parameter in function call
 * @param *d system data
 * @param order pozition of argument
 * @param *Fdata function data from symtable
 */
void LLfArgN(systemData *d,int order,STData * Fdata);
/**
 * simulating nonterminal for N expresion behind assigen
 * @param *d system data
 * @param numOfAsigens how much ids is behind assigeb
 */
void LLexpresionN(systemData *d,int numOfAsigens);

/**
 * @brief function for easy geting of tokens from scanner
 * @param *d system data
 */
token next(systemData *d);

/**
 * @brief error handeling for syntax checks 
 */
void LLerr();

/**
 * @brief  function for chenging scope of program typicaly when entering to if/else, while 
 * @param *d system data
 * @param IsFunc true-if chenging scope due to entering to function definition
 */
void changeRangeScope(systemData * d,bool IsFunc);

/**
 * @brief decoratin id 
 * @param *d system data
 * @param toDecorate symtable data of var
 */
void decorId(systemData * data,STData * toDecorate);

/**
 * @brief checking compabilyty between assigen
 * @param a first type
 * @param b second type
 */
void assigenCompCheck(tokenType a,tokenType b,bool isAsigen);