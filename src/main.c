/**
 * @brief   main
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "main.h"


int main(int argc, char** argv)
{
    bool scanerOnlyF=false;
    bool expresionOnlyF=false;
    bool debugF=false;
    for(int i=1;i<argc;i++){
        if(!strcmp(argv[i],"-d"))
            debugF=true;
        else if(!strcmp(argv[i],"-s"))
            scanerOnlyF=true;
        else if(!strcmp(argv[i],"-e"))
            expresionOnlyF=true;
        else if(!strcmp(argv[i],"-h")){
            fprintf(stderr,"Translater of programing language něco to programing language IFJ21\noptions:\n\t-d\tdebug mode enable\n\t-s\tsematic check only\n\t-h\tprint help\n");
            exit(0);
        }
        else{
            fprintf(stderr,"Arg not recognize,try \"-h\"\n");
            exit(99);
        }
    }
    if(debugF)
        debugRun(scanerOnlyF,expresionOnlyF);

    parserMain();
    return 0;
}

void debugRun(bool scanerOnlyF,bool expresionOnlyF)
{
    if(scanerOnlyF)
    {
        scanerData scData;
        token actualToken=(token){O_UNIMPORTANT,NULL};
        initScanerData(&scData);
        int i=0;
        while(actualToken.type!=T_EOF)
        {
            actualToken=getNextUsefullToken(&scData);
            debug("%d\t%-10s\t%s\n",i,tokenStr(actualToken),scData.fullToken.str);
            i++;
        }
        stringDestruct(&(scData.fullToken));
    }
    else if(expresionOnlyF)
    {
        scanerData scData;
        token actualToken=(token){O_UNIMPORTANT,NULL};
        initScanerData(&scData);
        while(actualToken.type!=T_EOF)
        {
            actualToken=getNextUsefullToken(&scData);
            expresionParse(actualToken,&scData);
        }
    }
    exit(0);
}