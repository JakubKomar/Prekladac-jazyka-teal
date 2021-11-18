/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "parser.h"

void parserMain(systemData * d)
{
    LLprolog(d);    //"require "ifj21"
    genereteProgramHeader();
    LLprog(d,NULL); //main body
    if(d->pData.actualToken.type!=T_EOF)    //no input left
        LLerr();
    frameStackPopFrame(&d->pData.dataModel);    //clean up
    if(searchForNonDefinedFunction(&d->pData.dataModel.globalF.bTree))  //searching for non defined functions
        errorD(3,"k některé uživatelské funci chybí definice");
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

void LLprog(systemData * d,STFuncData *fData)
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
                LLfuncCall(d,0);
                printf("CLEARS\n"); //cleaning of stack s
            break;
            case K_WHILE:
                LLwhile(d,fData); 
            break;  
            case K_IF:
                LLif(d,fData); 
            break; 
            case K_FUNCTION:
                LLfunction(d);  
            break; 
            case K_RETURN:
                LLreturn(d,fData);
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

void LLfunction(systemData *d)  //neterminal for definition of  function 
{
    token t=next(d);
    if(t.type!=T_FUNC_CALL)
        LLerr();
        
    bool checkOnly;
    char *key=stringCpyToChPtr(&d->sData.fullToken);
    STSymbolPtr* node=frameStackInsertFunctionDefinition(&d->pData.dataModel,key,&checkOnly);   //try insert function to datamodel
    STData * data=&(*node)->data;
    if(!checkOnly)  //function was declared - only checking params and ret params
        decorId(d,data);
    changeRangeScope(d,true);       //function body have its own range of vars
    genFuncHeader(data,(*node)->id);
    t=next(d);
    switch (t.type)
    {
        case T_ID: 
            LLfuncArg(d,checkOnly,0,data);
        break;   
        case T_RBR:
            if(checkOnly&&data->funcData->paramNum>0)
                errorD(3,"počty parametů v deklaraci neodpovídají");
        break; 
        default:
            LLerr();
        break;
    }

    if(d->pData.actualToken.type!=T_RBR)
        LLerr();
    
    t=next(d);
    if(t.type==T_COLON)     //control ret params if there is some
        LLreturnArg(d,checkOnly,0,data);
    else if(checkOnly&&data->funcData->retNum>0)
        errorD(3,"počty návratových parametů v deklaraci neodpovídají");

    LLprog(d,data->funcData);   //main body of function
    if(d->pData.actualToken.type!=K_END)
        LLerr();
    frameStackPopFrame(&d->pData.dataModel);        //pop frame from datamodel
    genFuncFoter(data,(*node)->id);
    t=next(d);
}

void LLreturnArg(systemData *d,bool checkOnly,int argNum,STData * Fdata)    //neterminal for definition of ret args
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
                    errorD(3,"počty návratových argumentů v definici neodpovídají počtu v deklaracaci");
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
                errorD(3,"počty návratových argumentů v definici neodpovídají počtu v deklaracaci");
            }
        break;
    }
    if(!checkOnly)
        Fdata->funcData->retTypes[argNum]=type.type;
}

void LLfuncArg(systemData *d,bool checkOnly,int argNum,STData * Fdata)  //neterminal for arg of function
{
    token id=d->pData.actualToken;
    if(id.type!=T_ID)
        LLerr();
    char *key=stringCpyToChPtr(&d->sData.fullToken);  

    token type=next(d);
    if(type.type!=T_COLON)
        LLerr();
    STData *varData;
    STSymbolPtr* node;
    type=next(d);
    switch (type.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            node=frameStackInsertVar(&d->pData.dataModel,key,false,type.type);
            varData=&(*node)->data;
            varData->varData->defined=true;
            decorId(d,varData);
            if(checkOnly)
            {
                if(!(Fdata->funcData->paramNum>argNum))
                    errorD(3,"počty argumentů v definici neodpovídají počtu v deklaracaci");
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
                errorD(3,"počty argumentů v definici neodpovídají počtu v deklaracaci");
            }
        break;
        default:
            LLerr();
        break;
    }
    if(!checkOnly)
        Fdata->funcData->paramTypes[argNum]=type.type;
    printf("DEFVAR ");genVar(varData->dekorator,key);printf("\n");
    printf("POPS ");genVar(varData->dekorator,key);printf("\n");
}

