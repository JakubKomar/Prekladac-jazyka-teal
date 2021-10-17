#include "tokens.h"

char * tokenStr(token type)
{
    char * str;
    switch (type.type)
    {
        case T_ID:
            str="T_ID";
        break;
        case T_FUNC_CALL:
            str="T_FUNC_CALL";
        break;
        case T_ADD:
            str="T_ADD";
        break;
        case T_SUB:
            str="T_SUB";
        break;
        case T_DIV:
            str="T_DIV";
        break;
        case T_DIV2:
            str="T_DIV2";
        break;
        case T_MUL:
            str="T_MUL";
        break;
        case T_STR_LEN:
            str="T_STR_LEN";
        break;
        case T_ASSIGEN:
            str="T_ASSIGEN";
        break;
        case T_EQ:
            str="T_EQ";
        break;
        case T_NOT_EQ:
            str="T_NOT_EQ";
        break;
        case T_LT:
            str="T_LT";
        break;
        case T_LTE:
            str="T_LTE";
        break;
        case T_GT:
            str="T_GT";
        break;
        case T_GTE:
            str="T_GTE";
        break;
        case T_RBR:
            str="T_RBR";
        break;
        case T_LBR:
            str="T_LBR";
        break;
        case T_COLON:
            str="T_COLON";
        break;
        case T_COMMA:
            str="T_COMMA";
        break;
        case T_EOF:
            str="T_EOF";
        break;
        case T_STR:
            str="T_STR";
        break;
        case T_INT:
            str="T_INT";
        break;
        case T_DOUBLE:
            str="T_DOUBLE";
        break;
        case T_DOT2:
            str="T_DOT2";
        break;
        case K_DO:
            str="K_DO";
        break;
        case K_ELSE:
            str="K_ELSE";
        break;
        case K_END:
            str="K_END";
        break;
        case K_FUNCTION:
            str="K_FUNCTION";
        break;
        case K_GLOBAL:
            str="K_GLOBAL";
        break;
        case K_IF:
            str="K_IF";
        break;
        case K_LOCAL:
            str="K_LOCAL";
        break;
        case K_NIL:
            str="K_NIL";
        break;
        case K_READ:
            str="K_READ";
        break;
        case K_REQUIRE:
            str="K_REQUIRE";
        break;
        case K_RETURN:
            str="K_RETURN";
        break;
        case K_THEN:
            str="K_THEN";
        break;
        case K_WHILE:
            str="K_WHILE";
        break;
        case K_WRITE:
            str="K_WRITE";
        break;
        case K_STRING:
            str="K_STRING";
        break;
        case K_NUMBER:
            str="K_NUMBER";
        break;
        case K_INTEGER:
            str="K_INTEGER";
        break;
        case O_NONE:
            str="O_NONE";
        break;
        case NE_EXP:
            str="NE_EXP";
        break;
        case O_DOLAR:
            str="O_DOLAR";
        break;
        case O_HANDLE:
            str="O_HANDLE";
        break;
        case O_ERR:
            str="O_ERR";
        break;
        case O_UNIMPORTANT:
            str="O_UNIMPORTANT";
        break;
        case S_EXPRESION:
            str="S_EXPRESION";
        break;
        case K_BOOL:
            str="K_BOOL";
        break;
        default:
            str="UNKNOWN";
        break;
    }
    return str;
}
