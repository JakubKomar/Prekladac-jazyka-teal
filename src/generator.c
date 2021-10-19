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
    fprintf(stdout,"%s\n",inst);
}
