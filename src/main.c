/**
 * @brief   main
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "main.h"


int main(int argc, char** argv)
{
    if(FORM_FILE)
    {
        fp=fopen("C:\\letsCodeSomeShit\\IFJ-2021\\src\\test.lua","r");
        if(!fp)
        {
            fprintf(stderr,"file not opened\n");
            exit(1);
        }
    }
    argParse(argc,argv);
    
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
        case 100:    //catch malloc_error : by invalid allocation of resorses - to avoid segmatation falut just exit the program, garbrege collector shoud dealocate memory later
            errCode=99;
        break;
        default:    //catch
            errorVisualization(&sData.sData);
            systemDataDestruct(&sData);
        break;
    }
    
    if(FORM_FILE)
        fclose(fp);
        
    return errCode;
}

void argParse(int argc, char** argv)
{
    for(int i=1;i<argc;i++)
    {
        if(!strcmp(argv[i],"-h")){
            fprintf(stderr,"Translater of programing language Teal to programing language IFJ21code\noptions:\n\t-d\tdebug mode enable\n\t-s\tsematic check only\n\t-h\tprint help\n");
            exit(0);
        }
        else{
            fprintf(stderr,"Arg not recognize,try \"-h\"\n");
            exit(99);
        }
    }
}
