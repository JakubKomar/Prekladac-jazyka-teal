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
        
    STData * data;
    bool checkOnly;
    char *key=strCpyWhithMalloc(&d->sData.fullToken);
    data=frameStackInsertFunctionDefinition(&d->pData.dataModel,key,&checkOnly);
    frameStack_pushFrame(&d->pData.dataModel,true);
    t=next(d);
    switch (t.type)
    {
        case T_ID: 
            LLfuncArg(d,checkOnly,0,data);
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
        LLreturnArg(d,checkOnly,0,data);

    LLprog(d);

    if(d->pData.actualToken.type!=K_END)
        LLerr();
    frameStack_popFrame(&d->pData.dataModel);

    t=next(d);
}

void LLreturnArg(systemData *d,bool checkOnly,int argNum,STData * Fdata)
{
    token type=next(d);
    switch (type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            if(checkOnly)
            {
                if(!(argNum<Fdata->funcData->retNum))
                    errorD(-1,"počty návratových argumentů v definici neodpovídají počtu v deklaracaci");
                else if(Fdata->funcData->retTypes[argNum]!=type.type)
                    errorD(3,"typ n8vratového parametru neodpovídá typu v deklaracaci");
            }
            else
            {
                Fdata->funcData->retNum++;
            }
        break;   
        default:
            LLerr();
        break;
    }
    token t=next(d);
    switch (t.type)
    {
        case T_COMMA: 
            LLreturnArg(d,checkOnly,argNum+1,Fdata);
        break;   
        default:
            if(!checkOnly)
            {
                if(!(Fdata->funcData->retTypes=malloc(sizeof(tokenType)*Fdata->funcData->retNum)))
                    error(100);
            }
            else if(Fdata->funcData->retNum!=(argNum+1))
            {
                errorD(-1,"počty návratových argumentů v definici neodpovídají počtu v deklaracaci");
            }
        break;
    }
    if(!checkOnly)
        Fdata->funcData->retTypes[argNum]=type.type;
}

void LLfuncArg(systemData *d,bool checkOnly,int argNum,STData * Fdata)
{
    token id=d->pData.actualToken;
    if(id.type!=T_ID)
        LLerr();
    char *key=strCpyWhithMalloc(&d->sData.fullToken);  

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
            frameStackInsertVar(&d->pData.dataModel,key,false,type.type);
            if(checkOnly)
            {
                if(!(Fdata->funcData->paramNum>argNum))
                    errorD(-1,"počty argumentů v definici neodpovídají počtu v deklaracaci");
                else if(Fdata->funcData->paramTypes[argNum]!=type.type)
                    errorD(3,"typ parametru neodpovídá typu v deklaracaci");
            }
            else
            {
                Fdata->funcData->paramNum++;
            }
        break;   
        default:
            free(key);
            LLerr();
        break;
    }

    token t=next(d);
    switch (t.type)
    {
        case T_COMMA: 
            next(d);
            LLfuncArg(d,checkOnly,argNum+1,Fdata);
        break;   
        case T_RBR:
            if(!checkOnly)
            {
                if(!(Fdata->funcData->paramTypes=malloc(sizeof(tokenType)*Fdata->funcData->paramNum)))
                {
                    error(100);
                }
            }
            else if(Fdata->funcData->paramNum!=(argNum+1))
            {
                errorD(-1,"počty argumentů v definici neodpovídají počtu v deklaracaci");
            }
        break;
        default:
            LLerr();
        break;
    }
    if(!checkOnly)
        Fdata->funcData->paramTypes[argNum]=type.type;
}

void LLif(systemData *d)
{
    token t=next(d);
    expresionParse(d,false);
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
            expresionParse(d,false);
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
            expresionParse(d,false);
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
    bool checkOnly;
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
            ptr =frameStackInsertFunctionDeclaration(&d->pData.dataModel,name,pozition.type==K_GLOBAL,&checkOnly);
            LLfuncDecParam(d,ptr,checkOnly);           
        break;      
        default:
            LLerr();
        break;
    }
}

