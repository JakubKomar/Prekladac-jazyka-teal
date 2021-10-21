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

void genFuncCall(STData * data,char * id)
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
    printf("CREATEFRAME\n");
    printf("PUSHFRAME\n");
}
void genFuncFoter(STData * data,char * id)
{
    for(int i=0;i<data->funcData->retNum;i++)
        printf("PUSHS nil@nil\n");
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL FCEND$%ld$%s\n",data->dekorator,id);
}
void genReturn()
{
    printf("POPFRAME\n");
    printf("RETURN\n");
}

unsigned long int genIfHeader(systemData *d,tokenType expT)
{
    genJumpExpresion(expT);
    if(expT!=K_STRING)
        printf("JUMPIFEQS IFEND$%ld\n",d->dekoratorIds);
    else
        printf("POPS\nJUMP IFEND$%ld\n",d->dekoratorIds);
    d->dekoratorIds++;
    return d->dekoratorIds-1;
}

void genIfFoter(unsigned long int decor)
{
    printf("LABEL IFEND$%ld\n",decor);
}

void genElseHeader(unsigned long int decor)
{
    printf("JUMP ELSEEND$%ld\n",decor);
    printf("LABEL IFEND$%ld\n",decor);
}

void genElseFoter(unsigned long int decor)
{
    printf("LABEL ELSEEND$%ld\n",decor);
}

void genJumpExpresion(tokenType expT)
{
    switch (expT)
    {
    case K_BOOL:
        printf("PUSHS bool@false\n");
        break;
    case K_STRING:
        break;
    case K_INTEGER:
        printf("PUSHS int@0\n");
        break;
    case K_NUMBER:
        printf("PUSHS float@0\n");
        break;
    case K_NIL:
        printf("PUSHS nil@nil\n");
        break;
    default:
        errorD(99,"if/while intern error");
        break;
    }
}
