#include "baseDeclarations.h"

void error(int code)
{
    if(code){
        printError(code);
        exit(code);
    } 
}

void errorD(int code,char * description)
{
    if(code){
        printError(code);
        fprintf(stderr,"More detailes: %s\n",description);
        longjmp(errorHandelingJump, code);
    } 
}

void printError(int code)
{
    char * text;
    switch (code)
    {
    case 1:
        text="chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému)";
    break;
    case 2:
        text="chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu).";
    break;
    case 3:
        text="sémantická chyba v programu – nedefinovaná funkce/proměnná, pokus o redefinici proměnné, atp";
    break;
    case 4:
        text="sémantická chyba v příkazu přiřazení (typová nekompatibilita).";
    break;
    case 5:
        text="sémantická chyba v programu – špatný počet/typ parametrů či návratových hodnotu volání funkce či návratu z funkce.";
    break;
    case 6:
        text="sémantická chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech.";
    break;
    case 7:
        text="ostatní sémantické chyby";
    break;
    case 8:
        text="běhová chyba při práci s neočekávanou hodnotou nil.";
    break;
    case 9:
        text="běhová chyba celočíselného dělení nulovou konstantou.";
    break;
    case 99:
        text="interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti, atd.).";
    break;
    default:
        text="Unknown error";
    }
    fprintf(stderr,"Error: %s\n",text);
}

