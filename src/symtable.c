/** @file symtable.c
 * 
 * IFJ21 compiler
 * 
 * @brief Symbol table implementation as binary tree.
 *
 * @authors xtverd01, xkomar33
 */

#include "symtable.h"

void symtable_init (STSymbolPtr* RootPtr) 
{
	*RootPtr= NULL;
}

STData* symtable_search (STSymbolPtr* RootPtr, char *id) 
{
	if(*RootPtr == NULL)
		return NULL;

	if(strcmp((*RootPtr)->id, id) == 0)
		return &(*RootPtr)->data;

	if(strcmp((*RootPtr)->id, id) > 0)
		return symtable_search(&(*RootPtr)->lPtr, id);
	else
		return symtable_search(&(*RootPtr)->rPtr, id);
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

	if((*RootPtr)->id == NULL){ //first insert case
		(*RootPtr)->id = id;
		return &(*RootPtr)->data;
	}

	if(strcmp((*RootPtr)->id, id) == 0)
	{
		free(id);
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
		symtable_data_disporese(&(*RootPtr));
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
	
	debug("\t%10s %10s:",(*RootPtr)->id,(*RootPtr)->data.type==ST_FUNC?"Function":"Variable");
	if((*RootPtr)->data.type==ST_FUNC)
	{
		debugS("[");
		for (int i = 0; i < (*RootPtr)->data.funcData->paramNum; i++)
			debug("%s,",tokenStr((token){(*RootPtr)->data.funcData->paramTypes[i]}));
		debugS("],[");
		for (int i = 0; i < (*RootPtr)->data.funcData->retNum; i++)
			debug("%s,",tokenStr((token){(*RootPtr)->data.funcData->retTypes[i]}));
		debugS("]");
	}
	else
		debug("%s",tokenStr((token){(*RootPtr)->data.varData->type}));
	debugS("\n");
	if((*RootPtr)->rPtr!=NULL)
		symtable_print(&(*RootPtr)->rPtr);
}


/******************frame model fuctions*********************/

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

void frameStack_initPreFunctions(frameStack * f)
{
	frameStack_initPreFunction(f,"reads",NULL,0,(tokenType []){K_STRING},1);
	frameStack_initPreFunction(f,"readi",NULL,0,(tokenType []){K_INTEGER},1);
	frameStack_initPreFunction(f,"readn",NULL,0,(tokenType []){K_NUMBER},1);
	frameStack_initPreFunction(f,"tointeger",(tokenType []){K_NUMBER},1,(tokenType []){K_INTEGER},1);
	frameStack_initPreFunction(f,"substr",(tokenType []){K_STRING,K_NUMBER,K_NUMBER},3,(tokenType []){K_STRING},1);
	frameStack_initPreFunction(f,"ord",(tokenType []){K_STRING,K_STRING},2,(tokenType []){K_INTEGER},1);
	frameStack_initPreFunction(f,"chr",(tokenType []){K_INTEGER},1,(tokenType []){K_STRING},1);
	frameStack_initPreFunction(f,"write",NULL,0,NULL,0);
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

bool searchForNonDefinedFunction(STSymbolPtr* RootPtr)
{
	if((*RootPtr))
	{
		if(((*RootPtr)->data.type==ST_FUNC&&(!((*RootPtr)->data.funcData->defined)))||(searchForNonDefinedFunction(&(*RootPtr)->lPtr))||(searchForNonDefinedFunction(&(*RootPtr)->rPtr)))
			return true;
	}
		return false;
}

void frameStack_popFrame(frameStack * s)
{
	if(s->last<0)
		errorD(99,"podtečení zásobníku rámců");
	if(searchForNonDefinedFunction(&s->localF[s->last].bTree))
		errorD(3,"Byla nalezena deklarovaná funkce bez definice");
	symtable_dispose(&s->localF[s->last].bTree);	
	s->last--;
}

void frameInit(frame *f,bool wedge)
{
	f->wedge=wedge;
	symtable_init(&f->bTree);
}

STData * frameStackSearchVar(frameStack *f,char * key)
{
	STData *data=NULL;
	for(int i=f->last;i>=0;--i)
	{
		data=symtable_search(&f->localF[i].bTree,key);

		if(data!=NULL)
			return data;
		else if(f->localF[i].wedge)
			break;
	}
	data=symtable_search(&f->globalF.bTree,key);
	return data;
}

STData * frameStackSearchFunc(frameStack *f,char * key)
{
	STData *data=NULL;
	for(int i=f->last;i>=0;--i)
	{
		data=symtable_search(&f->localF[i].bTree,key);
		if(data!=NULL)
			return data;
	}
	data=symtable_search(&f->globalF.bTree,key);
	return data;
}

STData * frameStackSearchActual(frameStack *f,char * key,bool isGolobal)
{
	return symtable_search(isGolobal?&f->globalF.bTree:&f->localF[f->last].bTree,key);
}


STData * frameStackInsert(frameStack *f,char *key,bool isGlobal)
{
	if(isGlobal)
		return symtable_insert_woData(&f->globalF.bTree,key);
	else if(f->last>=0)
		return symtable_insert_woData(&f->localF[f->last].bTree,key);
	else
		errorD(99,"cant insert into noexisting frame\n");
	return NULL;
}

STData * frameStackInsertFunctionDeclaration(frameStack *f,char *key,bool isGlobal,bool *checkOnly)
{
	STData *ptr= frameStackSearchActual(f,key,isGlobal);
	if(ptr)
	{
		free(key);
		if(ptr->type!=ST_FUNC)
			errorD(3,"k id funcke již byla přiřazena proměnná");
		if(ptr->funcData->declared)
			errorD(3,"redeklarace/redefinice funkce");
		ptr->funcData->declared=true;
		*checkOnly=true;
	}
	else
	{
		ptr=frameStackInsert(f, key,isGlobal);
		ptr->type=ST_FUNC;
		ptr->varData=NULL;

		ptr->funcData=malloc(sizeof(STFuncData));
		if(!ptr->funcData)
			errorD(100,"function sym table insert malloc error");

		ptr->funcData->paramNum=0;
		ptr->funcData->retNum=0;
		ptr->funcData->paramTypes=NULL;
		ptr->funcData->retTypes=NULL;

		ptr->funcData->declared=true;
		ptr->funcData->defined=false;
		*checkOnly=false;
	}
	return ptr;
}

void frameStack_initPreFunction(frameStack * f,char *key,tokenType *params,int parN,tokenType *retTypes,int retN)
{
	int len=0;
	while (true)
	{
		if(key[len]=='\0')
			break;
		len++;
	}
	char * copy;
	if(!(copy=malloc(sizeof(char)*(len+2))))
		error(100);
	strcpy(copy,key);

	STData *ptr;
	ptr =frameStackInsert(f,copy,true);
	ptr->type=ST_FUNC;
	ptr->varData=NULL;

	ptr->funcData=malloc(sizeof(STFuncData));
	if(!ptr->funcData)
		errorD(100,"function sym table insert malloc error");

	ptr->funcData->paramNum=parN;
	ptr->funcData->retNum=retN;
	ptr->funcData->declared=true;
	ptr->funcData->defined=true;
	

	if(parN>0)
	{
		if(!(ptr->funcData->paramTypes=malloc(sizeof(tokenType)*parN)))
			error(100);
		for(int i=0;i<parN;i++)
		{
			ptr->funcData->paramTypes[i]=params[i];
		}
	}
	else
		ptr->funcData->paramTypes=NULL;

	if(retN>0)
	{
		if(!(ptr->funcData->retTypes=malloc(sizeof(tokenType)*retN)))
			error(100);
		for(int i=0;i<retN;i++)
		{
			ptr->funcData->retTypes[i]=retTypes[i];
		}
	}
	else
		ptr->funcData->retTypes=NULL;
}

STData * frameStackInsertFunctionDefinition(frameStack *f,char *key,bool *checkOnly)
{
	STData *ptr;
	if((ptr=frameStackSearchActual(f,key,false)))
	{}
	else if((ptr=frameStackSearchActual(f,key,true)))
	{}
	else
	{
		ptr =frameStackInsert(f,key,false);
		ptr->type=ST_FUNC;
		ptr->varData=NULL;

		ptr->funcData=malloc(sizeof(STFuncData));
		if(!ptr->funcData)
			errorD(100,"function sym table insert malloc error");

		ptr->funcData->paramNum=0;
		ptr->funcData->retNum=0;
		ptr->funcData->paramTypes=NULL;
		ptr->funcData->retTypes=NULL;

		ptr->funcData->declared=false;
		ptr->funcData->defined=true;
		*checkOnly=false;
		return ptr;
	}
	free(key);
	*checkOnly=true;
	if(ptr->type!=ST_FUNC)
		errorD(3,"k id funcke již byla přiřazena proměnná");
	else if(ptr->funcData->defined)
		errorD(3,"tato funkce již byla definována");
	ptr->funcData->defined=true;	
	return ptr;
}


STData * frameStackInsertVar(frameStack *f,char *key,bool isGlobal,tokenType Ttype)
{
	STData *ptr=frameStackInsert(f, key,isGlobal);
	ptr->type=ST_VAR;
	ptr->funcData=NULL;
	ptr->varData=malloc(sizeof(STVarData));	
	if(!ptr->varData)
		errorD(100,"var sym table insert malloc error");
	ptr->varData->type=Ttype;
	return ptr;
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