void LLif(systemData *d,STFuncData *fData)
{
    token t=next(d);
    tokenType expT=expresionParse(d);
    t=d->pData.actualToken;
    if(t.type!=K_THEN)
        LLerr();
    unsigned long int decor=genIfHeader(d,expT);
    next(d);
    changeRangeScope(d,false);
    LLprog(d,fData);
    frameStackPopFrame(&d->pData.dataModel);
    t=d->pData.actualToken;
    switch (t.type)
    {
        case K_END:
            genIfFoter(decor);
        break;   
        case K_ELSE:
            genElseHeader(decor);
            LLelse(d,fData,decor);
            genElseFoter(decor);
        break; 
        default:
            LLerr();
        break;
    }
    next(d);
}

void LLelse(systemData *d,STFuncData *fData,unsigned long int decorId)
{
    next(d);
    changeRangeScope(d,false);
    LLprog(d,fData);
    frameStackPopFrame(&d->pData.dataModel);
    switch (d->pData.actualToken.type)
    {
        case K_END:

        break;   
        default:
            LLerr();
        break;
    }
}

void LLreturn(systemData *d,STFuncData *fData)
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
        case T_SUB:
        case T_ADD:
            LLreturnArgN(d,fData,0);
        break;   
        default:
            if(fData!=NULL)
                for(int i=0;i<fData->retNum;i++)
                {
                    genInst("PUSHS nil@nil");
                }
            else
            {
                genInst("EXIT int@0");
            }
        break;
    }
    t=d->pData.actualToken;
    if(t.type!=K_END&&t.type!=K_ELSE&& t.type!=T_EOF)
        LLerr();
    genReturn();
}
void LLreturnArgN(systemData *d,STFuncData *fData,int order)
{
    token t=d->pData.actualToken;
    tokenType retType;
    switch (t.type)
    {
        case T_INT:
        case T_STR:
        case T_STR_LEN:
        case T_LBR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
        case T_ADD:
        case T_SUB:
            retType=expresionParse(d);
            if(fData!=NULL)
            {
                if(order>=fData->retNum)
                    errorD(5,"počty návratových argumentů v reodpovídajá deklaraci/definici");
                assigenCompCheck(fData->retTypes[order],retType,false);
            }
            else
            {
                if(order==0)
                {
                    assigenCompCheck(K_INTEGER,retType,false);
                    genInst("POPS GF@&JUMPVAR\nEXIT GF@&JUMPVAR");
                }
                else
                    errorD(5,"počty návratových argumentů v reodpovídajá deklaraci/definici");
            }
        break;   
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type!=T_COMMA)
    {
        if(fData!=NULL)
            for(int i=order+1;i<fData->retNum;i++)
            {
                genInst("PUSHS nil@nil");
            }
        return;
    }
    else
    {
        next(d);
        LLreturnArgN(d,fData,order+1);
    }
}

void LLdeclaration(systemData *d)   //neterminal for declaration of funciton/var
{
    token pozition=d->pData.actualToken;    //global/local

    token id=next(d); 
    if(id.type!=T_ID)   
        LLerr();
    char *name=stringCpyToChPtr(&d->sData.fullToken);

    token type=next(d);     
    if(type.type!=T_COLON)
        LLerr();
    
    STData *ptr;
    STSymbolPtr *node;
    type=next(d);   //type of declaration 
    bool checkOnly;
    switch (d->pData.actualToken.type)
    {
        case K_NUMBER: 
        case K_INTEGER: 
        case K_STRING: 
        case K_NIL:
            node =frameStackInsertVar(&d->pData.dataModel,name,pozition.type==K_GLOBAL,d->pData.actualToken.type);
            ptr=&(*node)->data;
            if(pozition.type!=K_GLOBAL)
                decorId(d,ptr);
            if(d->pData.isInWhile)
            {
                varId * new=malloc(sizeof(varId));
                if(!new)
                    error(100);
                new->decor=ptr->dekorator;
                if(!(new->id=strdup((*node)->id)))
                    error(100);
                stackPush(&d->pData.varDeclarationBuffer,(token){O_UNIMPORTANT,O_UNIMPORTANT,new});
            }
            else
            {
                printf("DEFVAR ");genVar(ptr->dekorator,name);printf("\n");
            }

            next(d);
            if(d->pData.actualToken.type==T_ASSIGEN)
            {
                stackPush(&d->pData.expresionBuffer,(token){ptr->varData->type});
                STFuncData * Fdata=LLexp_or_func(d,1);
                if(Fdata)
                    assigenCompCheck(ptr->varData->type,Fdata->retTypes[0],true);               
                printf("POPS ");genVar(ptr->dekorator,name);printf("\n");
                ptr->varData->defined=true;
            }
            else
            {
                printf("MOVE ");genVar(ptr->dekorator,name);genInst(" nil@nil");
            }
   
        break;  
        case K_FUNCTION: 
            node =frameStackInsertFunctionDeclaration(&d->pData.dataModel,name,pozition.type==K_GLOBAL,&checkOnly);
            ptr=&(*node)->data;
            if((!checkOnly)&&pozition.type!=K_GLOBAL)
                decorId(d,ptr);
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
            if(checkOnly&&Fdata->funcData->paramNum>0)
                errorD(3,"počty parametů v deklaraci neodpovídají");
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
            if(checkOnly&&Fdata->funcData->retNum>0)
                errorD(3,"počty návratovýchparametů v deklaraci neodpovídají");
        break;
    }
}

