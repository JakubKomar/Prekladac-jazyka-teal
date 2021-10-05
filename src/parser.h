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
void LLTableErr();