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
    if(d->pData.actualToken.type!=T_EOF)
        LLerr();
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
    token t=d->pData.actualToken;
    while (t.type!=T_EOF&&t.type!=K_END&&t.type!=K_ELSE)
    {
        switch (t.type)
        {
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
                LLif(d); 
            break; 
            case K_FUNCTION:
                LLfunction(d);  
            break; 
            case K_RETURN:
                LLreturn(d);
            break; 
            case K_LOCAL:
            case K_GLOBAL:
                LLdeclaration(d);
            break; 
            default:
                LLerr();
            break;
        }
        t=d->pData.actualToken;
    }
}

void LLfunction(systemData *d)
{
    token t=next(d);
    if(t.type!=T_FUNC_CALL)
        LLerr();
    //kontrola v sym table
    t=next(d);
    switch (t.type)
    {
        case T_ID: 
            //konrola/zaznamenání
            LLfuncArg(d);
        break;   
        case T_RBR:

        break; 
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type!=T_RBR)
        LLerr();
    t=next(d);
    if(t.type==T_COLON)   
        LLreturnArg(d);
    LLprog(d);
    if(d->pData.actualToken.type!=K_END)
        LLerr();
    t=next(d);
}
void LLreturnArg(systemData *d)
{
    token type=next(d);
    switch (type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //konrola/zaznamenání
        break;   
        default:
            LLerr();
        break;
    }
    token t=next(d);
    switch (t.type)
    {
        case T_COMMA: 
            LLreturnArg(d);
        break;   
        default:
        break;
    }
}
void LLfuncArg(systemData *d)
{
    token id=d->pData.actualToken;
    token type=next(d);
    if(type.type!=T_COLON)
        LLerr();
    type=next(d);
    switch (type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //konrola/zaznamenání
        break;   
        default:
            LLerr();
        break;
    }
    LLfuncArgN(d);
}

void LLfuncArgN(systemData *d)
{
    token t=next(d);
    if(t.type==T_RBR)
        return;
    else if(t.type!=T_ID)
        LLerr();
    token id=t;
    t=next(d);
    if(t.type!=T_COLON)
        LLerr();
    token type=next(d);
    switch (type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //konrola/zaznamenání
        break;   
        default:
            LLerr();
        break;
    }
    LLfuncArgN(d);
}

void LLif(systemData *d)
{
    token t=next(d);
    expresionParse(d);
    t=d->pData.actualToken;
    if(t.type!=K_THEN)
        LLerr();
    next(d);
    LLprog(d);
    t=d->pData.actualToken;
    switch (t.type)
    {
        case K_END:

        break;   
        case K_ELSE:
            LLelse(d);
        break; 
        default:
            LLerr();
        break;
    }
    next(d);
}

void LLelse(systemData *d)
{
    next(d);
    LLprog(d);
    switch (d->pData.actualToken.type)
    {
        case K_END:

        break;   
        default:
            LLerr();
        break;
    }
}

void LLreturn(systemData *d)
{
    token t=next(d);
    switch (t.type)
    {
        case T_INT:
        case T_STR:
        case T_STR_LEN:
        case T_LBR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
            //zparsovat a zkontrolovat
            expresionParse(d);
            LLreturnArgN(d);
        break;   
        case K_END:
        case K_ELSE:
        case T_EOF:

        break; 
        default:
            LLerr();
        break;
    }
}
void LLreturnArgN(systemData *d)
{
    token t=d->pData.actualToken;
    if(t.type!=T_COMMA)
        return;
    t=next(d);
    switch (t.type)
    {
        case T_INT:
        case T_STR:
        case T_STR_LEN:
        case T_LBR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
            //zparsovat a zkontrolovat
            expresionParse(d);
            LLreturnArgN(d);
        break;   
        case K_END:
        case K_ELSE:
        case T_EOF:

        break; 
        default:
            LLerr();
        break;
    }
}

void LLdeclaration(systemData *d)
{
    token pozition=d->pData.actualToken;    //global/local

    token id=next(d); 
    if(id.type!=T_ID)   
        LLerr();
    char *name=strCpyWhithMalloc(&d->sData.fullToken);

    token type=next(d);     
    if(type.type!=T_COLON)
        LLerr();
    
    STData *ptr;
    type=next(d);   //type of declaration 
    switch (d->pData.actualToken.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            ptr =frameStackInsertVar(&d->pData.dataModel,name,pozition.type==K_GLOBAL,d->pData.actualToken.type);
            next(d);
            if(d->pData.actualToken.type==T_ASSIGEN)
                LLexp_or_func(d);
        break;  
        case T_FUNC_CALL: 
            ptr =frameStackInsertFunction(&d->pData.dataModel,name,pozition.type==K_GLOBAL,false);
            LLfuncDecParam(d);           
        break;      
        default:
            LLerr();
        break;
    }
}

void LLfuncDecParam(systemData *d)
{
    token t=next(d);
    switch (t.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //nějak zaznamentat
            LLfuncDecNParam(d);
        break;   
        case T_RBR:
        break;   
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type!=T_RBR)
        LLerr();
    t=next(d);
    if(t.type!=T_COLON)
        return;  
    t=next(d);          
    switch (t.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //nějak zaznamentat návratové hodnoty
            LLfuncDecNRet(d);
        break;   
        default:

        break;
    }
}

void LLfuncDecNRet(systemData *d)
{
    token t=next(d);
    if(t.type!=T_COMMA)
        return;   
    t=next(d);          
    switch (t.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //nějak zaznamentat návratové hodnoty
            LLfuncDecNRet(d);
        break;   
        default:
            LLerr();
        break;
    }
}

void LLfuncDecNParam(systemData *d)
{
    token t=next(d);
    if(t.type==T_RBR)
        return;
    else if(t.type!=T_COMMA)
        LLerr();
    t=next(d);  
    switch (t.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            //nějak zaznamentat
            LLfuncDecNParam(d);
        break;      
        default:
            LLerr();
        break;
    }

}

void LLwhile(systemData *d)
{
    token t=next(d); 
    expresionParse(d);
    t=d->pData.actualToken;
    if(t.type!=K_DO)
        LLerr();
    t=next(d); 
    LLprog(d);
    t=d->pData.actualToken;
    if(t.type!=K_END)
        LLerr();
    t=next(d); 
}

void LLid(systemData *d)
{

    //kontrola v tabulce symbolů
    LLid_next(d);
    if(d->pData.actualToken.type!=T_ASSIGEN)
        LLerr();
    LLexp_or_func(d);
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
            expresionParse(d);
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

void LLexpresionN(systemData *d)
{
    token t=d->pData.actualToken;
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
            expresionParse(d);
            LLexpresionN(d);
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
    next(d);
}

void LLfArg(systemData *d)
{   
    //kontrola v tabulce symbolu
    expresionParse(d);
    LLfArgN(d);
}

void LLfArgN(systemData *d)
{   
    token t=d->pData.actualToken;
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
                expresionParse(d);
                LLfArgN(d);
            break;  
            default:
                LLerr();
            break;
        }
    }
}

token next(systemData *d)
{
    d->pData.actualToken=getNextUsefullToken(&d->sData);
    return d->pData.actualToken;
}

void initParserData(parserData * data)
{
    frameStack_init(&data->dataModel);
}

void destructParserData(parserData * data)
{
    frameStack_disporse(&data->dataModel);
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
    errorD(2,"Chyba při kontrole syntaxe-porušeno rozkladové pravidlo.");
}
