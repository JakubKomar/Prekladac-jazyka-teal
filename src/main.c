/**
 * @brief   main
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "main.h"


int main(int argc, char** argv)
{
    
    fp=fopen("C:\\letsCodeSomeShit\\IFJ-2021\\src\\test.lua","r");
    if(!fp)
    {
        fprintf(stderr,"file not opened\n");
        exit(1);
    }
    argParse( argc, argv);
    systemData sData;
    systemDataInit(&sData);
    int errCode=setjmp(errorHandelingJump); //simulating try catch block
    switch (errCode)
    {
        case 0:     //try
            parserMain(&sData);
            systemDataDestruct(&sData);
            fprintf(stderr,"\033[32mTranslate successful \033[0m\n");//odstranit před odevzdáním, pouze vizualizace korekního překladu
            return 0;
        break; 
        case 100:    //error by invalid allocation of resorses - to avoid segmatation falut just exit the program, garbrege collector shoud dealocate memory later
            errCode=99;
        break;
        default:    //catch
            errorVisualization(&sData.sData);
            systemDataDestruct(&sData);
        break;
    }
    fclose(fp);
    return errCode;
}

void argParse(int argc, char** argv)
{
    bool scanerOnlyF=false;
    bool expresionOnlyF=false;
    bool debugF=false;
    for(int i=1;i<argc;i++)
    {
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
}

void debugRun(bool scanerOnlyF,bool expresionOnlyF)
{
    systemData sData;
    systemDataInit(&sData);
    int errCode=setjmp(errorHandelingJump); 
    switch (errCode)
    {
        case 0:  //try
            if(scanerOnlyF)
            {
                scanerData scData;
                initScanerData(&scData);
                token actualToken=getNextUsefullToken(&scData);

                for(int i=0;actualToken.type!=T_EOF;i++)
                {
                    actualToken=getNextUsefullToken(&scData);
                    debug("%d\t%-10s\t%s\n",i,tokenStr(actualToken),scData.fullToken.str);
                }
                destructScanerData(&scData);
            }
            else if(expresionOnlyF)
            {               
                while(sData.pData.actualToken.type!=T_EOF)
                {
                    sData.pData.actualToken=getNextUsefullToken(&sData.sData);
                    expresionParse(&sData);
                }
            }
            systemDataDestruct(&sData);
        break; 
        case 100:    //error by invalid allocation of resorses - to avoid segmatation falut just exit the program, garbrege collector shoud dealocate memory later
            errCode=99;
        break;
        default:    //catch
            systemDataDestruct(&sData);
        break;
    }
    exit(errCode);
}