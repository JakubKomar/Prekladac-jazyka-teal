/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include "baseDeclarations.h"
#include "symtable.h"
#include "programData.h"
void genereteProgramHeader();
void genVar(unsigned long int decor,char * id);
void genInst(char * inst);
void genFuncHeader(STData * data,char * id);
void genFuncFoter(STData * data,char * id);
void genReturn();
unsigned long int genIfHeader(systemData *d,tokenType expT);
void genIfFoter(unsigned long int decor);
unsigned long int genWhileSlabel(systemData *d);
void genWhileHeader(unsigned long int decor,tokenType expT);
void genWhileFoter(unsigned long int decor);
void genWhileDecJump(systemData *d);
void genWhileDecFLUSH(systemData *d,unsigned long int decor);
void genJumpExpresion(tokenType expT);
void genElseHeader(unsigned long int decor);
void genElseFoter(unsigned long int decor);