void LLfuncDecParam(systemData *d,STData *Fdata,bool checkOnly)
{
    token t=next(d);
    switch (t.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            LLfuncDecNParam(d,Fdata,0,checkOnly);
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
            LLfuncDecNRet(d,Fdata,0,checkOnly);
        break;   
        default:

        break;
    }
}

void LLfuncDecNRet(systemData *d,STData *Fdata,int argNum,bool checkOnly)
{
    token Type=d->pData.actualToken;
    switch (Type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            if(checkOnly)
            {
                if(!(argNum<Fdata->funcData->retNum))
                    errorD(-1,"počty návratových argumentů v deklaraci neodpovídají počtu v definici");
                else if(Fdata->funcData->retTypes[argNum]!=Type.type)
                    errorD(3,"typ návratového parametru neodpovídá typu v definici");
            }
            else
                Fdata->funcData->retNum++;
        break;      
        default:
            LLerr();
        break;
    }
    next(d);
    switch (d->pData.actualToken.type)
    {
        case T_COMMA: 
            next(d);
            LLfuncDecNRet(d,Fdata,argNum+1,checkOnly);
        break;      
        default:
            if(!checkOnly)
            {
                if(!(Fdata->funcData->retTypes=malloc(sizeof(tokenType)*Fdata->funcData->retNum)))
                    error(100);
            }
        break;
    }
    if(!checkOnly)
        Fdata->funcData->retTypes[argNum]=Type.type;
}

void LLfuncDecNParam(systemData *d,STData *Fdata,int argNum,bool checkOnly)
{
    token Type=d->pData.actualToken;
    switch (Type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            if(checkOnly)
            {
                if(!(argNum<Fdata->funcData->paramNum))
                    errorD(-1,"počty návratových argumentů v deklaraci neodpovídají počtu v definici");
                else if(Fdata->funcData->paramTypes[argNum]!=Type.type)
                    errorD(3,"typ návratového parametru neodpovídá typu v definici");
            }
            else
                Fdata->funcData->paramNum++;
        break;      
        default:
            LLerr();
        break;
    }
    next(d);
    switch (d->pData.actualToken.type)
    {
        case T_RBR: 
            if(!checkOnly)
            {
                if(!(Fdata->funcData->paramTypes=malloc(sizeof(tokenType)*Fdata->funcData->paramNum)))
                    error(100);
            }
        break; 
        case T_COMMA: 
            next(d);
            LLfuncDecNParam(d,Fdata,argNum+1,checkOnly);
        break;      
        default:
            LLerr();
        break;
    }
    if(!checkOnly)
        Fdata->funcData->paramTypes[argNum]=Type.type;
}

void LLwhile(systemData *d)
{
    token t=next(d); 
    expresionParse(d,false);
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
    LLid_next(d);
    if(d->pData.actualToken.type!=T_ASSIGEN)
        LLerr();
    LLexp_or_func(d);
}

void LLid_next(systemData *d)
{
    token t=d->pData.actualToken;
    if(t.type!=T_ID)
        LLerr();

    STData *data=frameStackSearch(&d->pData.dataModel,d->sData.fullToken.str);
    if(data==NULL)
        errorD(3,"přiřazení do nedeklarované proměnné");
    else if(data->type==ST_FUNC)
        errorD(3,"přiřazení do fukce není legální operace");

    t=next(d);
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
            expresionParse(d,false);
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
            expresionParse(d,false);
            LLexpresionN(d);
        break;  
        default:
            LLerr();
        break;
    }
}

void LLfuncCall(systemData *d)
{
    STData * data=frameStackSearch(&d->pData.dataModel,d->sData.fullToken.str);
    if(!data)
        errorD(3,"funkce není deklarována");
    if(data->type!=ST_FUNC)
        errorD(3,"proměnná nelze zavolat");
        
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
    expresionParse(d,false);
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
                expresionParse(d,false);
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
