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
MOVE TF@empty_str string@\\000\n\
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
LABEL safediv\n\
# function safediv (i: integer, j: integer) : integer\n\
# function safediv (i: number, j: number) : number\n\
\n\
PUSHFRAME\n\
CREATEFRAME\n\
\n\
DEFVAR TF@i\n\
DEFVAR TF@j\n\
\n\
MOVE TF@j gf@&regB\n\
JUMPIFEQ end_substr_error_8 TF@j nil@nil\n\
MOVE TF@i gf@&regA\n\
JUMPIFEQ end_substr_error_8 TF@i nil@nil\n\
\n\
DEFVAR TF@result\n\
\n\
DEFVAR TF@type\n\
TYPE TF@type TF@i\n\
JUMPIFEQ safediv_int TF@type string@int\n\
JUMPIFEQ safediv_number TF@type string@float\n\
\n\
# integer div\n\
LABEL safediv_int\n\
JUMPIFEQ safediv_div_zero TF@j int@0\n\
IDIV TF@result TF@i TF@j\n\
PUSHS TF@result\n\
\n\
POPFRAME \n\
RETURN\n\
\n\
# number div\n\
LABEL safediv_number\n\
JUMPIFEQ safediv_div_zero TF@j float@0x0p+0\n\
DIV TF@result TF@i TF@j\n\
PUSHS TF@result\n\
\n\
POPFRAME \n\
RETURN\n\
\n\
LABEL safediv_div_zero\n\
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
LABEL main\n\
\n\
CREATEFRAME\n\
DEFVAR gf@&JUMPVAR\n\
DEFVAR gf@&NULL\n\
DEFVAR gf@&regA\n\
DEFVAR gf@&regB\n\
DEFVAR gf@&regC\n\
");