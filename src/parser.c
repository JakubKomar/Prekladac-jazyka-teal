/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "parser.h"

void parserMain(systemData * sData)
{
    token actualToken=getNextUsefullToken(&sData->sData);
    stack * stack=&(sData->pData.stack);

    while (!stackEmpty(stack))
    {    
        debug("actual token: %s\n",tokenStr(actualToken));    
        stackPrint(stack);
        debugS("-------------------------------------------------------\n");  
        if(stackHead(stack).type>=N_START)//pokud neterminál
        {
            useLLtable(actualToken,stack);
        }
        else if(stackHead(stack).type==S_EXPRESION)
        {
            stackPop(stack);
            expresionParse(sData);
        }
        else
        {
            if(stackHead(stack).type==actualToken.type)
            {
                stackPop(stack);
                debug("conzume: %s\n",tokenStr(actualToken));
                actualToken=getNextUsefullToken(&sData->sData);
            }
            else
            {
                errorD(2,"Terminál na zásabníku se neschoduje s aktuálním terminálem");
            }
        }
    } 
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

void useLLtable(token Token,stack *stack) 
{
    tokenType actualToken=Token.type;
    switch (stackPop(stack).type)
    {
        case N_START:
            switch (actualToken)
            {
                case K_REQUIRE: 
                    stackPush(stack,(token){N_PROG,NULL});
                    stackPush(stack,(token){N_PROLOG,NULL}); 
                break;    
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_PROLOG:
            switch (actualToken)
            {
                case K_REQUIRE:
                    stackPush(stack,(token){T_STR,NULL});  
                    stackPush(stack,(token){K_REQUIRE,NULL});
                break;    
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_PROG:
            switch (actualToken)
            {
                case T_EOF:
    
                break;   
                case T_ID:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_EXP_OR_FUNC,NULL}); 
                    stackPush(stack,(token){T_ASSIGEN,NULL}); 
                    stackPush(stack,(token){N_ID_NEXT,NULL}); 
                    stackPush(stack,(token){T_ID,NULL}); 
                break;  
                case T_FUNC_CALL:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_FUNC_CALL,NULL});  
                break;  
                case K_WHILE:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_WHILE,NULL});  
                break;  
                case K_END:

                break;  
                case K_IF:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_IF,NULL});  
                break; 
                case K_ELSE:

                break; 
                case K_FUNCTION:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_FUNCTION,NULL});  
                break; 
                case K_RETURN:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_RETURN,NULL});  
                break; 
                case K_LOCAL:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_DECLARATION,NULL});  
                break; 
                case K_GLOBAL:
                    stackPush(stack,(token){N_PROG,NULL});  
                    stackPush(stack,(token){N_DECLARATION,NULL});  
                break; 
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_EXP_OR_FUNC:
            switch (actualToken)
            {
                case T_INT:
                case T_STR_LEN:
                case T_STR:
                case K_NIL:
                case T_DOUBLE:
                case T_ID: 
                    stackPush(stack,(token){N_EXPRESIONS,NULL});
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                break;  
                case T_FUNC_CALL: 
                    stackPush(stack,(token){N_FUNC_CALL,NULL});
                break;  
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_FUNC_CALL:
            switch (actualToken)
            {
                case T_FUNC_CALL: 
                    stackPush(stack,(token){T_RBR,NULL}); 
                    stackPush(stack,(token){N_F_ARG,NULL}); 
                    stackPush(stack,(token){T_FUNC_CALL,NULL}); 
                break;  
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_F_ARG:
            switch (actualToken)
            {
                case T_RBR: 

                break;  
                case T_INT:
                case T_STR:
                case T_STR_LEN:
                case K_NIL:
                case T_DOUBLE:
                case T_ID: 
                    stackPush(stack,(token){N_F_ARG_N,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                break;  
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_F_ARG_N:
            switch (actualToken)
            {
                case T_RBR: 

                break;  
                case T_COMMA: 
                    stackPush(stack,(token){N_F_ARG_N,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;  
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_ID_NEXT:
            switch (actualToken)
            {
                case T_ASSIGEN: 

                break;   
                case T_COMMA: 
                    stackPush(stack,(token){N_ID_NEXT,NULL}); 
                    stackPush(stack,(token){T_ID,NULL}); 
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;  
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_EXPRESIONS:
            switch (actualToken)
            {
                case T_EOF: 
                case K_RETURN:
                case T_ID:  
                case T_FUNC_CALL: 
                case K_WHILE: 
                case K_END: 
                case K_ELSE: 
                case K_FUNCTION: 
                case K_GLOBAL: 
                case K_LOCAL: 
                case K_IF:  

                break; 
                case T_COMMA: 
                    stackPush(stack,(token){N_EXPRESIONS,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;  
                default:
                    LLTableErr();
                break;
            }      
        break;
        case N_WHILE:
            switch (actualToken)
            {
                case K_WHILE: 
                    stackPush(stack,(token){K_END,NULL}); 
                    stackPush(stack,(token){N_PROG,NULL}); 
                    stackPush(stack,(token){K_DO,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                    stackPush(stack,(token){K_WHILE,NULL}); 
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_IF:
            switch (actualToken)
            {
                case K_IF: 
                    stackPush(stack,(token){K_END,NULL}); 
                    stackPush(stack,(token){N_ELSE_M,NULL}); 
                    stackPush(stack,(token){N_PROG,NULL}); 
                    stackPush(stack,(token){K_THEN,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                    stackPush(stack,(token){K_IF,NULL}); 
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_ELSE_M:
            switch (actualToken)
            {
                case K_END: 

                break; 
                case K_ELSE: 
                    stackPush(stack,(token){N_PROG,NULL}); 
                    stackPush(stack,(token){K_ELSE,NULL}); 
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_FUNCTION:
            switch (actualToken)
            {
                case K_FUNCTION: 
                    stackPush(stack,(token){K_END,NULL}); 
                    stackPush(stack,(token){N_PROG,NULL}); 
                    stackPush(stack,(token){N_RETURN_D,NULL}); 
                    stackPush(stack,(token){T_RBR,NULL}); 
                    stackPush(stack,(token){N_ARG,NULL}); 
                    stackPush(stack,(token){T_FUNC_CALL,NULL}); 
                    stackPush(stack,(token){K_FUNCTION,NULL});
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_ARG:
            switch (actualToken)
            {
                case T_ID: 
                    stackPush(stack,(token){N_ARGNEXT,NULL}); 
                    stackPush(stack,(token){N_TYPE,NULL}); 
                    stackPush(stack,(token){T_COLON,NULL}); 
                    stackPush(stack,(token){T_ID,NULL}); 
                break; 
                case T_RBR: 
                break;  
                default:
                    LLTableErr();
                break;
            }
        break;  
        case N_ARGNEXT:
            switch (actualToken)
            {
                case T_RBR: 
                break;  
                case T_COMMA: 
                    stackPush(stack,(token){N_ARGNEXT,NULL}); 
                    stackPush(stack,(token){N_TYPE,NULL}); 
                    stackPush(stack,(token){T_COLON,NULL}); 
                    stackPush(stack,(token){T_ID,NULL});  
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RETURN_D:
            switch (actualToken)
            {
                case T_COLON: 
                    stackPush(stack,(token){N_RETURN_DN,NULL}); 
                    stackPush(stack,(token){N_TYPE,NULL}); 
                    stackPush(stack,(token){T_COLON,NULL}); 
                break;   
                case T_ID:
                case T_FUNC_CALL:
                case K_WHILE:
                case K_END:
                case K_IF:
                case K_FUNCTION:
                case K_RETURN:
                case K_LOCAL:
                case K_GLOBAL:

                break;
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RETURN_DN:
            switch (actualToken)
            {
                case T_COMMA: 
                    stackPush(stack,(token){N_RETURN_DN,NULL}); 
                    stackPush(stack,(token){N_TYPE,NULL}); 
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;  
                case T_ID:
                case T_FUNC_CALL:
                case K_WHILE:
                case K_END:
                case K_IF:
                case K_FUNCTION:
                case K_RETURN:
                case K_LOCAL:
                case K_GLOBAL:
                
                break; 
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RETURN:
            switch (actualToken)
            {
                case K_RETURN: 
                    stackPush(stack,(token){N_RETURN_ARG,NULL}); 
                    stackPush(stack,(token){K_RETURN,NULL}); 
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RETURN_ARG:
            switch (actualToken)
            {
                case T_INT:
                case T_STR:
                case T_STR_LEN:
                case K_NIL:
                case T_DOUBLE:
                case T_ID: 
                    stackPush(stack,(token){N_RETURN_ARG_N,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                break;   
                case K_END:
                case K_ELSE:
                case T_EOF:

                break; 
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RETURN_ARG_N:
            switch (actualToken)
            {
                case T_COMMA: 
                    stackPush(stack,(token){N_RETURN_ARG_N,NULL}); 
                    stackPush(stack,(token){S_EXPRESION,NULL}); 
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break; 
                case K_END:
                case K_ELSE:
                case T_EOF:

                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_DECLARATION:
            switch (actualToken)
            {
                case K_LOCAL: 
                case K_GLOBAL: 
                    stackPush(stack,(token){N_DECLARATION_T,NULL});
                    stackPush(stack,(token){T_COLON,NULL});
                    stackPush(stack,(token){T_ID,NULL});
                    stackPush(stack,(token){N_RANGE,NULL});
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_DECLARATION_T:
            switch (actualToken)
            {
                case K_NUMBER: 
                case K_INTEGER: 
                case K_STRING: 
                case K_NIL:
                    stackPush(stack,(token){N_ASSIGEN_MAY,NULL});
                    stackPush(stack,(token){N_TYPE,NULL});
                break;  
                case K_FUNCTION: 
                    stackPush(stack,(token){N_RET_D,NULL});
                    stackPush(stack,(token){T_COLON,NULL});
                    stackPush(stack,(token){T_RBR,NULL});
                    stackPush(stack,(token){N_ARG_D,NULL});
                    stackPush(stack,(token){T_LBR,NULL});
                    stackPush(stack,(token){K_FUNCTION,NULL});
                break;      
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_ARG_D:
            switch (actualToken)
            {
                case K_NUMBER: 
                case K_INTEGER: 
                case K_STRING: 
                case K_NIL:
                    stackPush(stack,(token){N_ARG_DN,NULL});
                    stackPush(stack,(token){N_TYPE,NULL});
                break;  
                case T_RBR: 
                    
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_ARG_DN:
            switch (actualToken)
            {
                case T_COMMA: 
                    stackPush(stack,(token){N_ARG_DN,NULL});
                    stackPush(stack,(token){N_TYPE,NULL});
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;  
                case T_RBR: 
                    
                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RET_D:
            switch (actualToken)
            {
                case T_COLON: 
                    stackPush(stack,(token){N_ARG_DN,NULL});
                    stackPush(stack,(token){N_TYPE,NULL});
                    stackPush(stack,(token){T_COLON,NULL}); 
                break;  
                case K_NUMBER: 
                case K_INTEGER: 
                case K_STRING: 
                case K_NIL:
                    stackPush(stack,(token){N_RET_DN,NULL});
                    stackPush(stack,(token){N_TYPE,NULL});
                break;
                case T_EOF: 
                case T_ID:
                case T_FUNC_CALL:
                case K_WHILE:
                case K_END:
                case K_IF:
                case K_FUNCTION:
                case K_RETURN:
                case K_LOCAL:
                case K_GLOBAL:
                case K_ELSE:

                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RET_DN:
            switch (actualToken)
            {
                case T_COMMA: 
                    stackPush(stack,(token){N_RET_DN,NULL});
                    stackPush(stack,(token){N_TYPE,NULL});
                    stackPush(stack,(token){T_COMMA,NULL}); 
                break;  
                case T_EOF: 
                case T_ID:
                case T_FUNC_CALL:
                case K_WHILE:
                case K_END:
                case K_IF:
                case K_FUNCTION:
                case K_RETURN:
                case K_LOCAL:
                case K_GLOBAL:
                case K_ELSE:

                break;   
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_ASSIGEN_MAY:
            switch (actualToken)
            {
                case T_ASSIGEN: 
                    stackPush(stack,(token){N_EXP_OR_FUNC,NULL}); 
                    stackPush(stack,(token){T_ASSIGEN,NULL}); 
                break;  
                case T_EOF: 
                case T_ID:
                case T_FUNC_CALL:
                case K_WHILE:
                case K_END:
                case K_IF:
                case K_FUNCTION:
                case K_RETURN:
                case K_LOCAL:
                case K_GLOBAL:
                case K_ELSE:

                break;    
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_TYPE:
            switch (actualToken)
            {
                case K_NUMBER: 
                    stackPush(stack,(token){K_NUMBER,NULL});
                break;    
                case K_INTEGER: 
                    stackPush(stack,(token){K_INTEGER,NULL});
                break;    
                case K_STRING: 
                    stackPush(stack,(token){K_STRING,NULL});
                break;
                case K_NIL:
                    stackPush(stack,(token){K_NIL,NULL});
                break;
                default:
                    LLTableErr();
                break;
            }
        break;
        case N_RANGE: 
            switch (actualToken)
            {
                case K_LOCAL: 
                    stackPush(stack,(token){K_LOCAL,NULL}); 
                break; 
                case K_GLOBAL: 
                    stackPush(stack,(token){K_GLOBAL,NULL}); 
                break;  
                default:
                    LLTableErr();
                break;
            }
        break; 
        default:
            LLTableErr();
        break;
    }
}
void LLTableErr()
{
    errorD(2,"Pro daný neterminál nebyl nalezen rozklad");
}