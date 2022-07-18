#include <stdio.h>
#include <stdlib.h>
//jednoduchej skript na převod base codu do formátu printf
//nutno změnit řádkování ve zdrojovém souboru na lf !!!!!! 
#define out stdout
#define in stdin
int main(int argc, char** argv)
{
    fprintf(out,"printf(\"");
    char ch;
    ch=fgetc(in);
    while (ch!=EOF)
    {
        switch (ch)
        {
            case '\\':
                fprintf(out,"\\\\");
                break;
            case '%':
                fprintf(out,"%%%%");
                break;
            case '\n':
                fprintf(out,"\\n\\\n");
                break;
            default:
                fprintf(out,"%c",ch);
                break;
            }
        
        ch=fgetc(in);
    }
    fprintf(out,"\");");

   return 0;
}
