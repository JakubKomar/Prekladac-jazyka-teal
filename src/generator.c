/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#include "generator.h"

void genereteProgramHeader()
{
    buildInFuction();
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

void genGlobalDecFLUSH(systemData *d)
{
    printf("EXIT int@0\nLABEL GLOBALDEC\n");

    while (!stackEmpty(&d->pData.GlobalVarDeclarationBuffer))
    {
        token aux=stackPop(&d->pData.GlobalVarDeclarationBuffer);
        printf("DEFVAR ");genVar(0,aux.id->id);printf("\n");
        free(aux.id->id);
        free(aux.id);
    }
    printf("RETURN\n");
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
        errorD(99,"if/while interní chyba");
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
        else if(aux=='#'){
            printf("\\035");}
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
    printf("CALL write\n");
}

void buildInFuction(){
printf(".IFJcode21\n\
#\n\
# @brief Built in functions and operators\n\
#\n\
# @authors Jakub Křivánek (xkriva30)\n\
#\n\
JUMP main\n\
\n\
# BUILT IN FUNCTIONS\n\
\n\
LABEL FCSTART$0$reads\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@string\n\
READ TF@string string\n\
\n\
PUSHS TF@string\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
\n\
LABEL FCSTART$0$readi\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@string\n\
READ TF@string int\n\
\n\
PUSHS TF@string\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
\n\
LABEL FCSTART$0$readn\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@string\n\
READ TF@string float\n\
\n\
PUSHS TF@string\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
LABEL FCSTART$0$tointeger\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@f\n\
POPS TF@f\n\
\n\
JUMPIFEQ end_tointeger_nil TF@f nil@nil\n\
\n\
DEFVAR TF@i\n\
FLOAT2INT TF@i TF@f\n\
PUSHS TF@i\n\
POPFRAME\n\
RETURN\n\
\n\
LABEL end_tointeger_nil\n\
PUSHS nil@nil\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
\n\
LABEL FCSTART$0$substr\n\
# uses hastag operator\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@s\n\
DEFVAR TF@i\n\
DEFVAR TF@j\n\
\n\
\n\
POPS TF@j\n\
POPS TF@i\n\
POPS TF@s\n\
\n\
# checks if any parameter is nil\n\
DEFVAR TF@nil_check\n\
EQ TF@nil_check TF@s nil@nil\n\
JUMPIFEQ end_substr_error_8 TF@nil_check bool@true\n\
EQ TF@nil_check TF@i nil@nil\n\
JUMPIFEQ end_substr_error_8 TF@nil_check bool@true\n\
EQ TF@nil_check TF@j nil@nil\n\
JUMPIFEQ end_substr_error_8 TF@nil_check bool@true\n\
\n\
# checks if j < i\n\
DEFVAR TF@jlti\n\
LT TF@jlti TF@j TF@i\n\
JUMPIFEQ end_substr_empty TF@jlti bool@true\n\
\n\
# check if i and j arent out of bounds 1 to #s\n\
DEFVAR TF@out_of_bounds\n\
DEFVAR TF@len\n\
PUSHS TF@s\n\
CALL hashtag\n\
POPS TF@len\n\
JUMPIFEQ end_substr_error_8 TF@len nil@nil\n\
LT TF@out_of_bounds TF@i int@1\n\
JUMPIFEQ end_substr_empty TF@out_of_bounds bool@true\n\
LT TF@out_of_bounds TF@j int@1\n\
JUMPIFEQ end_substr_empty TF@out_of_bounds bool@true\n\
GT TF@out_of_bounds TF@i TF@len\n\
JUMPIFEQ end_substr_empty TF@out_of_bounds bool@true\n\
GT TF@out_of_bounds TF@j TF@len\n\
JUMPIFEQ end_substr_empty TF@out_of_bounds bool@true\n\
\n\
# sub i,j to be have the index from 0\n\
SUB TF@i TF@i int@1\n\
\n\
DEFVAR TF@ret\n\
MOVE TF@ret string@\n\
DEFVAR TF@aux\n\
\n\
DEFVAR TF@jumpvar\n\
MOVE TF@jumpvar TF@i\n\
\n\
    label cykleStart\n\
    LT TF@jumpvar TF@i TF@j\n\
    JUMPIFEQ cykleEnd TF@jumpvar bool@false\n\
    GETCHAR TF@aux TF@s TF@i\n\
    CONCAT TF@ret TF@ret TF@aux\n\
    ADD TF@i TF@i int@1\n\
    JUMP cykleStart\n\
    label cykleEnd\n\
\n\
PUSHS TF@ret\n\
POPFRAME\n\
RETURN\n\
\n\
LABEL end_substr_empty\n\
DEFVAR TF@empty_str\n\
MOVE TF@empty_str string@\n\
PUSHS TF@empty_str\n\
POPFRAME\n\
RETURN\n\
\n\
LABEL end_substr_error_8\n\
EXIT int@8\n\
\n\
\n\
LABEL FCSTART$0$ord\n\
# uses hashtag operator and substr\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@s\n\
DEFVAR TF@i\n\
\n\
POPS TF@i\n\
POPS TF@s\n\
\n\
# checks if any parameter is nil\n\
DEFVAR TF@nil_check\n\
EQ TF@nil_check TF@s nil@nil\n\
JUMPIFEQ end_ord_error_8 TF@nil_check bool@true\n\
EQ TF@nil_check TF@i nil@nil\n\
JUMPIFEQ end_ord_error_8 TF@nil_check bool@true\n\
\n\
# check if i isnt out of bounds 1 to #s\n\
DEFVAR TF@out_of_bounds\n\
DEFVAR TF@len\n\
PUSHS TF@s\n\
CALL hashtag\n\
POPS TF@len\n\
LT TF@out_of_bounds TF@i int@1\n\
JUMPIFEQ end_ord_nil TF@out_of_bounds bool@true\n\
GT TF@out_of_bounds TF@i TF@len\n\
JUMPIFEQ end_ord_nil TF@out_of_bounds bool@true\n\
\n\
PUSHS TF@s\n\
PUSHS TF@i\n\
PUSHS TF@i\n\
CALL FCSTART$0$substr\n\
POPS TF@s\n\
\n\
DEFVAR TF@ord\n\
STRI2INT TF@ord TF@s int@0\n\
PUSHS TF@ord\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
LABEL end_ord_nil\n\
PUSHS nil@nil\n\
POPFRAME\n\
RETURN\n\
\n\
LABEL end_ord_error_8\n\
EXIT int@8\n\
\n\
\n\
\n\
LABEL FCSTART$0$chr\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@i\n\
POPS TF@i\n\
\n\
# checks if i isnt nil\n\
JUMPIFEQ end_chr_error_8 TF@i nil@nil\n\
DEFVAR TF@out_of_bounds\n\
\n\
# checks if i isnt out of bounds\n\
LT TF@out_of_bounds TF@i int@0\n\
JUMPIFEQ end_chr_nil TF@out_of_bounds bool@true\n\
GT TF@out_of_bounds TF@i int@255\n\
JUMPIFEQ end_chr_nil TF@out_of_bounds bool@true\n\
\n\
DEFVAR TF@c\n\
INT2CHAR TF@c TF@i\n\
PUSHS TF@c\n\
POPFRAME\n\
RETURN\n\
\n\
LABEL end_chr_nil\n\
PUSHS nil@nil\n\
POPFRAME\n\
RETURN\n\
\n\
LABEL end_chr_error_8\n\
EXIT int@8\n\
\n\
\n\
\n\
# OPERATORS\n\
\n\
LABEL hashtag\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@str\n\
POPS TF@str\n\
JUMPIFEQ end_substr_error_8 TF@str nil@nil\n\
DEFVAR TF@len\n\
STRLEN TF@len TF@str\n\
DEFVAR TF@escaped_len\n\
MOVE TF@escaped_len TF@len\n\
\n\
DEFVAR TF@last_escaped\n\
MOVE TF@last_escaped bool@false\n\
\n\
DEFVAR TF@i\n\
MOVE TF@i int@0\n\
DEFVAR TF@c\n\
\n\
# loops throught the string and subs lenght for every escape sequence\n\
LABEL hashtag_loop\n\
JUMPIFEQ end_hashtag TF@i TF@len\n\
\n\
GETCHAR TF@c TF@str TF@i\n\
ADD TF@i TF@i int@1\n\
\n\
JUMPIFEQ hastag_not_escaped TF@last_escaped bool@false\n\
MOVE TF@last_escaped bool@false\n\
JUMP hashtag_loop\n\
\n\
LABEL hastag_not_escaped\n\
JUMPIFNEQ hashtag_loop TF@c string@\\092\n\
SUB TF@escaped_len TF@escaped_len int@1\n\
MOVE TF@last_escaped bool@true\n\
JUMP hashtag_loop\n\
\n\
\n\
LABEL end_hashtag\n\
\n\
PUSHS TF@escaped_len\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
\n\
LABEL concatenation\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@str1\n\
DEFVAR TF@str2\n\
\n\
POPS TF@str2\n\
JUMPIFEQ end_substr_error_8 TF@str2 nil@nil\n\
POPS TF@str1\n\
JUMPIFEQ end_substr_error_8 TF@str1 nil@nil\n\
DEFVAR TF@con\n\
\n\
CONCAT TF@con TF@str1 TF@str2\n\
PUSHS TF@con\n\
\n\
POPFRAME\n\
RETURN\n\
\n\
\n\
\n\
# OUR FUNCTIONS\n\
\n\
LABEL safediv_int\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
# integer div\n\
JUMPIFEQ safediv_int_div_zero gf@&regB int@0\n\
IDIV gf@&regC gf@&regA gf@&regB\n\
PUSHS gf@&regC\n\
\n\
POPFRAME \n\
RETURN\n\
\n\
LABEL safediv_int_div_zero\n\
EXIT int@9\n\
\n\
\n\
\n\
LABEL safediv_num\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
# number div\n\
JUMPIFEQ safediv_num_div_zero gf@&regB float@0x0p+0\n\
DIV gf@&regC gf@&regA gf@&regB\n\
PUSHS gf@&regC\n\
\n\
POPFRAME \n\
RETURN\n\
\n\
LABEL safediv_num_div_zero\n\
EXIT int@9\n\
\n\
\n\
\n\
LABEL neg\n\
# function neg (i: integer,) : integer\n\
# function neg (i: number) : number\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@i\n\
\n\
POPS TF@i\n\
JUMPIFEQ end_substr_error_8 TF@i nil@nil\n\
\n\
DEFVAR TF@type\n\
TYPE TF@type TF@i\n\
JUMPIFEQ neg_int TF@type string@int\n\
JUMPIFEQ neg_number TF@type string@float\n\
\n\
LABEL neg_int\n\
sub TF@i int@0 TF@i \n\
PUSHS TF@i\n\
POPFRAME\n\
RETURN\n\
\n\
# number div\n\
LABEL neg_number\n\
sub TF@i float@0x0p+0 TF@i \n\
PUSHS TF@i\n\
POPFRAME\n\
RETURN\n\
\n\
# \n\
LABEL pairPrepTN\n\
POPS gf@&regB\n\
JUMPIFEQ end_substr_error_8 gf@&regB nil@nil\n\
POPS gf@&regA\n\
JUMPIFEQ end_substr_error_8 gf@&regA nil@nil\n\
RETURN\n\
\n\
LABEL pairPrep\n\
POPS gf@&regB\n\
POPS gf@&regA\n\
RETURN\n\
\n\
LABEL sefeIntToFloat\n\
POPS gf@&regC\n\
JUMPIFEQ sefeIntToFloatJ gf@&regC nil@nil\n\
INT2FLOAT gf@&regC gf@&regC\n\
PUSHS  gf@&regC\n\
RETURN\n\
LABEL sefeIntToFloatJ\n\
PUSHS  gf@&regC\n\
RETURN\n\
\n\
LABEL write\n\
POPS gf@&regA\n\
JUMPIFEQ writeNil gf@&regA nil@nil\n\
write gf@&regA\n\
RETURN\n\
LABEL writeNil\n\
write string@nil\n\
RETURN\n\
\n\
LABEL main\n\
CALL GLOBALDEC\n\
CREATEFRAME\n\
DEFVAR gf@&JUMPVAR\n\
DEFVAR gf@&NULL\n\
DEFVAR gf@&regA\n\
DEFVAR gf@&regB\n\
DEFVAR gf@&regC\n\
");
}