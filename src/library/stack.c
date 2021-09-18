/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "stack.h"


void stackInit(pStack *S)
{

}

void stackPush(pStack S, tokenType type)
{

}

tokenType stackPop(pStack S)
{
    return T_ADD;
}

tokenType stackHead(pStack S)
{
     return T_ADD;
}

void stackDestruct(pStack *S)
{

}

void stackPrint(pStack s)
{
    fprintf(stderr,"Stack debug extract:");
    for (int i =0; i <=s->last ; i++)
        fprintf(stderr,"%-4d. %d\n",i,s->array[i]);
    fprintf(stderr,"Head of stack is here.");
}

bool stackEmpty(pStack s)
{
    return true;
}