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


void systemDataInit(systemData * data);
void systemDataDestruct(systemData * data);
void LLTableErr();
void parserMain(systemData * data);
void useLLtable(token actualToken,stack *stack);