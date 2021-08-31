/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once


#include <stdbool.h>
#include <malloc.h>
#include "./../scaner.h"
#include "./../baseDeclarations.h"

#define STACK_SIZE 200  //počateční velkost zásobníku

typedef struct Stack {
    int size;   //Velikost zásobníku
    int last;    //Spodek zásobníku
    tokenType *array;   //Pole pro zásobník
}*pStack;

/**
 * stack constructor
 * @param *S- stack to init
 */
void StackInit(pStack *S);
/**
 * string destructor
 * @param *S- stack to init
 */
void StackDestruct(pStack* S);
/**
 * stack push operation
 * @param *S- stack to pushm type-token to push
 */
void StackPush(pStack S, tokenType type);
/**
 * stack pop operation
 * @param *S- stack to pop
 * @return poped token
 */
tokenType StackPop(pStack S);
/**
 * return head of stack
 * @param *S- stack to operate whith
 * @return head of stack
 */
tokenType StackHead(pStack S);
/**
 * printing stack for debug
 * @param *S- stack to print
 */
void printStack(pStack *s);