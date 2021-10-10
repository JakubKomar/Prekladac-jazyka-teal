/** @file symtable.c
 * 
 * IFJ21 compiler
 * 
 * @brief Symbol table implementation as binary tree.
 *
 * @authors
 */

#include "symtable.h"

void symtable_init (STSymbolPtr* RootPtr) {
	*RootPtr = NULL;
}

STData* symtable_search (STSymbolPtr RootPtr, char *id) {
	if(RootPtr == NULL)
		return NULL;

	if(strcmp(RootPtr->id, id) == 0){
		return &RootPtr->data;
	}

	if(strcmp(RootPtr->id, id) > 0)
		return symtable_search(RootPtr->lPtr, id);

	return symtable_search(RootPtr->rPtr, id);
}

STData* symtable_insert_woData (STSymbolPtr* RootPtr, char *id) {
	if((*RootPtr) == NULL){
		if(!((*RootPtr) = malloc(sizeof(STSymbol))))
			return NULL; //unsuccessful

		(*RootPtr)->id = id;
		(*RootPtr)->lPtr = NULL;
		(*RootPtr)->rPtr = NULL;
		return &(*RootPtr)->data; //data to fill
	}

	if(strcmp((*RootPtr)->id, id) == 0){
		errorD(3,"The symbol already exists in the symbol table.");
		return NULL;
	}

	if(strcmp((*RootPtr)->id, id) > 0){ 
		return symtable_insert_woData(&(*RootPtr)->lPtr, id);
	}

	return symtable_insert_woData(&(*RootPtr)->rPtr, id);
}

void ReplaceByRightmost (STSymbolPtr PtrReplaced, STSymbolPtr* RootPtr) {
	if((*RootPtr)->rPtr == NULL){
		PtrReplaced->id = (*RootPtr)->id;
		PtrReplaced->data = (*RootPtr)->data;
		STSymbol *tmp = (*RootPtr);
		(*RootPtr) = (*RootPtr)->lPtr;
		free (tmp->data.funcData.paramTypes);
		free (tmp->data.funcData.retTypes);
		free (tmp->id);
		free (tmp);
		return;
	}

	ReplaceByRightmost(PtrReplaced, &(*RootPtr)->rPtr);
}

void symtable_delete (STSymbolPtr* RootPtr, char *id) {
	if((*RootPtr) == NULL)
		return;

	if(strcmp((*RootPtr)->id, id) > 0){
		symtable_delete(&(*RootPtr)->lPtr, id);
		return;
	}

	if(strcmp((*RootPtr)->id, id) < 0){
		symtable_delete(&(*RootPtr)->rPtr, id);
		return;
	}


	if(((*RootPtr)->lPtr == NULL) && ((*RootPtr)->rPtr == NULL)){
		free ((*RootPtr)->data.funcData.paramTypes);
		free ((*RootPtr)->data.funcData.retTypes);
		free ((*RootPtr)->id);
		free ((*RootPtr));
		(*RootPtr) = NULL;
		return;
	}

	STSymbol *tmp = (*RootPtr);

	if((*RootPtr)->lPtr == NULL){
		(*RootPtr) = (*RootPtr)->rPtr;
		free (tmp->data.funcData.paramTypes);
		free (tmp->data.funcData.retTypes);
		free (tmp->id);
		free (tmp);
		return;
	}

	if((*RootPtr)->rPtr == NULL){
		(*RootPtr) = (*RootPtr)->lPtr;
		free (tmp->data.funcData.paramTypes);
		free (tmp->data.funcData.retTypes);
		free (tmp->id);
		free (tmp);
		return;
	}

	ReplaceByRightmost((*RootPtr), &(*RootPtr)->lPtr);
	return;
}

void symtable_dispose (STSymbolPtr* RootPtr) {
	if((*RootPtr) != NULL)
		{
			symtable_dispose(&(*RootPtr)->rPtr);
			symtable_dispose(&(*RootPtr)->lPtr);
			free ((*RootPtr)->data.funcData.paramTypes);
			free ((*RootPtr)->data.funcData.retTypes);
			free ((*RootPtr)->id);
			free ((*RootPtr));
			(*RootPtr) = NULL;
		}
}