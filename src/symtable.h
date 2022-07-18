/**
 * Implementace překladače imperativního jazyka IFJ21
 *  
 * @file symtable.h
 * 
 * @brief Symbol table enums and structures definition, and function declaration for binary tree.
 *
 * @authors
 */
#pragma once

#include "tokens.h"
#include "baseDeclarations.h"


typedef enum {
    ST_VAR,
    ST_FUNC,
} STType;   //type of record

typedef struct {
    tokenType type;
    bool defined;
} STVarData;

typedef struct {
    tokenType *paramTypes;   //array of parameter types
    int paramNum;           //number of parameters
    tokenType *retTypes;    //array of returning types
    int retNum;             //number of returning types
    bool declared;          //is recorde declared
    bool defined;           //is recorde defined
} STFuncData;

typedef struct {
    STType type;            
    STVarData *varData;      
    STFuncData *funcData;
    unsigned long int dekorator;    
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
void symtableInit (STSymbolPtr* RootPtr);

/** @brief Searching data of specific symbol.
 *
 * @param RootPtr Root of tree.
 * @param id Id to search.
 * @return Pointer to data struct of symbol. NULL if not found.
 */
STSymbolPtr* symtableSearch (STSymbolPtr* RootPtr, char *id);

/** @brief Inserts symbol and returns its data to fill.
 *
 * @param RootPtr Root of tree.
 * @param id Id to insert.
 * @return Pointer to data struct of symbol. NULL if unsuccessful malloc or symbol already exists.
 */
STSymbolPtr* symtableInsertData (STSymbolPtr* RootPtr, char *id);

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
void symtableDelete (STSymbolPtr* RootPtr, char *id);

/** @brief Disposes of entire symbol tree and deallocates memory.
 *
 * @param RootPtr Root of tree.
 */
void symtableDispose (STSymbolPtr* RootPtr);

/** @brief destructer to data in b tree
 *
 *  @param *RootPtr pointer to root item
 */
void symtableDataDisporese (STSymbolPtr* RootPtr);

/** @brief destructer to data of function in b tree
 *
 *  @param *data pointer to data
 */
void symtableDataDisporeseFunc(STFuncData *data);

/** @brief Debug function print all tree
 *
 * @param RootPtr Root of tree.
 */
void symtablePrint (STSymbolPtr* RootPtr);


/******************************  memory model*********************************/

#define S_TABLE_FRAME_BASE 32  //base size of stack

typedef struct{
    bool wedge;         
    STSymbol * bTree;   
}frame;

typedef struct {
    int capacity;   //Capacity of stack
    int last;       //Last item of stack
    frame globalF;  //global frame
    frame *localF;  //locals frames
}frameStack;

/** @brief Inicialization of memory model
 *
 *  @param *s pointer to memory model
 */
void frameStackInit(frameStack * s);

/** @brief realocation of frame memory model
 *
 *  @param *s pointer to memory model
 */
void frameStackRealoc(frameStack * s);

/** @brief destruction of frame memory model
 *
 *  @param *s pointer to memory model
 */
void frameStackDisporse(frameStack * s);

/** @brief push frame to memory model
 *
 *  @param *s pointer to memory model
 *  @param isFunc if pushing is called from function definition 
 */
void frameStackPushFrame(frameStack * s,bool isFunc);

/** @brief pop frame from memory model
 *
 *  @param *s pointer to memory model
 */
void frameStackPopFrame(frameStack * s);

/** @brief frame inicialization
 *
 *  @param *f pointer to frame
 *  @param wedge if true search will end on this frame-for function definition 
 */
void frameInit(frame *f,bool wedge);

/** @brief frame disporse
 *
 *  @param *f pointer to frame
 */
void frameDisporse(frame *f);

/** @brief searching var in memory model
 *
 *  @param *f pointer to memory model
 *  @param *key key which is searched
 *  @return pointer to finded node or NULL
 */
STSymbolPtr * frameStackSearchVar(frameStack *f,char * key);

/** @brief searching fuction in memory model
 *
 *  @param *f pointer to memory model
 *  @param *key key which is searched
 *  @return pointer to finded node or NULL
 */
STSymbolPtr * frameStackSearchFunc(frameStack *f,char * key);

/** @brief inserting new item in memory model
 *
 *  @param *f pointer to memory model
 *  @param *key key which is searched
 *  @param *isGlobal is item in global frame
 */
STSymbolPtr * frameStackInsert(frameStack *f,char *key,bool isGlobal);

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
STSymbolPtr * frameStackSearchActual(frameStack *f,char * key,bool isGlobal);

/** @brief inserting function definition to memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of inserting the record
 *  @param isGlobal where to inset- true:global frame, false:local frame on the top of stack
 *  @return pointer to inserted data
 */
STSymbolPtr * frameStackInsertFunctionDefinition(frameStack *f,char *key,bool *checkOnly);

/** @brief inserting function declaration to memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of inserting the record
 *  @param *checkOnly if there is a declaration record, param will be set on true, else false
 *  @return pointer to inserted data
 */
STSymbolPtr * frameStackInsertFunctionDeclaration(frameStack *f,char *key,bool isGlobal,bool *checkOnly);

/** @brief inserting var declaration to memory model
 *
 *  @param *f pointer to memory model
 *  @param *key name of inserting the record
 *  @param isGlobal where to inset- true:global frame, false:local frame on the top of stack
 *  @param *checkOnly if there is a definition record, param will be set on true, else false
 *  @return pointer to inserted data
 */
STSymbolPtr * frameStackInsertVar(frameStack *f,char *key,bool isGlobal,tokenType Ttype);

/** @brief inserting predefined functions
 *
 *  @param *f pointer to memory model
 */
void frameStack_initPreFunctions(frameStack * f);

/** @brief inserting predefined function
 *
 *  @param *f pointer to memory model
 *  @param *key name of function
 *  @param *params array of params
 *  @param parN number of params
 *  @param *retTypes array of return params
 *  @param retN number of ret params
 */
void frameStack_initPreFunction(frameStack * f,char *key,tokenType *params,int parN,tokenType *retTypes,int retN);

/** @brief searching for definition of function
 *
 *  @param *RootPtr root node
 *  @return true-finded,false-not finded
 */
bool searchForNonDefinedFunction(STSymbolPtr* RootPtr);
