/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "generator.h"

void genereteProgramHeader()
{/*
    FILE* file=fopen("built_in_functions.ifjc","r");
    if(!file)
        errorD(99,"basefunction error");
    char c;
    while ((c = getc(file)) != EOF)
        putchar(c);
    fclose(file);
*/
}

void genInst(char * inst)
{
    printf("%s\n",inst);
}

void genVar(STData * data,char * id)
{
    if(data->dekorator==0)
        printf("gf@%s\n",id);
    else
        printf("tf@%ld$%s\n",data->dekorator,id);
}

void genFuncHeader(STData * data,char * id)
{
    printf("JUMP FCEND$%ld$%s\n",data->dekorator,id);
    printf("LABEL FCSTART$%ld$%s\n",data->dekorator,id);
}
void genFuncFoter(STData * data,char * id)
{
    for(int i=0;i<data->funcData->retNum;i++)
        printf("PUSHS nil@nil\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL FCEND$%ld$%s\n",data->dekorator,id);
}