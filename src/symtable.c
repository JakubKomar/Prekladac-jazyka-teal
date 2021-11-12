/** @file symtable.c
 * 
 * IFJ21 compiler
 * 
 * @brief Symbol table implementation as binary tree.
 *
 * @authors xtverd01, xkomar33
 */

#include "symtable.h"

void symtableInit (STSymbolPtr* RootPtr) 
{
	*RootPtr= NULL;
}

STSymbolPtr* symtableSearch (STSymbolPtr* RootPtr, char *id) 
{
	if(*RootPtr == NULL)
		return NULL;

	if(strcmp((*RootPtr)->id, id) == 0)
		return &(*RootPtr);

	if(strcmp((*RootPtr)->id, id) > 0)
		return symtableSearch(&(*RootPtr)->lPtr, id);
	else
		return symtableSearch(&(*RootPtr)->rPtr, id);
}

STSymbolPtr* symtableInsertData (STSymbolPtr* RootPtr, char *id) 
{
	if((*RootPtr) == NULL)
	{
		if(!((*RootPtr) = malloc(sizeof(STSymbol))))
			errorD(100,"chyba binárního stromu - maloc error\n");

		(*RootPtr)->id = id;
		(*RootPtr)->lPtr = NULL;
		(*RootPtr)->rPtr = NULL;
		return &(*RootPtr); //data to fill
	}

	if((*RootPtr)->id == NULL){ //first insert case
		(*RootPtr)->id = id;
		return &(*RootPtr);
	}

	if(strcmp((*RootPtr)->id, id) == 0)
	{
		free(id);
		errorD(3,"Záznam již existuje v paměťovém modelu.");
		return NULL;
	}

	if(strcmp((*RootPtr)->id, id) > 0)
		return symtableInsertData(&(*RootPtr)->lPtr, id);
	else
		return symtableInsertData(&(*RootPtr)->rPtr, id);
}

void symtableDispose (STSymbolPtr* RootPtr) 
{
	if((*RootPtr) != NULL)
	{
		symtableDispose(&(*RootPtr)->rPtr);
		symtableDispose(&(*RootPtr)->lPtr);
		symtableDataDisporese(&(*RootPtr));
		free ((*RootPtr));
		(*RootPtr) = NULL;
	}
}

void symtableDataDisporese (STSymbolPtr* RootPtr) 
{
	if((*RootPtr)->data.type==ST_VAR)
		free ((*RootPtr)->data.varData);
	else if((*RootPtr)->data.type==ST_FUNC)
	{
		symtableDataDisporeseFunc((*RootPtr)->data.funcData);
		free ((*RootPtr)->data.funcData);
	}
	free ((*RootPtr)->id);
}

void symtableDataDisporeseFunc(STFuncData *data)
{
	free(data->paramTypes);
	free(data->retTypes);
}

void symtablePrint (STSymbolPtr* RootPtr)
{
	if((*RootPtr)==NULL)
		return;
	if((*RootPtr)->lPtr!=NULL)
		symtablePrint(&(*RootPtr)->lPtr);
	
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
		symtablePrint(&(*RootPtr)->rPtr);
}


/******************frame model fuctions*********************/

void frameStackInit(frameStack * s)
{
	s->capacity=S_TABLE_FRAME_BASE;
	s->last=-1;

	s->localF=malloc(sizeof(frame)*s->capacity);
	if(s->localF==NULL)
		errorD(100,"chyba zásobníku - malloc error");

	frameInit(&s->globalF,true);
	frameStackPushFrame(s,true);

}

void frameStack_initPreFunctions(frameStack * f)
{
	frameStack_initPreFunction(f,"reads",NULL,0,(tokenType []){K_STRING},1);
	frameStack_initPreFunction(f,"readi",NULL,0,(tokenType []){K_INTEGER},1);
	frameStack_initPreFunction(f,"readn",NULL,0,(tokenType []){K_NUMBER},1);
	frameStack_initPreFunction(f,"tointeger",(tokenType []){K_NUMBER},1,(tokenType []){K_INTEGER},1);
	frameStack_initPreFunction(f,"substr",(tokenType []){K_STRING,K_INTEGER,K_INTEGER},3,(tokenType []){K_STRING},1);
	frameStack_initPreFunction(f,"ord",(tokenType []){K_STRING,K_INTEGER},2,(tokenType []){K_INTEGER},1);
	frameStack_initPreFunction(f,"chr",(tokenType []){K_INTEGER},1,(tokenType []){K_STRING},1);
	frameStack_initPreFunction(f,"write",NULL,-1,NULL,0);
}


void frameStackRealoc(frameStack * s)
{
	s->capacity=s->capacity*2;
	s->localF=realloc(s->localF,sizeof(frame)*s->capacity);
	if(s->localF==NULL)
		errorD(100,"chyba zásobníku -  realoc error");
}

void frameStackDisporse(frameStack * s)
{
	symtableDispose(&s->globalF.bTree);
	for(int i=0;i<=s->last;i++)
	{
		symtableDispose(&s->localF[i].bTree);
	}
	free(s->localF);
}

