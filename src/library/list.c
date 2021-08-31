/**
 * @brief   Structure 2way list
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "list.h"

void initList (list *l) 
{
    l->act=NULL;
    l->first=NULL;
    l->last =NULL;
}
void disposeList (list *l) 
{
    while(l->first)
    {
        l->act=l->first;
        l->first=l->first->rptr;
        free(l->first);
    }
    initList(l);
}
void insertLast(list *l, listItem new) 
{	     
    new->lptr=l->last;
    new->rptr=NULL;
    if(l->last!=NULL) 
        l->last->rptr=new;
    else 
        l->first=new;
    l->last=new;
}
void insertFirst(list *l, listItem new) 
{	     
    new->lptr=NULL;
    new->rptr=l->first;
    if(l->first!=NULL) 
        l->first->lptr=new;
    else 
        l->last=new;
    l->first=new;
}
void printList(list *l)
{
    fprintf(stderr,"list extract:");
    listItem aux=l->first;
    int i=0;
    while(aux){
        fprintf(stderr,"%-4d: %d ",i,aux);
        aux=aux->rptr;
        i++;
    }
}