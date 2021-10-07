/*
@file pre_funcs.ifjcode20.c

Soubor s hlavičkou

IFJ20; tým 125, varianta I

Autor:  Jakub Komárek,  xkomar33
        Michal Kraus,   xkraus14
*/

#include "pre_funcs.h"

void generateStart() {
 printf(".IFJcode20\n\
JUMP $$main\n\
#begining of pre-definated funktions\n\
\n\
LABEL $len  #vrátí délku řetězce\n\
    PUSHFRAME\n\
    DEFVAR LF@%%retval1\n\
    MOVE LF@%%retval1 int@0\n\
\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1\n\
\n\
    STRLEN LF@%%retval1 LF@%%param1\n\
\n\
    POPFRAME\n\
    RETURN\n\
\n\
LABEL $inputs  #inputs\n\
    PUSHFRAME\n\
\n\
    DEFVAR LF@%%retval1\n\
    DEFVAR LF@%%retval2\n\
    MOVE LF@%%retval2 int@0\n\
\n\
    READ LF@%%retval1 string\n\
\n\
    DEFVAR LF@!sysprom\n\
    TYPE LF@!sysprom LF@%%retval1\n\
\n\
    JUMPIFEQ $inputs$noterr LF@!sysprom string@string   #sice mě nenapá kdyby to mohlo nastat, ale projistotu...\n\
        MOVE LF@%%retval2 int@1\n\
    LABEL $inputs$noterr  \n\
\n\
    POPFRAME\n\
    RETURN\n\
\n\
LABEL $inputi  #inputi\n\
    PUSHFRAME\n\
\n\
    DEFVAR LF@%%retval1\n\
    DEFVAR LF@%%retval2\n\
    MOVE LF@%%retval2 int@0\n\
\n\
    READ LF@%%retval1 int\n\
\n\
    DEFVAR LF@!sysprom\n\
    TYPE LF@!sysprom LF@%%retval1\n\
\n\
    JUMPIFEQ $inputi$noterr LF@!sysprom string@int\n\
        MOVE LF@%%retval2 int@1\n\
    LABEL $inputi$noterr  \n\
\n\
    POPFRAME\n\
    RETURN\n\
\n\
LABEL $inputf  #inputf\n\
    PUSHFRAME\n\
\n\
    DEFVAR LF@%%retval1\n\
    DEFVAR LF@%%retval2\n\
    MOVE LF@%%retval2 int@0\n\
\n\
    READ LF@%%retval1 float\n\
\n\
    DEFVAR LF@!sysprom\n\
    TYPE LF@!sysprom LF@%%retval1\n\
\n\
    JUMPIFEQ $inputf$noterr LF@!sysprom string@float\n\
    MOVE LF@%%retval2 int@1\n\
    LABEL $inputf$noterr  \n\
\n\
    POPFRAME\n\
    RETURN\n\
\n\
");
printf("LABEL $print    #print prozatím s jedním parametrem, asi bych ji rozgeneroval na volání funkce po jednom parametru, nenapadá mě jak zjistit, kolik parametrů je do fukce posláno\n\
    PUSHFRAME\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1\n\
    WRITE LF@%%param1\n\
\n\
\n\
    POPFRAME\n\
    RETURN\n\
\n\
\n\
LABEL $chr\n\
    PUSHFRAME\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1\n\
    DEFVAR LF@%%retval1\n\
    MOVE LF@%%retval1 nil@nil\n\
    DEFVAR LF@%%retval2\n\
    MOVE LF@%%retval2 int@0\n\
\n\
    DEFVAR LF@!sysprom\n\
    gt LF@!sysprom LF@%%param1 int@255\n\
    JUMPIFEQ $chr$err LF@!sysprom bool@true\n\
\n\
    lt LF@!sysprom LF@%%param1 int@0\n\
    JUMPIFEQ $chr$err LF@!sysprom bool@true\n\
\n\
    INT2CHAR LF@%%retval1 LF@%%param1\n\
    JUMP $chr$noterr \n\
\n\
    LABEL $chr$err  \n\
        MOVE LF@%%retval2 int@1\n\
    LABEL $chr$noterr  \n\
\n\
    POPFRAME\n\
    RETURN\n\
\n\
LABEL $substr\n\
    PUSHFRAME\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1 \n\
    DEFVAR LF@%%param2\n\
    MOVE LF@%%param2 LF@%%2\n\
    DEFVAR LF@%%param3\n\
    MOVE LF@%%param3 LF@%%3\n\
\n\
    DEFVAR LF@%%retval1 \n\
    MOVE LF@%%retval1 string@\n\
    DEFVAR LF@%%retval2\n\
    MOVE LF@%%retval2 int@0\n\
\n\
    DEFVAR LF@!sysprom\n\
    DEFVAR LF@!sysprom1\n\
    DEFVAR LF@!sysprom2\n\
\n\
    CREATEFRAME \n\
        DEFVAR TF@%%1\n\
        MOVE TF@%%1 LF@%%param1\n\
        CALL $len\n\
    MOVE LF@!sysprom TF@%%retval1 #delka retezce\n\
\n\
    LT LF@!sysprom2 LF@%%param2 int@0\n\
    JUMPIFEQ $substr$err LF@!sysprom2 bool@true\n\
\n\
    gt LF@!sysprom2 LF@%%param2 LF@!sysprom \n\
    JUMPIFEQ $substr$err LF@!sysprom2 bool@true\n\
    \n\
    LT LF@!sysprom2 LF@%%param3 int@0\n\
    JUMPIFEQ $substr$err LF@!sysprom2 bool@true\n\
\n\
    SUB LF@!sysprom1 LF@!sysprom LF@%%param2\n\
    GT LF@!sysprom2 LF@%%param3 LF@!sysprom1\n\
    JUMPIFEQ $substr$err LF@!sysprom2 bool@true\n\
\n\
    DEFVAR LF@!sysprom4 \n\
    MOVE   LF@!sysprom4 int@0\n\
    \n\
    DEFVAR LF@!sysprom5\n\
\n\
    LABEL $substr$WHILE\n\
        LT LF@!sysprom2 LF@!sysprom4  LF@%%param3\n\
        JUMPIFNEQ $substr$noterr LF@!sysprom2 bool@true\n\
\n\
            GETCHAR LF@!sysprom5 LF@%%param1 LF@%%param2\n\
            CONCAT  LF@%%retval1 LF@%%retval1 LF@!sysprom5\n\
\n\
            add LF@%%param2 LF@%%param2 int@1\n\
            add LF@!sysprom4 LF@!sysprom4 int@1\n\
        \n\
    JUMP $substr$WHILE\n\
 \n\
    LABEL $substr$err\n\
         MOVE LF@%%retval2 int@1\n\
    LABEL $substr$noterr\n\
    POPFRAME\n\
    RETURN\n\
\n\
LABEL $ord\n\
    PUSHFRAME\n\
\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1 \n\
    DEFVAR LF@%%param2\n\
    MOVE LF@%%param2 LF@%%2\n\
\n\
    DEFVAR LF@%%retval1 \n\
    MOVE LF@%%retval1 nil@nil\n\
    DEFVAR LF@%%retval2 \n\
    MOVE LF@%%retval2 int@0\n\
\n\
    CREATEFRAME \n\
        DEFVAR TF@%%1\n\
        MOVE TF@%%1 LF@%%param1\n\
        DEFVAR TF@%%2\n\
        MOVE TF@%%2 LF@%%param2\n\
        DEFVAR TF@%%3\n\
        MOVE TF@%%3 int@1\n\
        CALL $substr\n\
    MOVE LF@%%retval2 TF@%%retval2\n\
    JUMPIFEQ $ordERR LF@%%retval2 int@1\n\
    STRI2INT LF@%%retval1 TF@%%retval1 int@0 \n\
    LABEL $ordERR\n\
    POPFRAME\n\
    RETURN\n\
\n\
LABEL  $float2int\n\
    PUSHFRAME\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1 \n\
    \n\
    DEFVAR LF@%%retval1 \n\
    FLOAT2INT LF@%%retval1 LF@%%param1\n\
\n\
    POPFRAME\n\
    RETURN\n\
LABEL  $int2float\n\
    PUSHFRAME\n\
    DEFVAR LF@%%param1\n\
    MOVE LF@%%param1 LF@%%1 \n\
    \n\
    DEFVAR LF@%%retval1 \n\
    INT2FLOAT LF@%%retval1 LF@%%param1\n\
\n\
    POPFRAME\n\
    RETURN\n\
#end of pre-definated fucktions\n\
\n\
\n\
LABEL $$main\n\
");
}
