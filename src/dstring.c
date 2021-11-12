/**
 * @brief   Dynamic string 
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "dstring.h"

void stringInit(string *s)
{
   s->capacity=STRING_BASE_SIZE;
   s->str=malloc(sizeof(char)*s->capacity);
   if(!s->str)
      errorD(100,"Chyba alokace paměti ve stringu");
   stringClear(s);
}

void stringDestruct(string *s)
{
   free(s->str);
}

void stringClear(string *s)
{
   s->str[0]='\0';
   s->length=0;
}

void stringAddChar(string *s, char c)
{
   if(stringFull(s))
      stringRealoc(s);
   s->str[s->length]=c;
   s->length++;
   addEnd(s);
}

void stringRealoc(string *s)
{
   s->capacity=s->capacity*2;
   s->str=realloc(s->str,sizeof(char)*s->capacity);
   if(!s->str)
      errorD(100,"Chyba realokace paměti ve stringu");
}

void stringRealocToSize(string *s,int newSize)
{
   s->capacity=newSize;
   s->str=realloc(s->str,sizeof(char)*s->capacity);
   if(!s->str)
      errorD(100,"Chyba realokace paměti ve stringu");
}

void stringCopy(string *s1, string *s2)
{
   if(s1->length>s2->capacity)
      stringRealocToSize(s2,s1->length+1);
   s2->length=s1->length;
   for(int i=0;i<s1->length;i++)
      s2->str[i]=s1->str[i];
   addEnd(s2);

}

void addEnd(string *s)
{
   s->str[s->length]='\0';
}

bool stringFull(string *s)
{
   return (s->length+1)>=s->capacity;
}

char* stringCpyToChPtr(string *s)
{
   return strdup(s->str);
}

char* strdup (const char* s)
{
   size_t slen = strlen(s);
   char* result = malloc(slen + 1);
   if(result == NULL)
      errorD(100,"Chyba alokace paměti ve stringu");
   strcpy(result,s);

   return result;
}