/**
 * @brief   Hash table
 *
 * @authors Jakub Komárek (xkomar33)
 */

#pragma once

#include "./../baseDeclarations.h"

#define HASH_TABLE_SIZE 300

typedef struct{
    struct htItem * array[HASH_TABLE_SIZE];
} hashTable;

typedef struct {
    int Data;
}htData;

typedef struct htItem {
    char *key;
    struct htItem *next;
    htData data;
} *htItemPtr;





void htInit(hashTable *ht);
void htDestruct(hashTable *ht);
void itemDestruct(htItemPtr item);
void htInsert(hashTable *ht,char *key,int data);
htItemPtr htSearch(hashTable *ht,char *key);
void htRemove(hashTable *ht,char *key);
int htHash(char * key);
void htDebug(hashTable *ht);
