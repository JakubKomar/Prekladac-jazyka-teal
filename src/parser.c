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
    
    stack stack;
    stackInit(&stack);
    stackPush(&stack,N_START);

    while (stackEmpty(&stack))
    {
        if(stackHead(&stack)==N_START)//pokud neterminál
        {
            useLLtable(actualToken,&stack);
        }
        else
        {
            if(stackHead(&stack)==actualToken)
            {
                stackPop(&stack);
                getNextToken(&scData);
            }
            else
            {
                errorD(32,"Terminál na zásabníku se neschoduje s aktuálním terminálem");
            }
        }
    }   
}

void useLLtable(tokenType actualToken,stack *stack) 
{
    switch (stackPop(stack))
    {
    case N_START:
        switch (actualToken)
        {
        case T_ASSIGEN:
            stackPush(stack,T_ASSIGEN);   //použití pravidla
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