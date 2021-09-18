/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "./../baseDeclarations.h"

#define STACK_BASE_SIZE 100  //počateční velkost zásobníku

typedef struct {
    unsigned int capacity;   //Velikost zásobníku
    unsigned int last;    //Spodek zásobníku
    tokenType *array;   //Pole pro zásobník
}stack;

/**
 * stack constructor
 * @param *s- stack to init
 */
void stackInit(stack *s);
/**
 * string destructor
 * @param *s- stack to init
 */
void stackDestruct(stack *s);
/**
 * stack push operation
 * @param *s- stack to pushm type-token to push
 */
void stackPush(stack *s, tokenType type);
/**
 * stack pop operation
 * @param *s- stack to pop
 * @return poped token
 */
tokenType stackPop(stack *s);
/**
 * return head of stack
 * @param *s- stack to operate whith
 * @return head of stack
 */
tokenType stackHead(stack *s);
/**
 * checking if stack is empty
 * @param *s- stack to check
 * @return TRUE-stack is empty, FALSE-stack is not empty
 */
bool stackEmpty(stack *s);
/**
 * checking if stack is full
 * @param *s- stack to check
 * @return TRUE-stack is FULL, FALSE-stack is not full
 */
bool stackFull(stack *s);
/**
 * printing stack for debug
 * @param *s- stack to print
 */
void stackPrint(stack *s);