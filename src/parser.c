/**
 * @brief   parser
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "parser.h"

void parserMain(){
    scanerData scData;
    tokenType actualToken=N_START;
    initScanerData(&scData);
    
    stack stack;
    stackInit(&stack);
    stackPush(&stack,T_EOF);
    stackPush(&stack,N_START);

    while (stackEmpty(&stack))
    {
        if(stackHead(&stack)>=N_START)//pokud neterminál
        {
            useLLtable(actualToken,&stack);
        }
        else
        {
            if(stackHead(&stack)==actualToken)
            {
                stackPop(&stack);
                getNextToken(&scData);
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
                    stackPush(stack,K_STRING);  
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
                    stackPush(stack,N_EXPRESIONS);  
                    stackPush(stack,S_EXPRESION); 
                    stackPush(stack,T_ASSIGEN); 
                    stackPush(stack,N_ID_NEXT); 
                    stackPush(stack,T_ID); 
                break;  
                case K_WHILE:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_WHILE);  
                break;  
                case K_END:

                break;  
                case K_IF:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,K_IF);  
                break; 
                case K_ELSE:

                break; 
                case K_FUNCTION:
                    stackPush(stack,N_PROG);  
                    stackPush(stack,N_FUNCTION);  
                break; 
                case K_RETURN:

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
        case N_ID_NEXT:
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
        case N_EXPRESIONS:
        
        break;
        
        break;
        case N_WHILE:
        
        break;
        case N_IF:
        
        break;
        case N_ELSE_M:
        
        break;
        case N_FUNCTION:
        
        break;
        case N_ARG:
        
        break;
        case N_ARGNEXT:
        
        break;
        case N_RETURN_D:
        
        break;
        case N_RETURN_DN:
        
        break;
        case N_RETURN:
        
        break;
        case N_RETURN_ARG:
        
        break;
        case N_RETURN_ARG_N:
        
        break;
        case N_DECLARATION:
        
        break;
        case N_DECLARATION_T:
        
        break;
        case N_ARG_D:
        
        break;
        case N_ARG_DN:
        
        break;
        case N_ASSIGEN_MAY:
        
        break;
        case N_TYPE:
        
        break;
        case N_RANGE: 

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