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

/**
 * main function of program-called first
 * function:parsing arguments, allocating resorses, call parser, hendeling errors
 * @param argc count of arguments
 * @param argv full text arguments
 */
int main(int argc, char** argv);
/**
 * parsing arguments
 * @param argc count of arguments
 * @param argv full text arguments
 */
void argParse(int argc, char** argv);
/**
 * debuging tools/special runs for debuging
 * @param flags flags to identifi special run
 */
void debugRun(bool scanerOnly,bool expresionOnly);
