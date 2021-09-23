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
    S_ID,
    S_SUB,
    S_LINE_COM,
    S_LINE_COM_2,
    S_LINE_COM_PER,
    S_BLOCK_COM,
    S_BLOCK_COM2,
    S_BLOCK_COM3,
    S_ADD,
    S_DIV,
    S_DIV2,
    S_MUL,
    S_STR_LEN,
    S_ASSIGEN,
    S_EQ,
    S_NOT_EQ1,
    S_NOT_EQ2,
    S_LT,
    S_LTE,
    S_GT,
    S_GTE,
    S_RBR,
    S_LBR,
    S_COLON,
    S_COMMA,
    S_EOL,
    S_EOF,
    S_SPACE,
    S_STR1,
    S_STR2,
    S_ESC1,
    S_ESC2,
    S_ESC3,
    S_ESC4,
    S_ESC5,
    S_INT,
    S_INT0,
    S_TRAP,
    S_DOUBLE1,
    S_DOUBLE2,
    S_EXP1,
    S_EXP2,
    S_EXP3,
    S_ERROR,
    S_UNDEFINATED,
}state;
bool isLetter(char toCompare);
bool isDecimal(char toCompare);
tokenType getNextToken(scanerData * data);
state nextState(scanerData*data, state curentState);
void initScanerData(scanerData * data);
void loadChar(scanerData * data);