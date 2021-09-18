/**
 * @brief   Hash table
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "hashTable.h"

void htInit(hashTable *ht)
{
    for(int i=0;i<HASH_TABLE_SIZE;i++)
    {
        ht->array[i]=NULL;
    }
}

void htDestruct(hashTable *ht)
{
    for(int i=0;i<HASH_TABLE_SIZE;i++)
    {
        itemDestruct(ht->array[i]);
    }
}

void itemDestruct(htItemPtr item)
{
    htItemPtr aux;
    while (item!=NULL)
    {
        aux=item;
        item=item->next;
        free(aux);
    }
}

void htInsert(hashTable *ht,char *key,int value)
{
    int index=htHash(key);

    htItemPtr new=malloc(sizeof(struct htItem));
    if(!new)
        errorD(99,"hash table item malloc error");
    new->data.Data=value;
    new->key=key;
    htItemPtr aux= ht->array[index];
    if(aux)
    {
        htItemPtr prev;
        do
        {
            prev=aux;
            aux=aux->next;
        } while (aux);
        prev->next=new;
    }
    else
    {
        ht->array[index]=new;
    }
}

htItemPtr htSearch(hashTable *ht,char *key)
{
    int index=htHash(key);
    htItemPtr aux= ht->array[index];
    while (aux!=NULL)
    {
        if(aux->key==key)//musím použít cpy
            return aux;
        aux=aux->next;
    }
    return NULL;  
}

void htRemove(hashTable *ht,char *key)
{

}
//djb2 hash function-převzato
int htHash(char *key)
{
    long hash = 5381;
    int c;

    while (c = *key++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return (int) (hash%HASH_TABLE_SIZE);
}

void htDebug(hashTable *ht)
{
    debugS("Hash table extract:\n");
    debug("%-4s|%-4s|%-10s|%-s\n","","hash","key","data");
    htItemPtr aux;
    int counter=0;
    for(int i=0;i<HASH_TABLE_SIZE;i++)
    {
        aux=ht->array[i];
        while (aux)
        {
            debug("%-4d|%-4d|%-10s|%-d\n",counter,i,aux->key,aux->data.Data);
            counter++;
            aux=aux->next;
        }    
    }
}
