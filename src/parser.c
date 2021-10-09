/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "parser.h"

void parserMain(systemData * d)
{
    LLprolog(d);
    LLprog(d);
}

void LLprolog(systemData * d)
{
    token t=next(d); 
    if(t.type!=K_REQUIRE)
        LLerr();

    t=next(d);
    if(t.type!=T_STR)
        LLerr(); 
    if(strcmp(d->sData.fullToken.str,"\"ifj21\""))
        LLerr();
    next(d);
}

void LLprog(systemData * d)
{
    switch (d->pData.actualToken.type)
    {
        case T_EOF:
        case K_END:
        case K_ELSE:
            return;
        break;   
        case T_ID:
            LLid(d);
        break;  
        case T_FUNC_CALL:
            LLfuncCall(d);
        break;  
        case K_WHILE:
            LLwhile(d); 
        break;  
        case K_IF:
            //LLif(d); 
        break; 
        case K_FUNCTION:
            //LLfunction(d);  
        break; 
        case K_RETURN:
            //LLreturn(d);
        break; 
        case K_LOCAL:
        case K_GLOBAL:
            //LLdeclaration(d);
        break; 
        default:
            LLerr();
        break;
    }
}

void LLwhile(systemData *d)
{
    token t=next(d); 
    
}

void LLid(systemData *d)
{
    //kontrola v tabulce symbolů
    LLid_next(d);
    if(d->pData.actualToken.type!=T_ASSIGEN)
        LLerr();
    LLexp_or_func(d);
    LLprog(d);
    next(d);
}

void LLid_next(systemData *d)
{
    token t=next(d);
    switch (t.type)
    {
        case T_ASSIGEN: 
            return;
        break;   
        case T_COMMA: 
        
        break;  
        default:
            LLerr();
        break;
    }
    t=next(d);
    if(t.type!=T_ID)
        LLerr();
    //kontrola v tabulce symbolů
    LLid_next(d);
}

void LLexp_or_func(systemData *d)
{
    token t=next(d);
    switch (t.type)
    {
        case T_INT:
        case T_STR_LEN:
        case T_STR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
        case T_LBR: 
            //parse expresion
            LLexpresionN(d);
        break;  
        case T_FUNC_CALL: 
            LLfuncCall(d);
        break;  
        default:
            LLerr();
        break;
    }
}

void LLfuncCall(systemData *d)
{
    //kontrola v tabulce symbolu
    token t=next(d);
    switch (t.type)
    {   
        case T_ID: 
            //kontrola v tabulce symbolu
        case T_INT:
        case T_STR:
        case K_NIL:
        case T_DOUBLE:
            LLfArg(d);
        case T_RBR: 

        break;  
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type!=T_RBR)
        LLerr();
}
void LLfArg(systemData *d)
{   
    //kontrola v tabulce symbolu
    LLfArgN(d);
}
void LLfArgN(systemData *d)
{   
    token t=next(d);
    if(t.type==T_RBR)
        return;
    else if(t.type==T_COMMA)
    {
        t=next(d);
        switch (t.type)
        {   
            case T_ID: 
                //kontrola v tabulce symbolu
            case T_INT:
            case T_STR:
            case K_NIL:
            case T_DOUBLE:
                LLfArgN(d);
            break;  
            default:
                LLerr();
            break;
        }
    }
}
void LLexpresionN(systemData *d)
{
    token t=next(d);
    if(t.type!=T_COMMA)
        return;
    t=next(d);
    switch (t.type)
    {
        case T_INT:
        case T_STR_LEN:
        case T_STR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
        case T_LBR: 
            //parse expresion
            LLexpresionN(d);
        break;  
        default:
            LLerr();
        break;
    }
}

token next(systemData *d)
{
    d->pData.actualToken=getNextUsefullToken(&d->sData);
    return d->pData.actualToken;
}

void initParserData(parserData * data)
{
    stackInit(&(data->stack));
    stackPush(&(data->stack),(token){T_EOF,NULL});
    stackPush(&(data->stack),(token){N_START,NULL});
}

void destructParserData(parserData * data)
{
    stackDestruct(&(data->stack));
}

void systemDataInit(systemData * data)
{
    initScanerData(&data->sData);
    initParserData(&data->pData);
    initExpresionData(&data->epData);
}

void systemDataDestruct(systemData * data)
{
    destructScanerData(&data->sData);
    destructParserData(&data->pData);
    destructExpresionData(&data->epData);
}

void LLerr()
{
    errorD(2,"Pro daný neterminál nebyl nalezen rozklad");
}