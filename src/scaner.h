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

typedef enum{   //typy tokenů
  
    //neterminály
    N_START,

    T_ERR,      //nesmí nastat // ze scenru se nevypíše
    T_UNIMPORTANT,//token nebude zapsán do listu-není důležitý // ze scenru se nevypíše
}tokenType;

tokenType getNextToken(scanerData * data);
state nextState(scanerData*data, state curentState);
void initScanerData(scanerData * data);
void loadChar(scanerData * data);