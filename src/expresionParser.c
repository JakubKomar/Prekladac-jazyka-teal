/**
 * @brief   Expresion parsing
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

void expresionParse(systemData *sData,bool ignor)
{
    debugS("\x1B[33m******************* analysys swich to expresion mode*************************\x1B[0m\n"); 
    stack * stack=&sData->epData.stack;
    token actual =sData->pData.actualToken;
    stackClear(stack);
    stackPush(stack,(token){O_DOLAR});
    bool separatorF=false;
    while (stackTop(stack).type!=O_DOLAR||actual.type!=T_EOF)
    {
        debug("input:%-10s stack:%-10s\n",tokenStr(actual),tokenStr(stackTop(stack))); 
        stackPrint(stack)  ; 
        switch (getSymFromPrecTable(actual.type,stackTop(stack).type))
        {
            case '=':
                stackPush(stack,actual);
                actual=nextTokenExpParser(&separatorF,sData);
                break;
            case '<':
                stackInsertHanle(stack);
                stackPush(stack,actual);
                actual=nextTokenExpParser(&separatorF,sData);
                break; 
            case '>':
                reduction(stack);
                break;
            case ' ':
                if(stackTop(stack).type==O_DOLAR&&actual.type==T_RBR)//right acket can end the fuction call-no lexical error
                {
                    debugS("\x1B[33m******************* analysys swich to normal mode*************************\x1B[0m\n"); 
                    return;
                }
                errorD(2,"syntax error in expresion");
                break;
            default:
                errorD(99,"precedence table error");
                break;
        }
    }
    debugS("\x1B[33m******************* analysys swich to normal mode*************************\x1B[0m\n"); 
} 

token nextTokenExpParser(bool * separatorF,systemData * sData)
{
    sData->pData.actualToken=getNextUsefullToken(&sData->sData);
    tokenType new= sData->pData.actualToken.type;

    if(*separatorF==true && (new==T_ID))
        return (token){T_EOF};
    else if(isId(new))
        *separatorF=true;
    else if(new!=T_LBR|| new!=T_RBR)
        *separatorF=false;
    if(isOperator(new)||isId(new)||new==T_RBR||new==T_LBR)
        return sData->pData.actualToken;
    else
        return (token){T_EOF};
}

void reduction(stack *s)
{
    token id1=(token){O_NONE};
    token op=(token){O_NONE};
    token id2=(token){O_NONE};

    tokenType aux=stackPop(s).type;
    switch (aux)
    {
        case T_INT:
        case T_DOUBLE:
        case T_STR:
        case T_ID:
        case K_NIL:
            stackRemoveHande(s);
            stackPush(s,(token){NE_EXP});
            return;
        break;
        case NE_EXP:
            id2.type=aux;
        break;
        case T_RBR:
            if(stackPop(s).type!=NE_EXP)
                errorD(2,"expresion in bracked err");
            if(stackPop(s).type!=T_LBR)
                errorD(2,"expresion in bracked err");
            stackRemoveHande(s);
            stackPush(s,(token){NE_EXP});    
            return;
        break;
        default:
            errorD(2,"sa reduction err");
    }
    aux=stackPop(s).type;
    switch (aux)
    {
        case T_STR_LEN:
            stackRemoveHande(s);
            stackPush(s,(token){NE_EXP});
            op.type=aux;
            generateExpresion(id1,op,id2);
            return;
        break;
        default:
            if(isOperator(aux))
                op.type=aux;
            else
                errorD(2,"sa reduction err");
    }
    aux=stackPop(s).type;
    switch (aux)
    {
        case NE_EXP:
            id1.type=aux;
            stackRemoveHande(s);
            stackPush(s,(token){NE_EXP});
            generateExpresion(id1,op,id2);
            return;
        break;
        default:
            errorD(2,"sa reduction err");
    }
}

void generateExpresion(token id1, token op ,token id2)
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
        case K_NIL:
        case T_DOUBLE:
            return 7;  
        case O_DOLAR:
        case T_EOF:
        default:
            return 8;
    }
}

void initExpresionData(expresionParserData *data)
{   
    stackInit(&data->stack);
}

void destructExpresionData(expresionParserData *data)
{   
    stackDestruct(&data->stack);
}

bool isId(tokenType toCompere)   
{
    return toCompere==T_STR||toCompere==T_INT||toCompere==K_NIL||toCompere==T_DOUBLE||toCompere==T_ID;
}

bool isOperator(tokenType toCompere)    
{
    return toCompere==T_DIV2||toCompere==T_DIV||toCompere==T_MUL||toCompere==T_ADD||toCompere==T_SUB||toCompere==T_STR_LEN||toCompere==T_EQ||toCompere==T_NOT_EQ||toCompere==T_LT||toCompere==T_LTE||toCompere==T_GT||toCompere==T_GTE||toCompere==T_DOT2||toCompere==T_STR_LEN;
}

