/**
 * @brief  basic declaration 
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include "library/dstring.h"
#define INPUT stdin




void error(int code);
void errorD(int code,char * description);
void printError(int code);