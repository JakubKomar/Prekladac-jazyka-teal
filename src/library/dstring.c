/**
 * @brief   Dynamic string 
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "dstring.h"

void strInit(string *s)
{
   if ((s->str = (char*) malloc(STR_BASE_LEN)) == NULL)
      errorD(99,"String alocation error");
   s->str[0] = '\0';
   s->length = 0;
   s->allocSize = STR_BASE_LEN;
}

void strFree(string *s)
{
   free(s->str);
}

void strClear(string *s)
{
   s->str[0] = '\0';
   s->length = 0;
}

void strAddChar(string *s1, char c)
{
   if (s1->length + 1 >= s1->allocSize)
   {
      if(realocate(s1))
         errorD(99,"String alocation error");
   }
   s1->str[s1->length] = c;
   s1->length++;
   s1->str[s1->length] = '\0';
}

int realocate(string *s)
{
   s->str = realloc(s->str, s->length*2);
   if((s->str)==NULL)
      return -1;
   s->allocSize = s->length*2;
   return 0;
}

void strCopyString(string *s1, string *s2)
{
   int newLength = s2->length;
   if (newLength >= s1->allocSize)
   {
      if ((s1->str = (char*) realloc(s1->str, newLength + 1)) == NULL)
         errorD(99,"String alocation error");
      s1->allocSize = newLength + 1;
   }
   strcpy(s1->str, s2->str);
   s1->length = newLength;
   return 0;
}
