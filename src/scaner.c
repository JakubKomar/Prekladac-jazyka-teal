/**
 * @brief   scaner
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "scaner.h"

tokenType getNextToken(scanerData * data){
    state curentState=S_START;
    state prevState=S_UNDEFINATED;
    strClear(&(data->fullToken));
   
    while(curentState!=S_ERROR || curentState!=S_EOF){
        prevState=curentState;
        curentState=nextState(data,curentState);
        loadChar(data);
    }
    return prevState;
}
state nextState(scanerData*data, state curentState){
    char aux=data->curentSymbol;
    state next;
    switch (curentState)
    {
    case S_START:
        if(aux==EOF){
            next=S_EOF;
        }
        break;
    
    default:
        break;
    }
    return next;
}
void initScanerData(scanerData * data){
    data->charCounter=0;
    data->colum=0;
    data->line=0;
    loadChar(data);
} 
void loadChar(scanerData * data){
    data->curentSymbol=fgetc(INPUT);
    data->charCounter++;
    if(data->curentSymbol=='\n'){
        data->colum=0;
        data->line++;
    }
    else
        data->colum++;
    strInit(&(data->fullToken));
}
