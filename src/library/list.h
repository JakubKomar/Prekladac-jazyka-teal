/**
 * @brief   Structure 2 line list
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include <malloc.h>
#include "./../baseDeclarations.h"

typedef struct item{                    /* prvek dvousměrně vázaného seznamu */                                  
    struct item *lptr;             /* ukazatel na předchozí prvek seznamu */
    struct item *rptr;             /* ukazatel na následující prvek seznamu */
    int data; //to do
}*listItem;

typedef struct {                      /* dvousměrně vázaný seznam */
    listItem first;                   /* ukazatel na první prvek seznamu */
    listItem act;                     /* ukazatel na aktuální prvek seznamu */
    listItem last;                    /* ukazatel na posledni prvek seznamu */
}list;
/**
 * list constructor
 * @param *l - list to construct
 */
void initList (list *l);
/**
 * list destructor
 * @param *l - list to destruct
 */
void disposeList (list *l);
/**
 * insert to end of list
 * @param *l - list to construct, token- token to insert
 */
void insertLast(list *l, listItem token) ;
/**
 * insert to start of list
 * @param *l - list to construct, token- token to insert
 */
void insertFirst(list *l, listItem new);
/**
 * debug function-print the list
 * @param *l - list to print
 */
void printList(list *l);