/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "parser.h"

void parserMain(){
    scanerData scData;
    tokenType actualToken=N_START;
    initScanerData(&scData);
    while (1)
    {
        getNextToken(&scData);
    }
    
}