/**
 * @brief   main
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include "baseDeclarations.h"
#include "scaner.h"
#include "parser.h"
#include "expresionParser.h"
void debugRun(bool scanerOnly,bool expresionOnly);
void argParse(int argc, char** argv);