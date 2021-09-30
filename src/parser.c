/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "parser.h"
#include <signal.h>

void parserMain(){
    scanerData scData;
    initScanerData(&scData);
    tokenType actualToken=getNextUsefullToken(&scData);
    stack stack;
    stackInit(&stack);
    stackPush(&stack,T_EOF);
    stackPush(&stack,N_START);
    while (!stackEmpty(&stack))
    {    
        debug("actual token: %s\n",tokenStr(actualToken));    
        stackPrint(&stack);
        debugS("-------------------------------------------------------\n");  
        if(stackHead(&stack)>=N_START)//pokud neterminál
        {
            useLLtable(actualToken,&stack);
        }
        else if(stackHead(&stack)==S_EXPRESION)
        {
            stackPop(&stack);
            actualToken=expresionDevelop(actualToken,&scData);
        }
        else
        {
            if(stackHead(&stack)==actualToken)
            {
                stackPop(&stack);
                debug("conzume: %s\n",tokenStr(actualToken));
                actualToken=getNextUsefullToken(&scData);
            }
            else
            {
                errorD(32,"Terminál na zásabníku se neschoduje s aktuálním terminálem");
            }
        }
    }   
}

void useLLtable(tokenType actualToken,stack *stack) 
{
    switch (stackPop(stack))
    {
        case N_START:
            switch (actualToken)
            {
                case K_REQUIRE: 
                    stackPush(stack,N_PROG);
                    stackPush(stack,N_PROLOG); 
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
                    stackPush(stack,T_STR);  
                    stackPush(stack,K_REQUIRE);
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
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_EXP_OR_FUNC); 
                    stackPush(stack,T_ASSIGEN); 
                    stackPush(stack,N_ID_NEXT); 
                    stackPush(stack,T_ID); 
                break;  
                case T_FUNC_CALL:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_FUNC_CALL);  
                break;  
                case K_WHILE:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_WHILE);  
                break;  
                case K_END:

                break;  
                case K_IF:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_IF);  
                break; 
                case K_ELSE:

                break; 
                case K_FUNCTION:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_FUNCTION);  
                break; 
                case K_RETURN:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_RETURN);  
                break; 
                case K_LOCAL:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_DECLARATION);  
                break; 
                case K_GLOBAL:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_DECLARATION);  
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
                    stackPush(stack,N_EXPRESIONS);
                    stackPush(stack,S_EXPRESION); 
                break;  
                case T_FUNC_CALL: 
                    stackPush(stack,N_FUNC_CALL);
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
                    stackPush(stack,T_RBR); 
                    stackPush(stack,N_F_ARG); 
                    stackPush(stack,T_FUNC_CALL); 
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
                    stackPush(stack,N_F_ARG_N); 
                    stackPush(stack,S_EXPRESION); 
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
                    stackPush(stack,N_F_ARG_N); 
                    stackPush(stack,S_EXPRESION); 
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_ID_NEXT); 
                    stackPush(stack,T_ID); 
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_EXPRESIONS); 
                    stackPush(stack,S_EXPRESION); 
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,K_END); 
                    stackPush(stack,N_PROG); 
                    stackPush(stack,K_DO); 
                    stackPush(stack,S_EXPRESION); 
                    stackPush(stack,K_WHILE); 
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
                    stackPush(stack,K_END); 
                    stackPush(stack,N_ELSE_M); 
                    stackPush(stack,N_PROG); 
                    stackPush(stack,K_THEN); 
                    stackPush(stack,S_EXPRESION); 
                    stackPush(stack,K_IF); 
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
                    stackPush(stack,N_PROG); 
                    stackPush(stack,K_ELSE); 
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
                    stackPush(stack,K_END); 
                    stackPush(stack,N_PROG); 
                    stackPush(stack,N_RETURN_D); 
                    stackPush(stack,T_RBR); 
                    stackPush(stack,N_ARG); 
                    stackPush(stack,T_FUNC_CALL); 
                    stackPush(stack,K_FUNCTION);
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
                    stackPush(stack,N_ARGNEXT); 
                    stackPush(stack,N_TYPE); 
                    stackPush(stack,T_COLON); 
                    stackPush(stack,T_ID); 
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
                    stackPush(stack,N_ARGNEXT); 
                    stackPush(stack,N_TYPE); 
                    stackPush(stack,T_COLON); 
                    stackPush(stack,T_ID);  
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_RETURN_DN); 
                    stackPush(stack,N_TYPE); 
                    stackPush(stack,T_COLON); 
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
                    stackPush(stack,N_RETURN_DN); 
                    stackPush(stack,N_TYPE); 
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_RETURN_ARG); 
                    stackPush(stack,K_RETURN); 
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
                    stackPush(stack,N_RETURN_ARG_N); 
                    stackPush(stack,S_EXPRESION); 
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
                    stackPush(stack,N_RETURN_ARG_N); 
                    stackPush(stack,S_EXPRESION); 
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_DECLARATION_T);
                    stackPush(stack,T_COLON);
                    stackPush(stack,T_ID);
                    stackPush(stack,N_RANGE);
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
                    stackPush(stack,N_ASSIGEN_MAY);
                    stackPush(stack,N_TYPE);
                break;  
                case K_FUNCTION: 
                    stackPush(stack,N_RET_D);
                    stackPush(stack,T_COLON);
                    stackPush(stack,T_RBR);
                    stackPush(stack,N_ARG_D);
                    stackPush(stack,T_LBR);
                    stackPush(stack,K_FUNCTION);
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
                    stackPush(stack,N_ARG_DN);
                    stackPush(stack,N_TYPE);
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
                    stackPush(stack,N_ARG_DN);
                    stackPush(stack,N_TYPE);
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_ARG_DN);
                    stackPush(stack,N_TYPE);
                    stackPush(stack,T_COLON); 
                break;  
                case K_NUMBER: 
                case K_INTEGER: 
                case K_STRING: 
                case K_NIL:
                    stackPush(stack,N_RET_DN);
                    stackPush(stack,N_TYPE);
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
                    stackPush(stack,N_RET_DN);
                    stackPush(stack,N_TYPE);
                    stackPush(stack,T_COMMA); 
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
                    stackPush(stack,N_EXP_OR_FUNC); 
                    stackPush(stack,T_ASSIGEN); 
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
                    stackPush(stack,K_NUMBER);
                break;    
                case K_INTEGER: 
                    stackPush(stack,K_INTEGER);
                break;    
                case K_STRING: 
                    stackPush(stack,K_STRING);
                break;
                case K_NIL:
                    stackPush(stack,K_NIL);
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
                    stackPush(stack,K_LOCAL); 
                break; 
                case K_GLOBAL: 
                    stackPush(stack,K_GLOBAL); 
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
    errorD(32,"Pro daný neterminál nebyl nalezen rozklad");
}