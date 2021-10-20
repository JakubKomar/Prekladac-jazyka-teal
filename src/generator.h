/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include "baseDeclarations.h"
#include "symtable.h"
void genereteProgramHeader();
void genVar(STData * data,char * id);
void genInst(char * inst);
void genFuncHeader(STData * data,char * id);
void genFuncFoter(STData * data,char * id);
void genReturn();