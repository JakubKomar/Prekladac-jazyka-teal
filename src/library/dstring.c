/**
 * @brief   Dynamic string 
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "dstring.h"

#define STR_LEN_INC 8   //base size memory alocation of string

int strInit(string *s)
{
   if ((s->str = (char*) malloc(STR_LEN_INC)) == NULL)
      return 1;
   s->str[0] = '\0';
   s->length = 0;
   s->allocSize = STR_LEN_INC;
   return 0;
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

int strAddChar(string *s1, char c)
{
   if (s1->length + 1 >= s1->allocSize)
   {
      if ((s1->str = (char*) realloc(s1->str, s1->length + STR_LEN_INC)) == NULL)
         return 1;
      s1->allocSize = s1->length + STR_LEN_INC;
   }
   s1->str[s1->length] = c;
   s1->length++;
   s1->str[s1->length] = '\0';
   return 0;
}

int strAddString(string *s1, char *s2)
{
   int i=0;
   while(s2[i]!='\0')
   {
      if(strAddChar(s1,s2[i]))
         return 1;
      i++;
   }
   return 0;
}

int strCopyString(string *s1, string *s2)
{
   int newLength = s2->length;
   if (newLength >= s1->allocSize)
   {
      if ((s1->str = (char*) realloc(s1->str, newLength + 1)) == NULL)
         return 1;
      s1->allocSize = newLength + 1;
   }
   strcpy(s1->str, s2->str);
   s1->length = newLength;
   return 0;
}
