/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "expresionParser.h"


void expresionParse(tokenType actual,scanerData *sData)
{
    pStack stack;
    StackInit(&stack);
    StackPush(stack,O_DOLAR);

    while (StackHead(stack)==O_DOLAR&&actual==O_DOLAR)
    {
        switch (getSomething(actual,StackHead(stack)))
        {
        case '=':
            StackPush(stack,actual);
            actual=getNextToken(sData);
            break;
        case '<':
            StackPush(stack,O_HANDLE);
            StackPush(stack,actual);
            actual=getNextToken(sData);
            break; 
        case '>':
            //reduction
            while (StackHead(stack)!=O_HANDLE)
            {
                StackPop(stack);
            }
            
            break;
        case ' ':
            errorD(99,"syntax error");
            break;
        default:
            errorD(99,"precedence table error");
            break;
        }
    }
    


    StackDestruct(&stack);
} 
char getSomething(tokenType actual, tokenType head)
{
    int colum=getOrderInTable(head);
    int row=getOrderInTable(actual);
    return precTable[row][colum];

}

int getOrderInTable(tokenType toDecode)
{
    switch (toDecode)
    {
    case T_ADD:
        return 0;
    case T_SUB:
        return 1;  
    case T_MUL:
        return 2;    
    case T_DIV:
        return 3;
    case T_LT:
        return 4;   
    case T_GT:
        return 5;
    case T_LTE:
        return 6;  
    case T_GTE:
        return 7;    
    case T_EQL:
        return 8;
    case T_NEQ:
        return 9;
    case T_LBR:
        return 10;           
    case T_RBR:
        return 11;
    case T_ID:
        return 12;  
    case O_DOLAR:
    default:
        return 13;  
    }
}
/*T_RBR,      //pravá závorka
    T_LBR,      //levá závorka
    T_GT,       //>
    T_GTE,      //>=
    T_LT,       //>
    T_LTE,      //<=
    T_NEQ,      //   !=
    T_ASSIGEN,  // =
    T_EQL,      //  ==
    T_DIV,      //dělení /
    T_MUL,      //násobení *
    T_SUB,      //odčítání -
    T_ADD,      //sčítání    +
    */