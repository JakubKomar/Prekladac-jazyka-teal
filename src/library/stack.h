/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once


#include <stdbool.h>
#include <malloc.h>
#include "./../baseDeclarations.h"

#define STACK_BASE_SIZE 200  //počateční velkost zásobníku

typedef struct Stack {
    int size;   //Velikost zásobníku
    int last;    //Spodek zásobníku
    tokenType *array;   //Pole pro zásobník
}*pStack;

/**
 * stack constructor
 * @param *S- stack to init
 */
void stackInit(pStack *S);
/**
 * string destructor
 * @param *S- stack to init
 */
void stackDestruct(pStack* S);
/**
 * stack push operation
 * @param *S- stack to pushm type-token to push
 */
void stackPush(pStack S, tokenType type);
/**
 * stack pop operation
 * @param *S- stack to pop
 * @return poped token
 */
tokenType stackPop(pStack S);
/**
 * return head of stack
 * @param *S- stack to operate whith
 * @return head of stack
 */
tokenType stackHead(pStack S);
/**
 * is stack empty function
 * @param *S- stack to check
 * @return TRUE-stack is empty, FALSE-stack is not empty
 */
bool stackEmpty(pStack s);
/**
 * printing stack for debug
 * @param *S- stack to print
 */
void stackPrint(pStack s);