void frameStackPushFrame(frameStack * s,bool isFunc)
{	
	s->last++;
	if(!(s->last<s->capacity))
		frameStackRealoc(s);
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

void frameStackPopFrame(frameStack * s)
{
	if(s->last<0)
		errorD(99,"podtečení zásobníku rámců");
	if(searchForNonDefinedFunction(&s->localF[s->last].bTree))
		errorD(3,"Byla nalezena deklarovaná funkce bez definice");
	symtableDispose(&s->localF[s->last].bTree);	
	s->last--;
}

void frameInit(frame *f,bool wedge)
{
	f->wedge=wedge;
	symtableInit(&f->bTree);
}

STSymbolPtr * frameStackSearchVar(frameStack *f,char * key)	
{
	STSymbolPtr *data=NULL;
	for(int i=f->last;i>=0;--i)
	{
		data=symtableSearch(&f->localF[i].bTree,key);

		if(data!=NULL)
			return data;
		else if(f->localF[i].wedge)
			break;
	}
	data=symtableSearch(&f->globalF.bTree,key);
	return data;
}

STSymbolPtr * frameStackSearchFunc(frameStack *f,char * key)
{
	STSymbolPtr *data=NULL;
	for(int i=f->last;i>=0;--i)
	{
		data=symtableSearch(&f->localF[i].bTree,key);
		if(data!=NULL)
			return data;
	}
	return symtableSearch(&f->globalF.bTree,key);
}

STSymbolPtr * frameStackSearchActual(frameStack *f,char * key,bool isGolobal)
{
	return symtableSearch(isGolobal?&f->globalF.bTree:&f->localF[f->last].bTree,key);
}


STSymbolPtr * frameStackInsert(frameStack *f,char *key,bool isGlobal)
{
	if(isGlobal)
		return symtableInsertData(&f->globalF.bTree,key);
	else if(f->last>=0)
		return symtableInsertData(&f->localF[f->last].bTree,key);
	else
		errorD(99,"nelze vkládat do neexistujícího rámce");
	return NULL;
}

STSymbolPtr * frameStackInsertFunctionDeclaration(frameStack *f,char *key,bool isGlobal,bool *checkOnly)
{
	STSymbolPtr *node= frameStackSearchActual(f,key,isGlobal);
	STData * ptr=node?&(*node)->data:NULL;
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
		node=frameStackInsert(f, key,isGlobal);
		ptr=&(*node)->data;
		ptr->type=ST_FUNC;
		ptr->varData=NULL;

		ptr->funcData=malloc(sizeof(STFuncData));
		if(!ptr->funcData)
			errorD(100,"chyba při vkládání do paměťového modelu - malloc error");

		ptr->funcData->paramNum=0;
		ptr->funcData->retNum=0;
		ptr->funcData->paramTypes=NULL;
		ptr->funcData->retTypes=NULL;

		ptr->funcData->declared=true;
		ptr->funcData->defined=false;
		ptr->dekorator=0;
		*checkOnly=false;
	}
	return node;
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

	STSymbolPtr *node;
	node =frameStackInsert(f,copy,true);
	STData *ptr=&(*node)->data;
	ptr->type=ST_FUNC;
	ptr->varData=NULL;

	ptr->funcData=malloc(sizeof(STFuncData));
	if(!ptr->funcData)
		errorD(100,"chyba při vkládání do paměťového modelu - malloc error");

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

STSymbolPtr * frameStackInsertFunctionDefinition(frameStack *f,char *key,bool *checkOnly)
{
	STSymbolPtr *node;
	STData *ptr;
	if((node=frameStackSearchActual(f,key,false)))
	{}
	else if((node=frameStackSearchActual(f,key,true)))
	{}
	else
	{
		node =frameStackInsert(f,key,false);
		ptr=&(*node)->data;
		ptr->type=ST_FUNC;
		ptr->varData=NULL;

		ptr->funcData=malloc(sizeof(STFuncData));
		if(!ptr->funcData)
			errorD(100,"chyba při vkládání do paměťového modelu - malloc error");

		ptr->funcData->paramNum=0;
		ptr->funcData->retNum=0;
		ptr->funcData->paramTypes=NULL;
		ptr->funcData->retTypes=NULL;

		ptr->funcData->declared=false;
		ptr->funcData->defined=true;
		*checkOnly=false;
		return node;
	}
	ptr=&(*node)->data;
	free(key);
	*checkOnly=true;
	if(ptr->type!=ST_FUNC)
		errorD(3,"k id funcke již byla přiřazena proměnná");
	else if(ptr->funcData->defined)
		errorD(3,"tato funkce již byla definována");
	ptr->funcData->defined=true;	
	return node;
}


STSymbolPtr * frameStackInsertVar(frameStack *f,char *key,bool isGlobal,tokenType Ttype)
{
	STSymbolPtr *node=frameStackInsert(f, key,isGlobal);;
	STData *ptr=&(*node)->data;
	ptr->type=ST_VAR;
	ptr->funcData=NULL;
	ptr->varData=malloc(sizeof(STVarData));	
	if(!ptr->varData)
		errorD(100,"chyba při vkládání proměnné do paměťového modelu - malloc error");
	ptr->varData->type=Ttype;
	ptr->varData->defined=false;
	ptr->dekorator=0;
	return node;
}

void frameStackPrint(frameStack *f)
{
	debugS("------------------Symtable print------------------\nGlobal:\n");
	symtablePrint(&f->globalF.bTree);
	debugS("Local Frames:\n");
	for(int i=0;i<=f->last;i++)
	{
		symtablePrint(&f->localF[i].bTree);
		debugS("*****************\n");
	}
	debugS("------------------end of Symtable print------------------\n");
}