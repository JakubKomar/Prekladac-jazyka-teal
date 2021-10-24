/**
 * @brief   Structure stack
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "baseDeclarations.h"
#include "tokens.h"
#define STACK_BASE_SIZE 64  //base size of stack

typedef struct {
    int capacity;   //Capacity of stack-can chenge dynamicly
    int last;    //Last item in stack
    token *array;   //array for stack
}stack;


/**
 * @brief stack constructor
 * @param *s stack to init
 */
void stackInit(stack *s);

/**
 * @brief @briefstring destructor
 * @param *s stack to init
 */
void stackDestruct(stack *s);

/**
 * @brief stack push operation
 * @param *s stack to push
 * @param type token to push
 */
void stackPush(stack *s, token type);

/**
 * @brief stack pop operation
 * @param *s stack to pop
 * @return poped token
 */
token stackPop(stack *s);

/**
 * @brief return head of stack
 * @param *s stack to operate whith
 * @return head of stack
 */
token stackHead(stack *s);

/**
 * @brief return first terminal on stack
 * @param *s stack to operate whith
 * @return  first terminal on stack
 */
token stackTop(stack *s);

/**
 * @brief checking if stack is empty
 * @param *s stack to check
 * @return TRUE-stack is empty, FALSE-stack is not empty
 */
bool stackEmpty(stack *s);

/**
 * @brief checking if stack is full
 * @param *s stack to check
 * @return TRUE-stack is FULL, FALSE-stack is not full
 */
bool stackFull(stack *s);

/**
 * @brief printing stack for debug
 * @param *s stack to print
 */
void stackPrint(stack *s);

/**
 * @brief clear all items from stack
 * @param *s stack to operate whith
*/
void stackClear(stack *s);

/**
 * @brief inserting hadle before terminal
 * @param *s stack to operate whith
 */
void stackInsertHanle(stack *s);

/**
 * @brief removing handle from stack- if there is no handle->error
 * @param *s stack to operate whith
 */
void stackRemoveHande(stack *s);

/**
 * @brief shift all item from wage in stack to right 
 * @param *s stack to operate whith
 * @param wage index in stack 
 */
void stackShiftRight(stack *s,int wege);
