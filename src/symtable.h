/** @file symtable.h
 * 
 * IFJ21 compiler
 * 
 * @brief Symbol table enums and structures definition, and function declaration for binary tree.
 *
 * @authors
 */
#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include "tokens.h"
#include "baseDeclarations.h"


typedef enum {
    ST_VAR,
    ST_FUNC,
} STType;

typedef struct {
    tokenType type;
} STVarData;

typedef struct {
    tokenType *paramTypes; //array of parameter types
    unsigned short paramNum; //number of parameters
    tokenType *retTypes; //array of returning types
    unsigned short retNum; //number of returning types
    bool declared;
    bool defined;
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

/** @brief Symbol tree initialization. Allocates an instance.
 *
 * @param RootPtr Root of tree.
 */
void symtable_init (STSymbolPtr* RootPtr);

/** @brief Searching data of specific symbol.
 *
 * @param RootPtr Root of tree.
 * @param id Id to search.
 * @return Pointer to data struct of symbol. NULL if not found.
 */
STData* symtable_search (STSymbolPtr* RootPtr, char *id);

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

/** @brief destructer to data in b tree
 *
 *  @param *RootPtr pointer to root item
 */
void symtable_data_disporese (STSymbolPtr* RootPtr);

/** @brief destructer to data of function in b tree
 *
 *  @param *data pointer to data
 */
void symtable_data_disporese_func(STFuncData *data);

/** @brief Debug function print all tree
 *
 * @param RootPtr Root of tree.
 */
void symtable_print (STSymbolPtr* RootPtr);


/******************************  memory model*********************************/

#define S_TABLE_FRAME_BASE 100  //počateční velkost zásobníku

typedef struct{
    bool wedge;
    STSymbol * bTree;
}frame;

typedef struct {
    int capacity;   //Velikost zásobníku
    int last;    //Spodek zásobníku
    frame globalF;
    frame *localF;   //Pole pro zásobník
}frameStack;

/** @brief Inicialization of memory model
 *
 *  @param *s pointer to memory model
 */
void frameStack_init(frameStack * s);

/** @brief realocation of frame memory model
 *
 *  @param *s pointer to memory model
 */
void frameStack_realoc(frameStack * s);

/** @brief destruction of frame memory model
 *
 *  @param *s pointer to memory model
 */
void frameStack_disporse(frameStack * s);

/** @brief push frame to memory model
 *
 *  @param *s pointer to memory model
 *  @param isFunc if pushing is called from function definition 
 */
void frameStack_pushFrame(frameStack * s,bool isFunc);

/** @brief pop frame from memory model
 *
 *  @param *s pointer to memory model
 */
void frameStack_popFrame(frameStack * s);

/** @brief push frame to memory model
 *
 *  @param *s pointer to memory model
 *  @param isFunc if pushing is called from function definition 
 */
void frameInit(frame *f,bool wedge);

/** @brief frame inicialization
 *
 *  @param *f pointer to frame
 *  @param wedge if true search will end on this frame-for function definition 
 */
void frameDisporse(frame *f);

/** @brief searching in memory model
 *
 *  @param *f pointer to memory model
 *  @param *key key which is searched
 */
STData * frameStackSearchVar(frameStack *f,char * key);

STData * frameStackSearchFunc(frameStack *f,char * key);

/** @brief inserting new item in memory model
 *
 *  @param *f pointer to memory model
 *  @param *key key which is searched
 *  @param *isGlobal is item in global frame
 */
STData * frameStackInsert(frameStack *f,char *key,bool isGlobal);

/** @brief printing whole memory model
 *
 *  @param *f pointer to memory model
 */
void frameStackPrint(frameStack *f);

/** @brief searching in memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of searching the record
 *  @param isGlobal where to search- true:global frame, false:local frame on the top of stack
 *  @return pointer to finded data, if not finded null
 */
STData * frameStackSearchActual(frameStack *f,char * key,bool isGlobal);

/** @brief inserting function definition to memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of inserting the record
 *  @param isGlobal where to inset- true:global frame, false:local frame on the top of stack
 *  @return pointer to inserted data
 */
STData * frameStackInsertFunctionDefinition(frameStack *f,char *key,bool *checkOnly);

/** @brief inserting function declaration to memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of inserting the record
 *  @param *checkOnly if there is a declaration record, param will be set on true, else false
 *  @return pointer to inserted data
 */
STData * frameStackInsertFunctionDeclaration(frameStack *f,char *key,bool isGlobal,bool *checkOnly);

/** @brief inserting var declaration to memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of inserting the record
 *  @param isGlobal where to inset- true:global frame, false:local frame on the top of stack
 *  @param *checkOnly if there is a definition record, param will be set on true, else false
 *  @return pointer to inserted data
 */
STData * frameStackInsertVar(frameStack *f,char *key,bool isGlobal,tokenType Ttype);

void frameStack_initPreFunctions(frameStack * f);
void frameStack_initPreFunction(frameStack * f,char *key,tokenType *params,int parN,tokenType *retTypes,int retN);



#endif 