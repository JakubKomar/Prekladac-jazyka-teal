/**
 * @brief   Sym table probably...
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "btree.h"


void bInit(bNodePtr *tree)
{
    *tree = NULL;
}

void bDestruct(bNodePtr *tree)
{
    if((*tree) != NULL){
        bDestruct(&(*tree)->lPtr);
        bDestruct(&(*tree)->rPtr);
        free(*tree);
        *tree = NULL;
    }
}

void bInsert(bNodePtr *tree, char *key, bData data)
{
    if(*tree==NULL)	//pokud uzel neexistuje, musí se vytvořit
	{
		*tree=malloc(sizeof(struct bNode));
		if(*tree==NULL) //alakoce se nezdařila
			errorD(99,"binary tree maloc error");	
		//naplnění uzlu daty
		(*tree)->lPtr=NULL;
		(*tree)->rPtr=NULL;
		(*tree)->key=key;
		(*tree)->data=data;
	}
	else	//pokud  uzel existuje, zkontroluje se klíč
	{
        int cmp = strcmp(key, (*tree)->key); 
		if(cmp==0)	//pokud položka se stejným klíčem existuje pouze přepíšeme obsah
			errorD(99,"redefinice položky v b. stromě");
		else					//jinak se zvolí podle klíče podstrom, který nad kterým se zavolá tato funkce znova				
		{		
			if(cmp < 0) 
				bInsert(&(*tree)->lPtr,key,data); 	
			else 
				bInsert(&(*tree)->rPtr,key,data);
		}
	}
}

void bDelete(bNodePtr *tree, char *key)
{
    if((*tree) != NULL)
    {   
        int cmp = strcmp(key, (*tree)->key);  
        if(cmp < 0)
            bDelete(&(*tree)->lPtr, key);
        else if(cmp > 0)
            bDelete(&(*tree)->rPtr, key);
        else
        {
            replaceByRightmost((*tree), (&(*tree)->lPtr));
            if((*tree)->rPtr == NULL)
                (*tree) = (*tree)->lPtr;
            else
                (*tree) = (*tree)->rPtr;
        }
    }
}

bNodePtr bSearch(bNodePtr *tree, char *key)
{
    if(tree)
    {
        int cmp = strcmp(key, (*tree)->key);  
        if(cmp==0) 
            return (*tree);            
        if(cmp < 0) 
            return bSearch(&(*tree)->lPtr,key);
        else
            return bSearch(&(*tree)->rPtr,key);
    }
    else
        return NULL;
}

void replaceByRightmost (bNodePtr PtrReplaced, bNodePtr *tree)
{
    if((*tree) != NULL)
    {
        if((*tree)->rPtr != NULL)
            replaceByRightmost(PtrReplaced, &(*tree)->rPtr);
        else
        {
            PtrReplaced->data = (*tree)->data;
            PtrReplaced->key = (*tree)->key;
            bNodePtr tmp = (*tree);
            (*tree) = (*tree)->lPtr;
            free(tmp);
        }
    }
}

void bPrint(bNodePtr *tree)
{
    if((*tree) != NULL)
    {   
        nodePrint(tree);  
        bPrint(&(*tree)->lPtr);
        bPrint(&(*tree)->rPtr);
    }
}

void nodePrint(bNodePtr *tree)
{
    debugS("bin tree data...");
}