/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "stack.h"


void stackInit(stack *s)
{
    s->capacity=STACK_BASE_SIZE;
    s->last=0;
    s->array=malloc(sizeof(tokenType)*STACK_BASE_SIZE);
    if(!s->array)
        errorD(99,"Stack initialization error");
}

void stackRealoc(stack *s)
{
    s->capacity=s->capacity*2;
    s->array=realloc(s->array,sizeof(tokenType)* s->capacity);
    if(!s->array)
        errorD(99,"Stack realoc error");
}

void stackPush(stack *s, tokenType type)
{
    if(stackFull(s))
        stackRealoc(s);
    s->last++;
    s->array[s->last-1]=type;
}

tokenType stackPop(stack *s)
{
    if(stackEmpty(s))
        errorD(99,"Stack owerflow");
    s->last--;
    return s->array[s->last];
}

tokenType stackHead(stack *s)
{
    if(stackEmpty(s))
        errorD(99,"Stack is empty");
    return s->array[s->last-1];
}

void stackDestruct(stack *s)
{
    free(s->array);
}

void stackPrint(stack *s)
{
    debugS("Stack debug extract:\n");
    for (int i =0; i <s->last ; i++)
        debug("%-4d. %d\n",i,s->array[i]);
    debugS("↑Head of stack is here.↑");
}

bool stackFull(stack *s)
{
    return s->capacity<=s->last;
}

bool stackEmpty(stack *s)
{
    return s->last==0;
}