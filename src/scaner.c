/**
 * @brief   scaner
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "scaner.h"

token getNextUsefullToken(scanerData * data)
{
    tokenType tType;
    do
    {
       tType=getNextToken(data);
    } while (tType==O_UNIMPORTANT||tType==O_ERR);
    
    token next={tType};
    
    return next;
}

tokenType getNextToken(scanerData * data)
{
    state curentState=S_START;
    state prevState;
    stringClear(&(data->fullToken));
    data->write=true;

    while(true)
    {
        prevState=curentState;
        curentState=nextState(data,curentState);
        
        if(curentState==S_ERROR)
            break;
        else if(curentState==S_EOF)
            return T_EOF;
        if(data->write)
            stringAddChar(&(data->fullToken),data->curentSymbol);
        loadChar(data);
    }
    tokenType token= getTokenFromState(prevState);
    if(token==O_ERR)
        errorD(1,"není koncový stav");  
    else if(token==T_ID||token==T_FUNC_CALL)
        token=checkKeywords(data,token);
    return token;
}

tokenType checkKeywords(scanerData *data,tokenType type)
{
    char *s=data->fullToken.str;
    tokenType token;
    if(!strcmp(s,"do"))
        token=K_DO;
    else if(!strcmp(s,"else"))
        token=K_ELSE;
    else if(!strcmp(s,"end"))
        token=K_END;
    else if(!strcmp(s,"function"))
        return K_FUNCTION;
    else if(!strcmp(s,"global"))
        token=K_GLOBAL;
    else if(!strcmp(s,"if"))
        token=K_IF;
    else if(!strcmp(s,"local"))
        token=K_LOCAL;
    else if(!strcmp(s,"nil"))
        token=K_NIL;
    else if(!strcmp(s,"read"))
        token=K_READ;
    else if(!strcmp(s,"require"))
        token=K_REQUIRE;
    else if(!strcmp(s,"return"))
        token=K_RETURN;
    else if(!strcmp(s,"then"))
        token=K_THEN;
    else if(!strcmp(s,"while"))
        token=K_WHILE;
    else if(!strcmp(s,"integer"))
        token=K_INTEGER;
    else if(!strcmp(s,"string"))
        token=K_STRING;
    else if(!strcmp(s,"number"))
        token=K_NUMBER;
    else
        token=T_ID;

    if(type==T_FUNC_CALL&&token!=T_ID)
    {
        errorD(3,"Klíčové slovo se nesmí vyskytovat v názvu funkce");
        return O_ERR;
    }
    else if(type==T_FUNC_CALL&&token==T_ID)
        return T_FUNC_CALL;
    else
        return token;
}

tokenType getTokenFromState(state state)
{
    tokenType token;
    switch (state)
    {
    case S_ID:
    case S_IDS:
        token=T_ID;
    break;
    case S_FUNC_CALL:
        token=T_FUNC_CALL;
    break;
    case S_SUB:
        token=T_SUB;
    break;
    case S_LINE_COM:
    case S_LINE_COM_2:
    case S_LINE_COM_PER:
    case S_BLOCK_COM3:
    case S_SPACE:
        token=O_UNIMPORTANT;
    break;
    case S_ADD:
        token=T_ADD;
    break;
    case S_DIV:
        token=T_DIV;
    break;
    case S_DIV2:
        token=T_DIV2;
    break;
    case S_MUL:
        token=T_MUL;
    break;
    case S_STR_LEN:
        token=T_STR_LEN;
    break;  
    case S_ASSIGEN:
        token=T_ASSIGEN;
    break; 
    case S_EQ:
        token=T_EQ;
    break;
    case S_NOT_EQ2:
        token=T_NOT_EQ;
    break; 
    case S_LT:
        token=T_LT;
    break; 
    case S_LTE:
        token=T_LTE;
    break; 
    case S_GT:
        token=T_GT;
    break; 
    case S_GTE:
        token=T_GTE;
    break; 
    case S_RBR:
        token=T_RBR;
    break;
    case S_LBR:
        token=T_LBR;
    break;   
    case S_COLON:
        token=T_COLON;
    break; 
    case S_COMMA:
        token=T_COMMA;
    break;
    case S_EOF:
        token=T_EOF;
    break;
    case S_STR2:
        token=T_STR;
    break;
    case S_INT:
    case S_INT0:
        token=T_INT;
    break;   
    case S_DOUBLE2:
    case S_EXP3:
        token=T_DOUBLE;
    break; 
    case S_DOT2:
        token=T_DOT2;
    break; 
    default:
        token=O_ERR;
    break;
    }
    return token;
}

state nextState(scanerData*data, state curentState)
{
    char sym=data->curentSymbol;
    state next=S_ERROR;
    switch (curentState)
    {
        case S_START:
            if(isLetter(sym)||sym=='_')
                next=S_ID;
            else if(sym=='-')
                next=S_SUB;
            else if(sym=='+')
                next=S_ADD;
            else if(sym=='/')
                next=S_DIV;   
            else if(sym=='*')
                next=S_MUL; 
            else if(sym=='#')
                next=S_STR_LEN;     
            else if(sym=='=')
                next=S_ASSIGEN;  
            else if(sym=='~')
                next=S_NOT_EQ1;  
            else if(sym=='<')
                next=S_LT; 
            else if(sym=='>')
                next=S_GT; 
            else if(sym==')')
                next=S_RBR; 
            else if(sym=='(')
                next=S_LBR; 
            else if(sym==':')
                next=S_COLON; 
            else if(sym==',')
                next=S_COMMA;
            else if(sym=='.')
                next=S_DOT1;
            else if(sym==EOF)
                next=S_EOF; 
            else if(sym==' '||sym=='\t'||sym=='\n')
                next=S_SPACE; 
            else if(sym=='\"')
                next=S_STR1; 
            else if(sym>='1'&&sym<='9')
                next=S_INT; 
            else if(sym=='0')
                next=S_INT0;
        break;
        case S_DOT1:
            if(sym=='.')
                next=S_DOT2;
        break;
        case S_ID:
            if(isLetter(sym)||isdigit(sym)||sym=='_')
                next=S_ID;
            else 
            {   
                if(sym=='(')
                    next=S_FUNC_CALL;
                else if(sym==' ')
                    next=S_IDS;
                data->write=false;
            }
        break;
        case S_IDS:
            if(sym==' ')
                next=S_IDS;
            else if(sym=='(')
                next=S_FUNC_CALL;
        break;
        case S_SUB:
            if(sym=='-')
                next=S_LINE_COM;
        break;
        case S_LINE_COM:
            if(sym=='[')
                next=S_LINE_COM_2; 
            else if(sym!='\n'&&sym!=EOF)
                next=S_LINE_COM_PER; 
        break;
        case S_LINE_COM_PER:
            if(sym!='\n'&&sym!=EOF)
                next=S_LINE_COM_PER; 
        break;
        case S_LINE_COM_2:
            if(sym=='[')
                next=S_BLOCK_COM; 
            else if(sym!='\n'&&sym!=EOF)
                next=S_LINE_COM_PER; 
        break;
        case S_BLOCK_COM:
            if(sym==']')
                next=S_BLOCK_COM2;
            else if(sym!=EOF)
                next=S_BLOCK_COM;     
        break;
        case S_BLOCK_COM2:
            if(sym==']')
                next=S_BLOCK_COM3;
            else if(sym!=EOF)
                next=S_BLOCK_COM;     
        break;
        case S_DIV:
            if(sym=='/')
                next=S_DIV2;
        break;
        case S_ASSIGEN:
            if(sym=='=')
                next=S_EQ;
        break;
        case S_NOT_EQ1:
            if(sym=='=')
                next=S_NOT_EQ2;
        break;
        case S_LT:
            if(sym=='=')
                next=S_LTE;
        break;
        case S_GT:
            if(sym=='=')
                next=S_GTE;
        break;        
        case S_SPACE:
            if(sym==' '||sym=='\t'||sym=='\n')
                next=S_SPACE;
        break;
        case S_STR1:
            if(sym=='\\')
                next=S_ESC1;
            else if(sym=='\"')
                next=S_STR2;
            else if(sym>31)
                next=S_STR1;
        break;
        case S_ESC1:
            if(sym=='\"'||sym=='n'||sym=='t'||sym=='\\')
                next=S_STR1;
            else if(sym=='2')
                next=S_ESC2;
            else if(sym=='0'||sym=='1')
                next=S_ESC4;
        break;
        case S_ESC2:
            if(sym=='5')
                next=S_ESC3;
            else if(sym>='0'&&sym<='4')
                next=S_ESC5;
        break;
        case S_ESC3:
            if(sym>='0'&&sym<='5')
                next=S_STR1;
        break;
        case S_ESC4:
            if(isDecimal(sym))
                next=S_ESC5;
        break;
        case S_ESC5:
            if(isDecimal(sym))
                next=S_STR1;
        break;
        case S_INT:
            if(sym=='.')
                next=S_DOUBLE1;
            else if(sym=='e'||sym=='E')
                next=S_EXP1;
            else if(isDecimal(sym))
                next=S_INT;
        break;
        case S_INT0:
            if(isDecimal(sym))
                next=S_TRAP;
            else if(sym=='e'||sym=='E')
                next=S_EXP1;
            else if(sym=='.')
                next=S_DOUBLE1;
        break;
        case S_DOUBLE1:
            if(isDecimal(sym))
                next=S_DOUBLE2;
        break;
        case S_DOUBLE2:
            if(isDecimal(sym))
                next=S_DOUBLE2;
            else if(sym=='e'||sym=='E')
                next=S_EXP1;
        break;
        case S_EXP1:
            if(isDecimal(sym))
                next=S_EXP3;
            else if(sym=='+'||sym=='-')
                next=S_EXP2;
        break;
        case S_EXP2:
            if(isDecimal(sym))
                next=S_EXP3;
        break;
        case S_EXP3:
            if(isDecimal(sym))
                next=S_EXP3;
        break;
        default:
        break;
    }
    return next;
}

bool isLetter(char toCompare)
{
    return (toCompare>='a'&&toCompare<='z') || (toCompare>='A'&&toCompare<='Z');
}

bool isDecimal(char toCompare)
{
    return toCompare>='0'&&toCompare<='9';
}

void initScanerData(scanerData * data)
{
    data->write=true;
    data->colum=0;
    data->line=0;
    stringInit(&(data->fullToken));
    stringInit(&(data->fullLine));
    loadChar(data);
} 

void destructScanerData(scanerData * data)
{
    stringDestruct(&data->fullToken);
    stringDestruct(&data->fullLine);
}

void loadChar(scanerData * data)
{
    data->curentSymbol=fgetc(INPUT);
    
    if(data->curentSymbol=='\n')
    {
        stringClear(&data->fullLine);
        data->colum=0;
        data->line++;
    }
    else
    {
        stringAddChar(&data->fullLine, data->curentSymbol);
        data->colum++;
    }
}

void errorVisualization(scanerData * data)
{
    fprintf(stderr,"\nIn input: L:%d C:%d :\n%s \033[35m<-\033[31mERROR\033[0m is near by\n",data->line,data->colum,data->fullLine.str);
}