void LLfuncDecNRet(systemData *d,STData *Fdata,int argNum,bool checkOnly)//neterminal for declaration retrun arg in fucntion
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
                    errorD(3,"počty návratových argumentů v deklaraci neodpovídají počtu v definici");
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
                    errorD(3,"počty návratových argumentů v deklaraci neodpovídají počtu v definici");
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

void LLwhile(systemData *d,STFuncData *fData)//neterminal for while
{
    bool prevInWhile=d->pData.isInWhile;
    if(!prevInWhile)        //immersion in whiles
        genWhileDecJump(d);     //jump to declaration of var in whole while body-its called only on start of while cykle
    d->pData.isInWhile=true;
    token t=next(d); 
    unsigned long int decor=genWhileSlabel(d);  //uniqe name for while cykle
    tokenType retT=expresionParse(d);
    genWhileHeader(decor,retT); 
    t=d->pData.actualToken;
    if(t.type!=K_DO)
        LLerr();
    t=next(d); 
    changeRangeScope(d,false);  //body of while cykle have its own scope of range
    LLprog(d,fData);
    frameStackPopFrame(&d->pData.dataModel);
    t=d->pData.actualToken;
    if(t.type!=K_END)
        LLerr();
    genWhileFoter(d,decor,prevInWhile);  
    t=next(d); 
}

void LLid(systemData *d)
{
    LLid_next(d,0);
}

STFuncData * LLid_next(systemData *d,int order) 
{
    STFuncData * fData;
    token t=d->pData.actualToken;
    if(t.type!=T_ID)
        LLerr();
    order++;
    STSymbolPtr *ptr=frameStackSearchVar(&d->pData.dataModel,d->sData.fullToken.str);   
    if(ptr==NULL)
        errorD(3,"přiřazení do nedeklarované proměnné");
    STData *data=&(*ptr)->data;
    if(data->type==ST_FUNC)
        errorD(3,"přiřazení do fukce není legální operace");
    stackPush(&d->pData.expresionBuffer,(token){data->varData->type});

    t=next(d);
    switch (t.type)
    {
        case T_ASSIGEN: 
            fData=LLexp_or_func(d,order);
        break;   
        case T_COMMA: 
            next(d);
            fData=LLid_next(d,order);
        break;  
        default:
            LLerr();
        break;
    }
    if(fData)
        assigenCompCheck(data->varData->type,fData->retTypes[order-1],true);
    printf("POPS ");genVar(data->dekorator,(*ptr)->id);printf("\n");
    data->varData->defined=true;
    return fData;
}

STFuncData * LLexp_or_func(systemData *d,int numOfAsigens)
{
    STFuncData * fData=NULL;
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
        case T_ADD:
        case T_SUB:
            LLexpresionN(d,numOfAsigens);
        break;  
        case T_FUNC_CALL: 
            fData=LLfuncCall(d,numOfAsigens);
            for(int i=fData->retNum;i>numOfAsigens;i--)
                printf("POPS gf@&NULL\n");
        break;  
        default:
            LLerr();
        break;
    }
    return fData;
}

void LLexpresionN(systemData *d,int numOfAsigens)
{
    token t=d->pData.actualToken;
    tokenType typeOfresult;
    switch (t.type)
    {
        case T_INT:
        case T_STR_LEN:
        case T_STR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
        case T_LBR: 
        case T_ADD:
        case T_SUB:
            typeOfresult=expresionParse(d);
            if(numOfAsigens>0)
            {
                assigenCompCheck(d->pData.expresionBuffer.array[d->pData.expresionBuffer.last-numOfAsigens].type,typeOfresult,true);     
            }
            else
                genInst("POPS gf@&NULL");
        break;  
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type==T_COMMA)
    {
        t=next(d);
        LLexpresionN(d,numOfAsigens-1);
    }
    else if(numOfAsigens>1)
        errorD(5,"počet výrazů je menší než počet identifikátorů v příkazu přiřazení");
    else if(numOfAsigens>0)
        stackPop(&d->pData.expresionBuffer);

}

