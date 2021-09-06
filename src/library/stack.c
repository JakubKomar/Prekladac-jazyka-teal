/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "stack.h"


void StackInit(pStack *S)
{
    *S = malloc(sizeof(struct Stack));
    if((*S)==NULL)
        errorD(99,"stack aloc error");

    (*S)->last = -1;
    (*S)->array = malloc(STACK_SIZE * sizeof(tokenType));
    
    if(((*S)->array)==NULL)
        errorD(99,"stack aloc error");
    (*S)->size = STACK_SIZE;
}

void StackPush(pStack S, tokenType type)
{
    if(S->last >= S->size)
    {
        S->size = S->size + STACK_SIZE;
        S->array = realloc(S->array, S->size*sizeof(tokenType));
        if((S->array)==NULL)
            errorD(99,"stack realoc error");
    }
    S->last++;
    S->array[S->last] = type;
}

tokenType StackPop(pStack S)
{
    if(S->last < 0)
        errorD(99,"stack underflow");
    else
        S->last--;  
    return(S->array[ S->last+1]);
}
tokenType StackHead(pStack S)
{
    if(S->last<0)       
        errorD(99,"reading from empty stack");
    return(S->array[S->last]);
}

void StackDestruct(pStack *S)
{
    free((*S)->array);
    free(*S);
}

void printStack(pStack s)
{
    fprintf(stderr,"Stack debug extract:");
    for (int i =0; i <=s->last ; i++)
        fprintf(stderr,"%-4d. %d\n",i,s->array[i]);
    fprintf(stderr,"Head of stack is here.");
}
bool emptyStack(pStack s){
    return (s->last<0);
}