/**
 * Implementace překladače imperativního jazyka IFJ21
 * @brief   main
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "main.h"


int main(int argc, char** argv)
{
    argParse(argc,argv);
    
    systemData sData;
    systemDataInit(&sData);

    int errCode=setjmp(errorHandelingJump); //simulating try catch block
    switch (errCode)
    {
        case 0:     //try
            parserMain(&sData);
            systemDataDestruct(&sData);
            return 0;
        break; 
        case 100:    //catch malloc_error : by invalid allocation of resorses - to avoid segmatation falut just exit the program, garbrege collector shoud dealocate memory later
            errCode=99;
        break;
        default:    //catch
            errorVisualization(&sData.sData);
            systemDataDestruct(&sData);
        break;
    }
            
    return errCode;
}

void argParse(int argc, char** argv)
{
    for(int i=1;i<argc;i++)
    {
        if(!strcmp(argv[i],"-h")){
            fprintf(stderr,"Překladač programovacího jazyka Teal do jazyka IFJ21code.\nVstup/výstup přes stdin/out\nparametry:\n-h\tprint help\n");
            exit(0);
        }
        else{
            fprintf(stderr,"Argument nebyl rozeznán \"-h\"\n");
            exit(99);
        }
    }
}
