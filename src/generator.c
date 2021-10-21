/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "generator.h"

void genereteProgramHeader()
{
    printf(".IFJcode21\nCREATEFRAME\nDEFVAR gf@&JUMPVAR\n");
    /*
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

void genVar(unsigned long int decor,char * id)
{
    if(decor==0)
        printf("gf@%s\n",id);
    else
        printf("tf@%s$%ld\n",id,decor);
}

void genFuncCall(unsigned long int decor,char * id)
{
    if(decor==0)
        printf("gf@%s\n",id);
    else
        printf("tf@%ld$%s\n",decor,id);
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
    printf("POPS gf@&JUMPVAR\n");
    printf("JUMPIFEQ IFEND$%ld gf@&JUMPVAR nil@nil\n",d->dekoratorIds);
    printf("JUMPIFEQ IFEND$%ld gf@&JUMPVAR ",d->dekoratorIds);genJumpExpresion(expT);printf("\n");

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

void genWhileDecJump(systemData *d)
{
    printf("CALL WHILEDEC$%ld\n",d->dekoratorIds);
}

unsigned long int genWhileSlabel(systemData *d)
{
    printf("LABEL WHILESTART$%ld\n",d->dekoratorIds);
    d->dekoratorIds++;
    return d->dekoratorIds-1;
}

void genWhileHeader(unsigned long int decor,tokenType expT)
{
    printf("POPS gf@&JUMPVAR\n");
    printf("JUMPIFEQ WHILEEND$%ld gf@&JUMPVAR nil@nil\n",decor);
    printf("JUMPIFEQ WHILEEND$%ld gf@&JUMPVAR ",decor);genJumpExpresion(expT);printf("\n");
}

void genWhileFoter(unsigned long int decor)
{
    printf("JUMP WHILESTART$%ld\n",decor);
    printf("LABEL WHILEEND$%ld\n",decor);
}

void genWhileDecFLUSH(systemData *d,unsigned long int decor)
{
    printf("LABEL WHILEDEC$%ld\n",decor);

    while (!stackEmpty(&d->pData.varDeclarationBuffer))
    {
        token aux=stackPop(&d->pData.varDeclarationBuffer);
        printf("DEFVAR ");genVar(aux.id->decor,aux.id->id);
        free(aux.id->id);
        free(aux.id);
    }
    printf("RETURN\n");
    d->pData.isInWhile=false;
}

void genJumpExpresion(tokenType expT)
{
    switch (expT)
    {
    case K_BOOL:
        printf("bool@false\n");
        break;
    case K_STRING:
        printf("nil@nil\n");
        break;
    case K_INTEGER:
        printf("int@0\n");
        break;
    case K_NUMBER:
        printf("float@0\n");
        break;
    case K_NIL:
        printf("nil@nil\n");
        break;
    default:
        errorD(99,"if/while intern error");
        break;
    }
}
