/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "generator.h"

void genereteProgramHeader()
{
    if(!FORM_FILE){
    FILE* file=fopen("built_in_functions.ifjc","r");
    if(!file)
    {
        file=fopen("./src/built_in_functions.ifjc","r");
        if(!file){
            file=fopen("./../src/built_in_functions.ifjc","r");
            if(!file)
                errorD(99,"basefunction error");
        }
    }
    char c;
    while ((c = getc(file)) != EOF)
        putchar(c);
    fclose(file);
    }
}

void genInst(char * inst)
{
    printf("%s\n",inst);
}

void genVar(unsigned long int decor,char * id)
{
    if(decor==0)
        printf("gf@%s",id);
    else
        printf("tf@%s$%ld",id,decor);
}

void genFuncHeader(STData * data,char * id)
{
    printf("JUMP FCEND$%ld$%s\n",data->dekorator,id);
    printf("LABEL FCSTART$%ld$%s\n",data->dekorator,id);
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
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

void genWhileFoter(systemData *d,unsigned long int decor,bool prevInWhile)
{
    printf("JUMP WHILESTART$%ld\n",decor);
    if(!prevInWhile)
        genWhileDecFLUSH(d,decor);
    printf("LABEL WHILEEND$%ld\n",decor);
}

void genWhileDecFLUSH(systemData *d,unsigned long int decor)
{
    printf("LABEL WHILEDEC$%ld\n",decor);

    while (!stackEmpty(&d->pData.varDeclarationBuffer))
    {
        token aux=stackPop(&d->pData.varDeclarationBuffer);
        printf("DEFVAR ");genVar(aux.id->decor,aux.id->id);printf("\n");
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

void genStringConstant(char * string)
{
    char aux=string[0];
    int i=0;
    while (aux!='\0')
    {
        if(aux=='\"')
        {   
            aux=string[++i];
            continue;
        }
        else if(aux=='\\')
        {
            genEscapeSec(string,&i);
            aux=string[i];
            continue;
        }
        else if(aux=='\t'){
            printf("\\009");}
        else if(aux==' '){
            printf("\\032");}
        else
            printf("%c",aux);
        aux=string[++i];
    }
    
}

void genEscapeSec(char * string,int *i)
{
    (*i)++;
    printf("\\");
    if(string[(*i)]=='t')
    {printf("009");}
    else if (string[(*i)]=='n')
    {printf("010");}
    else if (string[(*i)]=='"')
    {printf("034");}
    else if (string[(*i)]=='\\')
    {printf("092");}
    else
    {
        for(int j=0;j<3;j++)
        {
            printf("%c",string[(*i)]);
            (*i)++;
        }
        return;
    }
    (*i)++;
}

void genWrite()
{
    printf("POPS gf@&regA\nWRITE gf@&regA\n");
}