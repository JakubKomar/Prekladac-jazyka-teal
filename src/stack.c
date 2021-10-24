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
    s->array=malloc(sizeof(token)*STACK_BASE_SIZE);
    if(!s->array)
        errorD(100,"Stack initialization error");
}

void stackDestruct(stack *s)
{
    free(s->array);
}

void stackRealoc(stack *s)
{
    s->capacity=s->capacity*2;
    s->array=realloc(s->array,sizeof(token)* s->capacity);
    if(!s->array)
        errorD(100,"Stack realoc error");
}

void stackPush(stack *s, token token)
{
    if(stackFull(s))
        stackRealoc(s);
    s->last++;
    s->array[s->last-1]=token;
}

token stackPop(stack *s)
{
    if(stackEmpty(s))
        errorD(99,"Stack owerflow");
    s->last--;
    return s->array[s->last];
}

token stackHead(stack *s)
{
    if(stackEmpty(s))
        errorD(99,"Stack is empty");
    return s->array[s->last-1];
}

void stackInsertHanle(stack *s)
{
    int i =s->last-1;
    for (; i>=0 ;i--)
    {
        if(s->array[i].type<O_HANDLE)
        {
            break;
        }
    }
    if(i>s->last-1)
        errorD(99,"cant insert handle behind dolar");
    stackShiftRight(s,i);
    s->array[i+1].type=O_HANDLE;
}

void stackPrint(stack *s)
{
    debugS("Stack debug extract:\n");
    for (int i =0; i <s->last ; i++)
        debug("%-4d. %s\n",i,tokenStr(s->array[i]));
    debugS("↑Head of stack is here.↑\n");
}

bool stackFull(stack *s)
{
    return s->capacity<=s->last;
}

bool stackEmpty(stack *s)
{
    return s->last==0;
}

void stackClear(stack *s)
{
    s->last=0;
}

token stackTop(stack *s)
{
    for (int i =s->last-1; i>=0 ;i--)
    {
        if(s->array[i].type <O_HANDLE)
        {
            return s->array[i];
        }
    }
    return (token){O_ERR};
}

void stackRemoveHande(stack *s)
{
    if(stackPop(s).type!=O_HANDLE)
        errorD(99,"handle isnt on top of stack");
}

void stackShiftRight(stack *s,int wege)
{
    token empty={O_UNIMPORTANT};
    stackPush(s,empty);
    for (int i =s->last-1; i>wege ;i--)
    {
        s->array[i]=s->array[i-1];
    }   
}   