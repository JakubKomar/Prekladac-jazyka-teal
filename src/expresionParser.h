/**
 * @brief   Zpracování výrazů
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once

#include "./scaner.h"
#include "./baseDeclarations.h"
#include "./library/stack.h"

const char precTable[14][14] =
{
//	  +       -       *       /       <       >      <=      >=      ==      !=      (         )     val      $
	{'>'	,'>'	,'<'	,'<'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// +
	{'>'	,'>'	,'<'	,'<'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// -
	{'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,' '	,'>'	,'<'	,'>'},// *
	{'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,' '	,'>'	,'<'	,'>'},// /
	{'<'	,'<'	,'<'	,'<'	,' '	,' '	,' '	,' '	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// >
	{'<'	,'<'	,'<'	,'<'	,' '	,' '	,' '	,' '	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// >
	{'<'	,'<'	,'<'	,'<'	,' '	,' '	,' '	,' '	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// <=
	{'<'	,'<'	,'<'	,'<'	,' '	,' '	,' '	,' '	,'>'	,'>'	,'<'	,'>'	,'<'	,'>'},// >=
	{'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,' '	,' '	,'<'	,'>'	,'<'	,'>'},// ==
	{'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,' '	,' '	,'<'	,'>'	,'<'	,'>'},// !=
	{'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'='	,'<'	,' '},// (	
	{'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,' '	,'>'	,' '	,'>'},// )
	{'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,'>'	,' '	,'>'	,' '	,'>'},// val
	{'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,'<'	,' '	,'<'	,' '},// $
};
void expresionParse(tokenType actual,scanerData *sData);
char getSomething(tokenType actual, tokenType head);
int getOrderInTable(tokenType toDecode);