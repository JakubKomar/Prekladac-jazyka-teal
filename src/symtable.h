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
    bool defined;
} STVarData;

typedef struct {
    STDataType *paramTypes; //array of parameter types
    unsigned short paramNum; //number of parameters
    STDataType *retTypes; //array of returning types
    unsigned short retNum; //number of returning types
    bool defined;
} STFuncData;

typedef struct {
    STType type;
    STVarData varData;
    STFuncData funcData;
} STData;

typedef struct BTNode {
    char *id; //= key in BT
    STData data;
    struct BTNode *lPtr;
    struct BTNode *rPtr;
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