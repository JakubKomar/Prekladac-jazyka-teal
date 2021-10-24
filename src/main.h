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
 * @brief main function of program-called first
 * function:parsing arguments, allocating resorses, call parser, hendeling errors
 * @param argc count of arguments
 * @param argv full text arguments
 */
int main(int argc, char** argv);

/**
 * @brief parsing arguments
 * @param argc count of arguments
 * @param argv full text arguments
 */
void argParse(int argc, char** argv);