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
    debugS("Stack debug extract:");
    for (int i =1; i <=s->last ; i++)
        debug("%-4d. %d\n",i,s->array[i]);
    debugS("Head of stack is here.↑");
}

bool stackEmpty(pStack s)
{
    return true;
}