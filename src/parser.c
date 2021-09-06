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
    
    pStack stack;
    StackInit(&stack);
    StackPush(stack,N_START);

    while (emptyStack(stack))
    {
        if(StackHead(stack)==N_START)//pokud neterminál
        {
            useLLtable(actualToken,stack);
        }
        else
        {
            if(StackHead(stack)==actualToken)
            {
                StackPop(stack);
                getNextToken(&scData);
            }
            else
            {
                errorD(32,"Terminál na zásabníku se neschoduje s aktuálním terminálem");
            }
        }
    }   
}

void useLLtable(tokenType actualToken,pStack stack) 
{
    switch (StackPop(stack))
    {
    case N_START:
        switch (actualToken)
        {
        case T_ASSIGEN:
            StackPush(stack,T_ASSIGEN);   //použití pravidla
            break;
        
        default:
            errorD(32,"Pro daný neterminál nebyl nalezen rozklad");
            break;
        }
        break;
    
    default:
        errorD(32,"Pro daný neterminál nebyl nalezen rozklad");
        break;
    }
}