void assigenCompCheck(tokenType a,tokenType b,bool isAsigen)
{
    if(a==b)
        return;
    else if(b==K_NIL)
        return;
    else
    {
        if(a==K_NUMBER&&b==K_INTEGER)
            printf("CALL sefeIntToFloat\n");
        else if(isAsigen)
            errorD(4,"Typová nekompabilita v příkazu přiřazení");
        else
            errorD(5,"Typová nekompabilita v návratových typů");
    }
}

STFuncData* LLfuncCall(systemData *d,int numOfAsigens)
{
    STSymbolPtr *node=frameStackSearchFunc(&d->pData.dataModel,d->sData.fullToken.str);
    if(!node)
        errorD(3,"funkce není deklarována");
    STData * data=&(*node)->data;
    if(data->type!=ST_FUNC)
        errorD(3,"proměnná nelze zavolat");
    if(numOfAsigens>data->funcData->retNum)
        errorD(3,"Funkce nevrací tolik parametů");    
    token t=next(d);
    switch (t.type)
    {   
        case T_ID: 
        case T_INT:
        case T_STR:
        case K_NIL:
        case T_DOUBLE:
        case T_LBR:
        case T_STR_LEN:
        case T_SUB:
        case T_ADD:
            LLfArgN(d,0,data);
        break;
        case T_RBR: 
            if(data->funcData->paramNum>0)
                errorD(5,"počty argumentů ve volání funkce nesouhlasí");
        break;  
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type!=T_RBR)
        LLerr();
    
    if(!(data->funcData->paramNum<0))
        fprintf(stdin,"CALL FCSTART$%ld$%s\n",data->dekorator,(*node)->id);
    next(d);
    
    return data->funcData;
}

void LLfArgN(systemData *d,int order,STData * Fdata)
{   
    token t=d->pData.actualToken;
    tokenType expT;
    switch (t.type)
    {   
        case T_INT:
        case T_STR_LEN:
        case T_STR:
        case K_NIL:
        case T_DOUBLE:
        case T_ID: 
        case T_LBR: 
        case T_ADD:
        case T_SUB:
            expT =expresionParse(d);
            if(Fdata->funcData->paramNum>=0)
            {
                if(!(Fdata->funcData->paramNum>order))
                    errorD(5,"počty argumentů ve volání funkce nesouhlasí");
                assigenCompCheck(Fdata->funcData->paramTypes[order],expT,false);
            }
            else if(Fdata->funcData->paramNum<0)    //negative num of args means write instruction
            {
                genWrite();
            }
        break;  
        default:
            LLerr();
        break;
    }
    if(d->pData.actualToken.type==T_RBR)
    {
        return;
    }
    else if(d->pData.actualToken.type==T_COMMA)
    {
        next(d);
        LLfArgN(d,order+1,Fdata);
    }
    else
        LLerr();
}

token next(systemData *d)
{
    d->pData.actualToken=getNextUsefullToken(&d->sData);
    return d->pData.actualToken;
}

void initParserData(parserData * data)
{
    frameStackInit(&data->dataModel);
    frameStack_initPreFunctions(&data->dataModel);
    stackInit(&data->expresionBuffer);
    stackInit(&data->varDeclarationBuffer);
    data->isInWhile=false;
}

void destructParserData(parserData * data)
{
    frameStackDisporse(&data->dataModel);
    stackDestruct(&data->expresionBuffer);
    stackDestruct(&data->varDeclarationBuffer);
}

void systemDataInit(systemData * data)
{
    initScanerData(&data->sData);
    initParserData(&data->pData);
    initExpresionData(&data->epData);
    data->dekoratorIds=1;//0 is for global vars
    data->dekoratorJumps=0;
}

void systemDataDestruct(systemData * data)
{
    destructScanerData(&data->sData);
    destructParserData(&data->pData);
    destructExpresionData(&data->epData);
}

void decorId(systemData * data,STData * toDecorate)
{
    toDecorate->dekorator=data->dekoratorIds;
}

void changeRangeScope(systemData * d,bool IsFunc)
{
    frameStackPushFrame(&d->pData.dataModel,IsFunc);
    d->dekoratorIds++;
}

void LLerr()
{
    errorD(2,"Chyba při kontrole syntaxe-porušeno rozkladové pravidlo.");
}
