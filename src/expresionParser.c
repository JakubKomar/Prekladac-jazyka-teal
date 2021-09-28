/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "expresionParser.h"


void expresionDevelop(tokenType actual,scanerData *sData)   //nebude ve finální verzi, pouze pro účekly testu ll gramatiky,
{
    bool operatorFlag=false;
    bool firstOperant=true;
    bool instideBracked=false;
    while(true)
    {
        if(firstOperant)
        {
            if(isId(actual))
            {
                firstOperant=false;
            }
            else
                errorD(99,"šatný expression");
        }
        else if(operatorFlag)
        {
            if(isId(actual))
            {
                operatorFlag=false;
            }
            else
                errorD(99,"šatný expression");
        }
        else if(isOperator(actual))
        {
            if(actual==T_LBR)
                instideBracked=true;
            else
                operatorFlag=true;
        }
        else if(instideBracked)
        {
            if(actual==T_RBR)
                instideBracked=false;
        }
        else
        {
            break;              
        }
        actual=getNextUsefullToken(sData);
    }
}
bool isId(tokenType toCompere)   //nebude ve finální verzi, pouze pro účekly testu ll gramatiky
{
    return toCompere==T_STR||toCompere==T_INT||toCompere==K_NIL||toCompere==T_DOUBLE||toCompere==T_ID;
}
bool isOperator(tokenType toCompere)     //nebude ve finální verzi, pouze pro účekly testu ll gramatiky
{
    return toCompere==T_DIV2||toCompere==T_DIV||toCompere==T_MUL||toCompere==T_ADD||toCompere==T_SUB||toCompere==T_STR_LEN||toCompere==T_EQ||toCompere==T_NOT_EQ||toCompere==T_LT||toCompere==T_LTE||toCompere==T_GT||toCompere==T_GTE||toCompere==T_RBR||toCompere==T_LBR;
}


void expresionParse(tokenType actual,scanerData *sData)
{
    stack stack;
    stackInit(&stack);
    stackPush(&stack,O_DOLAR);

    while (stackHead(&stack)==O_DOLAR&&actual==O_DOLAR)
    {
        switch (getSomething(actual,stackHead(&stack)))
        {
        case '=':
            stackPush(&stack,actual);
            actual=getNextToken(sData);
            break;
        case '<':
            stackPush(&stack,O_HANDLE);
            stackPush(&stack,actual);
            actual=getNextToken(sData);
            break; 
        case '>':
            //reduction
            while (stackHead(&stack)!=O_HANDLE)
            {
                stackPop(&stack);
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

    stackDestruct(&stack);
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
    case T_EQ:
        return 8;
    case T_NOT_EQ:
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