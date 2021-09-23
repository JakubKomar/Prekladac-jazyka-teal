/**
 * @brief   scaner
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "scaner.h"

tokenType getNextToken(scanerData * data)
{
    state curentState=S_START;
    state prevState=S_UNDEFINATED;
    stringClear(&(data->fullToken));
   
    while(curentState!=S_ERROR){

        prevState=curentState;
        curentState=nextState(data,curentState);
        if(curentState==S_EOF)
            break;
        loadChar(data);
    }
    return prevState;
}

state nextState(scanerData*data, state curentState)
{
    char sym=data->curentSymbol;
    state next;
    switch (curentState)
    {
        case S_START:
            if(isLetter(sym)||sym=='_'){
                next=S_ID;}
            else if(sym=='-'){
                next=S_SUB;}
            else if(sym=='+'){
                next=S_ADD;}
            else if(sym=='/'){
                next=S_DIV;}   
            else if(sym=='*'){
                next=S_MUL;} 
            else if(sym=='='){
                next=S_ASSIGEN;}  
            else if(sym=='~'){
                next=S_NOT_EQ1;}  
            else if(sym=='<'){
                next=S_LT;} 
            else if(sym=='>'){
                next=S_GT;} 
            else if(sym==')'){
                next=S_RBR;} 
            else if(sym=='('){
                next=S_LBR;} 
            else if(sym==':'){
                next=S_COLON;} 
            else if(sym==','){
                next=S_COMMA;}
            else if(sym=='\n'){
                next=S_EOL;}  
            else if(sym==EOF){
                next=S_EOF;} 
            else if(sym==' '||sym=='\t'){
                next=S_SPACE;} 
            else if(sym=='\"'){
                next=S_STR1;} 
            else if(sym>='1'&&sym<='9'){
                next=S_INT;} 
            else if(sym=='0'){
                next=S_INT0;}
        break;
        case S_SUB:
            if(sym=='-'){
                next=S_LINE_COM;}
        break;
        case S_LINE_COM:
            if(sym=='['){
                next=S_LINE_COM_2;} 
            else if(sym!='\n'||sym!=EOF){
                next=S_LINE_COM_PER;} 
        break;
        case S_LINE_COM_PER:
            if(sym!='\n'||sym!=EOF){
                next=S_LINE_COM_PER;} 
        break;
        case S_LINE_COM_2:
            if(sym=='['){
                next=S_BLOCK_COM;} 
            else if(sym!='\n'||sym!=EOF){
                next=S_LINE_COM_PER;} 
        break;
        case S_BLOCK_COM:
            if(sym==']'){
                next=S_BLOCK_COM2;}
            else if(sym!=EOF){
                next=S_BLOCK_COM;}     
        break;
        case S_BLOCK_COM2:
            if(sym==']'){
                next=S_BLOCK_COM3;}
            else if(sym!=EOF){
                next=S_BLOCK_COM;}     
        break;
        case S_DIV:
            if(sym=='/'){
                next=S_DIV2;}
        break;
        case S_ASSIGEN:
            if(sym=='='){
                next=S_EQ;}
        break;
        case S_NOT_EQ1:
            if(sym=='='){
                next=S_NOT_EQ2;}
        break;
        case S_LT:
            if(sym=='='){
                next=S_LTE;}
        break;
        case S_GT:
            if(sym=='='){
                next=S_GTE;}
        break;
        case S_EOL:
            if(sym=='\n'){
                next=S_EOL;}
        break;              
        case S_SPACE:
            if(sym==' '||sym=='\t'){
                next=S_SPACE;}
        break;
        case S_STR1:
            if(sym=='\\'){
                next=S_ESC1;}
            else if(sym=='\"'){
                next=S_STR2;}
            else if(sym>31){
                next=S_STR1;}
        break;
        case S_ESC1:
            if(sym=='\"'||sym=='n'||sym=='t'||sym=='\\'){
                next=S_STR1;}
            else if(sym=='2'){
                next=S_ESC2;}
            else if(sym=='0'||sym=='1'){
                next=S_ESC4;}
        break;
        case S_ESC2:
            if(sym=='5'){
                next=S_ESC3;}
            else if(sym>='0'&&sym<='4'){
                next=S_ESC5;}
        break;
        case S_ESC3:
            if(sym>='0'&&sym<='5'){
                next=S_STR1;}
        break;
        case S_ESC4:
            if(isDecimal(sym)){
                next=S_ESC5;}
        break;
        case S_ESC5:
            if(isDecimal(sym)){
                next=S_STR1;}
        break;
        case S_INT:
            if(sym=='.'){
                next=S_DOUBLE1;}
            else if(sym=='e'||sym=='E'){
                next=S_EXP1;}
            else if(isDecimal(sym)){
                next=S_INT;}
        break;
        case S_INT0:
            if(isDecimal(sym)){
                next=S_TRAP;}
            else if(sym=='e'||sym=='E'){
                next=S_EXP1;}
            else if(sym=='.'){
                next=S_DOUBLE1;}
        break;
        case S_DOUBLE1:
            if(isDecimal(sym)){
                next=S_DOUBLE2;}
        break;
        case S_DOUBLE2:
            if(isDecimal(sym)){
                next=S_DOUBLE2;}
            else if(sym=='e'||sym=='E'){
                next=S_EXP1;}
        break;
        case S_EXP1:
            if(isDecimal(sym)){
                next=S_EXP3;}
            else if(sym=='+'||sym=='-'){
                next=S_EXP2;}
        break;
        case S_EXP2:
            if(isDecimal(sym)){
                next=S_EXP3;}
        break;
        case S_EXP3:
            if(isDecimal(sym)){
                next=S_EXP3;}
        break;
        default:
            break;
    }
    return next;
}

bool isLetter(char toCompare)
{
    return (toCompare>='a'&&toCompare<='z') || (toCompare>='A'&&toCompare<='Z');
}

bool isDecimal(char toCompare)
{
    return toCompare>='0'&&toCompare<='9';
}

void initScanerData(scanerData * data)
{
    data->charCounter=0;
    data->colum=0;
    data->line=0;
    stringInit(&(data->fullToken));
    loadChar(data);
} 

void loadChar(scanerData * data)
{
    data->curentSymbol=fgetc(INPUT);
    data->charCounter++;
    if(data->curentSymbol=='\n')
    {
        data->colum=0;
        data->line++;
    }
    else
        data->colum++;
    stringAddChar(&(data->fullToken),data->curentSymbol);
}
