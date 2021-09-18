#include "baseDeclarations.h"

void error(int code)
{
    if(code){
        printError(code);
        exit(code);
    } 
}

void errorD(int code,char * description)
{
    if(code){
        printError(code);
        fprintf(stderr,"More detailes: %s",description);
        exit(code);
    } 
}

void printError(int code)
{
    char * text;
    switch (code)
    {
    case 1:
        text="Very long description of error ........";
        break;
    
    default:
        text="Unknown error";
    }
    fprintf(stderr,"Error: %s\n",text);
}

