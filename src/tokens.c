#include "tokens.h"

char * tokenStr(tokenType type)
{
    char * str;
    switch (type)
    {
    case T_ID:
        str="T_ID";
    break;
    case T_ADD:
        str="T_ADD";
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
    default:
        str="UNDEFINED";
        break;
    }
    return str;
}
