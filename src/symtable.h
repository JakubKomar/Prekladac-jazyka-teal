/** @file symtable.h
 * 
 * IFJ21 compiler
 * 
 * @brief Symbol table enums and structures definition, and function declaration for binary tree.
 *
 * @authors
 */

#pragma once
#include "tokens.h"
#include "dstring.h"
#include "baseDeclarations.h"

typedef enum {
    ST_VAR,
    ST_FUNC,
} STType;

typedef enum {
    UNDEF,
    NIL,
    INT,
    NUMBER,
    STRING,
    BOOL
} STDataType;

typedef struct {
    STDataType type;
    bool declared;
} STVarData;

typedef struct {
    STDataType *paramTypes; //array of parameter types
    unsigned short paramNum; //number of parameters
    STDataType *retTypes; //array of returning types
    unsigned short retNum; //number of returning types
    bool declared;
} STFuncData;

typedef struct {
    STType type;
    STVarData *varData;
    STFuncData *funcData;
} STData;

typedef struct BTNode {
    char *id; //= key in BT
    struct BTNode *lPtr;
    struct BTNode *rPtr;
    STData data;
} STSymbol, *STSymbolPtr;

/** @brief Symbol tree initialization.
 *
 * @param RootPtr Root of tree.
 * @return 
 */
void symtable_init (STSymbolPtr* RootPtr);

/** @brief Searching data of specific symbol.
 *
 * @param RootPtr Root of tree.
 * @param id Id to search.
 * @return Pointer to data struct of symbol. NULL if not found.
 */
STData* symtable_search (STSymbolPtr RootPtr, char *id);

/** @brief Inserts symbol and returns its data to fill.
 *
 * @param RootPtr Root of tree.
 * @param id Id to insert.
 * @return Pointer to data struct of symbol. NULL if unsuccessful malloc or symbol already exists.
 */
STData* symtable_insert_woData (STSymbolPtr* RootPtr, char *id);

/** @brief Auxiliary function for copying and deallocation the rightmost node in a subtree.
 *
 * @param PtrReplaced Node where to copy data.
 * @param RootPtr Root of a subtree.
 */
void ReplaceByRightmost (STSymbolPtr PtrReplaced, STSymbolPtr* RootPtr);

/** @brief Deletes symbol with the given id.
 *
 * @param RootPtr Root of tree.
 * @param id Id to delete.
 */
void symtable_delete (STSymbolPtr* RootPtr, char *id);

/** @brief Disposes of entire symbol tree and deallocates memory.
 *
 * @param RootPtr Root of tree.
 */
void symtable_dispose (STSymbolPtr* RootPtr);

void symtable_print (STSymbolPtr* RootPtr);

#define S_TABLE_FRAME_BASE 100  //počateční velkost zásobníku

typedef struct{
    bool wedge;
    STSymbolPtr bTree;
}frame;


typedef struct {
    int capacity;   //Velikost zásobníku
    int last;    //Spodek zásobníku
    frame globalF;
    frame *localF;   //Pole pro zásobník
}frameStack;

void frameStack_init(frameStack * s);
void frameStack_realoc(frameStack * s);
void frameStack_disporse(frameStack * s);

void frameStack_pushFrame(frameStack * s,bool isFunc);
void frameStack_popFrame(frameStack * s);


void frameInit(frame *f,bool wedge);
void frameDisporse(frame *f);

STData * frameStackSearch(frameStack *f,char * key);
void frameStackInsert(frameStack *f,char *key,bool isGlobal);
void frameStackPrint(frameStack *f);
void symtable_print (STSymbolPtr* RootPtr);

void symtable_data_disporese (STSymbolPtr* RootPtr);
void symtable_data_disporese_func(STFuncData *data);