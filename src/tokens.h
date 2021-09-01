/**
 * @brief   tokens for translator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

typedef enum{   //typy tokenů
    T_ID,
    T_RBR,      //pravá závorka
    T_LBR,      //levá závorka
    T_GT,       //>
    T_GTE,      //>=
    T_LT,       //>
    T_LTE,      //<=
    T_NEQ,      //   !=
    T_ASSIGEN,  // =
    T_EQL,      //  ==
    T_DIV,      //dělení /
    T_MUL,      //násobení *
    T_SUB,      //odčítání -
    T_ADD,      //sčítání    +
    //neterminály
    N_START,
    //ostatní
    O_HANDLE,   //začátek handle
    O_DOLAR,
    O_ERR,      //nesmí nastat // ze scenru se nevypíše
    O_UNIMPORTANT,//token nebude zapsán do listu-není důležitý // ze scenru se nevypíše
}tokenType;