/**
 * @brief   scaner
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include "baseDeclarations.h"

typedef struct {
    char curentSymbol;
    string fullToken;
    int line;
    int colum;
    int charCounter;
}scanerData;

typedef enum{       //stavy automatu laxikální analýzy 
    S_START,
    S_EOL,
    S_EOF,
    S_ERROR,
    S_UNDEFINATED,
}state;

tokenType getNextToken(scanerData * data);
state nextState(scanerData*data, state curentState);
void initScanerData(scanerData * data);
void loadChar(scanerData * data);