/** @file symtable.c
 * 
 * IFJ21 compiler
 * 
 * @brief Symbol table implementation as binary tree.
 *
 * @authors
 */

#include "symtable.h"

void symtable_init (STSymbolPtr* RootPtr) 
{
	*RootPtr = NULL;
}

STData* symtable_search (STSymbolPtr RootPtr, char *id) 
{
	if(RootPtr == NULL)
		return NULL;

	if(strcmp(RootPtr->id, id) == 0)
		return &RootPtr->data;

	if(strcmp(RootPtr->id, id) > 0)
		return symtable_search(RootPtr->lPtr, id);
	else
		return symtable_search(RootPtr->rPtr, id);
}

STData* symtable_insert_woData (STSymbolPtr* RootPtr, char *id) 
{
	if((*RootPtr) == NULL)
	{
		if(!((*RootPtr) = malloc(sizeof(STSymbol))))
			errorD(100,"btree maloc error\n");

		(*RootPtr)->id = id;
		(*RootPtr)->lPtr = NULL;
		(*RootPtr)->rPtr = NULL;
		return &(*RootPtr)->data; //data to fill
	}

	if(strcmp((*RootPtr)->id, id) == 0)
	{
		errorD(3,"The symbol already exists in the symbol table.");
		return NULL;
	}

	if(strcmp((*RootPtr)->id, id) > 0)
		return symtable_insert_woData(&(*RootPtr)->lPtr, id);
	else
		return symtable_insert_woData(&(*RootPtr)->rPtr, id);
}
/*
void ReplaceByRightmost (STSymbolPtr PtrReplaced, STSymbolPtr* RootPtr) 
{
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

void symtable_delete (STSymbolPtr* RootPtr, char *id) 
{
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
*/
void symtable_dispose (STSymbolPtr* RootPtr) 
{
	if((*RootPtr) != NULL)
	{
		symtable_dispose(&(*RootPtr)->rPtr);
		symtable_dispose(&(*RootPtr)->lPtr);
		//symtable_data_disporese(RootPtr);
		free ((*RootPtr));
		(*RootPtr) = NULL;
	}
}

void symtable_data_disporese (STSymbolPtr* RootPtr) 
{
	if((*RootPtr)->data.type==ST_VAR)
		free ((*RootPtr)->data.varData);
	else if((*RootPtr)->data.type==ST_FUNC)
	{
		symtable_data_disporese_func((*RootPtr)->data.funcData);
		free ((*RootPtr)->data.funcData);
	}
	free ((*RootPtr)->id);
}

void symtable_data_disporese_func(STFuncData *data)
{
	free(data->paramTypes);
	free(data->retTypes);
}

void symtable_print (STSymbolPtr* RootPtr)
{
	if((*RootPtr)==NULL)
		return;
	if((*RootPtr)->lPtr!=NULL)
		symtable_print(&(*RootPtr)->lPtr);
	
	debug("\t%s\n",(*RootPtr)->id);

	if((*RootPtr)->rPtr!=NULL)
		symtable_print(&(*RootPtr)->rPtr);
}


/*frame model fuctions*/

void frameStack_init(frameStack * s)
{
	s->capacity=S_TABLE_FRAME_BASE;
	s->last=-1;

	s->localF=malloc(sizeof(frame)*s->capacity);
	if(s->localF==NULL)
		errorD(100,"frameStack malloc error");

	frameInit(&s->globalF,true);
	frameStack_pushFrame(s,true);
}

void frameStack_realoc(frameStack * s)
{
	s->capacity=s->capacity*2;
	s->localF=realloc(s->localF,sizeof(frame)*s->capacity);
	if(s->localF==NULL)
		errorD(100,"frameStack realoc error");
}

void frameStack_disporse(frameStack * s)
{
	symtable_dispose(&s->globalF.bTree);
	for(int i=0;i<=s->last;i++)
	{
		symtable_dispose(&s->localF[i].bTree);
	}
	free(s->localF);
}

void frameStack_pushFrame(frameStack * s,bool isFunc)
{	
	s->last++;
	if(!(s->last<s->capacity))
		frameStack_realoc(s);
	frameInit(&s->localF[s->last],isFunc);
}

void frameStack_popFrame(frameStack * s)
{
	if(s->last<0)
		errorD(99,"podtečení zásobníku rámců");
	symtable_dispose(&s->localF[s->last].bTree);	
	s->last--;
}

void frameInit(frame *f,bool wedge)
{
	f->wedge=wedge;
	symtable_init(&f->bTree);
}

STData * frameStackSearch(frameStack *f,char * key)
{
	STData *data=NULL;
	for(int i=f->last;i>=0;--i)
	{
		data=symtable_search(f->localF[i].bTree,key);

		if(data!=NULL)
			return data;
		else if(f->localF[i].wedge)
			break;
	}
	data=symtable_search(f->globalF.bTree,key);
	return data;
}

void frameStackInsert(frameStack *f,char *key,bool isGlobal)
{
	if(isGlobal)
		symtable_insert_woData(&f->globalF.bTree,key);
	else if(f->last>=0)
		symtable_insert_woData(&f->localF[f->last].bTree,key);
	else
		errorD(99,"cant insert into noexisting frame\n");
}

void frameStackPrint(frameStack *f)
{
	debugS("------------------Symtable print------------------\nGlobal:\n");
	symtable_print(&f->globalF.bTree);
	debugS("Local Frames:\n");
	for(int i=0;i<=f->last;i++)
	{
		symtable_print(&f->localF[i].bTree);
		debugS("*****************\n");
	}
	debugS("------------------end of Symtable print------------------\n");
}