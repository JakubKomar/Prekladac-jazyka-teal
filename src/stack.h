/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "baseDeclarations.h"
#include "tokens.h"
#define STACK_BASE_SIZE 100  //počateční velkost zásobníku

typedef struct {
    unsigned int capacity;   //Velikost zásobníku
    unsigned int last;    //Spodek zásobníku
    token *array;   //Pole pro zásobník
}stack;

/**
 * stack constructor
 * @param *s stack to init
 */
void stackInit(stack *s);
/**
 * string destructor
 * @param *s stack to init
 */
void stackDestruct(stack *s);
/**
 * stack push operation
 * @param *s stack to push
 * @param type token to push
 */
void stackPush(stack *s, token type);
/**
 * stack pop operation
 * @param *s stack to pop
 * @return poped token
 */
token stackPop(stack *s);
/**
 * return head of stack
 * @param *s stack to operate whith
 * @return head of stack
 */
token stackHead(stack *s);
/**
 * return first terminal on stack
 * @param *s stack to operate whith
 * @return  first terminal on stack
 */
token stackTop(stack *s);
void stackInsertHanle(stack *s);
void stackRemoveHande(stack *s);
void stackShiftRight(stack *s,int wege);
/**
 * checking if stack is empty
 * @param *s stack to check
 * @return TRUE-stack is empty, FALSE-stack is not empty
 */
bool stackEmpty(stack *s);
/**
 * checking if stack is full
 * @param *s stack to check
 * @return TRUE-stack is FULL, FALSE-stack is not full
 */
bool stackFull(stack *s);
/**
 * printing stack for debug
 * @param *s stack to print
 */
void stackPrint(stack *s);