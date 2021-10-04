/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "expresionParser.h"

const char precTable[10][10] =
{
//	  #    *,/,//,   +-      ..       b       (       )        i      $
    {'<'	,'>'	,'>'	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// #
    {'<'	,'>'	,'>'	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// *,/
	{'<'	,'<'	,'>'	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// +,-
	{'<'	,'<'	,'<'	,'<'	,'>'	,'<'	,'>'	,'<'	,'>'},// ..
	{'<'	,'<'	,'<'	,'<'	,'>'	,'<'	,'>'	,'<'	,'>'},// >, <, <=, >=, ==, !=
	{'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'='	,'<'	,' '},// (	
	{'>'	,'>'	,'>'	,'>'	,'>'	,' '	,'>'    ,' '	,'>'},// )
	{' '	,'>'	,'>'	,'>'	,'>'	,' '	,'>'	,' '	,'>'},// i
	{'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,' '	,'<'	,' '},// $
};

tokenType expresionDevelop(tokenType actual,scanerData *sData)   //nebude ve finální verzi, pouze pro účekly testu ll gramatiky,
{
    bool operatorFlag=false;
    bool firstOperant=true;
    bool instideBracked=false;
    while(true)
    {
        printf("-----------------------------------------------------debug:%s\n",tokenStr(actual));
        if(actual==T_STR_LEN&&firstOperant)
        {

        }
        else if(firstOperant)
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
    return actual;
}

bool isId(tokenType toCompere)   //nebude ve finální verzi, pouze pro účekly testu ll gramatiky
{
    return toCompere==T_STR||toCompere==T_INT||toCompere==K_NIL||toCompere==T_DOUBLE||toCompere==T_ID;
}

bool isOperator(tokenType toCompere)     //nebude ve finální verzi, pouze pro účekly testu ll gramatiky
{
    return toCompere==T_DIV2||toCompere==T_DIV||toCompere==T_MUL||toCompere==T_ADD||toCompere==T_SUB||toCompere==T_STR_LEN||toCompere==T_EQ||toCompere==T_NOT_EQ||toCompere==T_LT||toCompere==T_LTE||toCompere==T_GT||toCompere==T_GTE||toCompere==T_DOT2||toCompere==T_STR_LEN;
}

void expresionParse(tokenType actual,scanerData *sData)
{
    stack stack;
    stackInit(&stack);
    stackPush(&stack,O_DOLAR);

    while (stackTop(&stack)!=O_DOLAR||actual!=T_EOF)
    {
        debug("input:%-10s stack:%-10s\n",tokenStr(actual),tokenStr(stackTop(&stack))); 
        stackPrint(&stack)   ; 
        switch (getSymFromPrecTable(actual,stackTop(&stack)))
        {
            case '=':
                stackPush(&stack,actual);
                actual=getNextToken(sData);
                break;
            case '<':
                stackInsertHanle(&stack);
                stackPush(&stack,actual);
                actual=getNextToken(sData);
                break; 
            case '>':
                reduction(&stack);
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

void reduction(stack *s)
{
    tokenType id1=O_NONE;
    tokenType op=O_NONE;
    tokenType id2=O_NONE;

    tokenType aux=stackPop(s);
    switch (aux)
    {
        case T_INT:
        case T_DOUBLE:
        case T_STR:
        case T_ID:
            stackRemoveHande(s);
            stackPush(s,NE_EXP);
            return;
        break;
        case NE_EXP:
            id2=aux;
        break;
        case T_RBR:
            if(stackPop(s)!=NE_EXP)
                errorD(-1,"expresion in bracked err");
            if(stackPop(s)!=T_LBR)
                errorD(-1,"expresion in bracked err");
            stackRemoveHande(s);
            stackPush(s,NE_EXP);    
            return;
        break;
        default:
            errorD(-1,"sa reduction err");
    }
    aux=stackPop(s);
    switch (aux)
    {
        case T_STR_LEN:
            stackRemoveHande(s);
            stackPush(s,NE_EXP);
            op=aux;
            generateExpresion(id1,op,id2);
            return;
        break;
        default:
            if(isOperator(aux))
                op=aux;
            else
                errorD(-1,"sa reduction err");
    }
    aux=stackPop(s);
    switch (aux)
    {
        case NE_EXP:
            id1=aux;
            stackRemoveHande(s);
            stackPush(s,NE_EXP);
            generateExpresion(id1,op,id2);
            return;
        break;
        default:
            errorD(-1,"sa reduction err");
    }

}

void generateExpresion(tokenType id1, tokenType op ,tokenType id2)
{
    debug("generated: %s %s %s\n",tokenStr(id2),tokenStr(op),tokenStr(id1));
}

char getSymFromPrecTable(tokenType input, tokenType stack)
{
    int colum=getPosInTable(input);
    int row=getPosInTable(stack);
    return precTable[row][colum];
}

int getPosInTable(tokenType toDecode)
{
    switch (toDecode)
    {
    case T_STR_LEN:
        return 0;
    case T_MUL:  
    case T_DIV:
    case T_DIV2:
        return 1;
    case T_ADD:
    case T_SUB:
        return 2;  
    case T_DOT2:
        return 3;   
    case T_GT:
    case T_LT:
    case T_LTE:
    case T_GTE:  
    case T_EQ:
    case T_NOT_EQ:
        return 4;
    case T_LBR:
        return 5;           
    case T_RBR:
        return 6;
    case T_ID:
    case T_STR:
    case T_INT:
    case T_DOUBLE:
        return 7;  
    case O_DOLAR:
    case T_EOF:
        return 8;
    default:
         return 8;
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