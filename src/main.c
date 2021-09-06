/**
 * @brief   main
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "baseDeclarations.h"
#include "main.h"


int main(int argc, char** argv)
{
    bool debugF=false;
    bool scanerOnlyF=false;

    for(int i=1;i<argc;i++)
    {
        if(!strcmp(argv[i],"-d"))
        {
            debugF=true;
        }
        else if(!strcmp(argv[i],"-s"))
        {
            scanerOnlyF=true;
        }
        else if(!strcmp(argv[i],"-h"))
        {
            fprintf(stderr,"Translater of programing language něco to programing language IFJ21\noptions:\n\t-d\tdebug mode enable\n\t-s\tsematic check only\n\t-h\tprint help\n");
            exit(0);
        }
        else
        {
            fprintf(stderr,"Arg not recognize,try \"-h\"\n");
            exit(-1);
        }
    }
    if(debugF)
        debug(scanerOnlyF);

    parserMain();
    return 0;
}
void debug(bool scanerOnlyF)
{
    if(scanerOnlyF)
    {
        scanerData scData;
        tokenType actualToken;
        initScanerData(&scData);
        while(actualToken!=T_EOF)
            actualToken=getNextToken(&scData);
    }
    exit(0);
}