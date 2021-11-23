/**
 * @brief   Code generator
 *
 * @authors Jakub Komárek (xkomar33)
 */
#pragma once
#include "baseDeclarations.h"
#include "symtable.h"
#include "programData.h"

/**
 * @brief genereting header of translated program-build in fucntions+internal functions
 */
void genereteProgramHeader();

/**
 * @brief generating decorated varieble
 * @param decor dekorator value
 * @param *id name of variable
 */
void genVar(unsigned long int decor,char * id);

/**
 * @brief simple print whith \n in end
 * @param *ins string to print
 */
void genInst(char * inst);

/**
 * @brief genereting header of user defined function
 * @param *data function data from symtable
 * @param *id name of function
 */
void genFuncHeader(STData * data,char * id);

/**
 * @brief genereting footer of user defined function
 * @param *data function data from symtable
 * @param *id name of function
 */
void genFuncFoter(STData * data,char * id);

/**
 * @brief genereting return comand from function
 */
void genReturn();

/**
 * @brief genereting header of if statement
 * @param *d system data
 * @param *expT type of expecting statement to compere - String,int,double...
 * @return decorator for use later
 */
unsigned long int genIfHeader(systemData *d,tokenType expT);

/**
 * @brief genereting footer of if statement 
 * @param decor decorator
 */
void genIfFoter(unsigned long int decor);

/**
 * @brief genereting jumping label for while
 * @param *d system data
 * @return decorator for use later
 */
unsigned long int genWhileSlabel(systemData *d);

/**
 * @brief genereting header for while
 * @param decor decorator 
 * @param expT type of expecting statement to compere - String,int,double...
 */
void genWhileHeader(unsigned long int decor,tokenType expT);

/**
 * @brief genereting footer for while
 * @param *d system data
 * @param decor decorator 
 * @param prevInWhile if is while submerged in another while-true else false
 */
void genWhileFoter(systemData *d,unsigned long int decor,bool prevInWhile);

/**
 * @brief genereting jump for "delcaration vars" part of generated while
 * @param *d system data
 */
void genWhileDecJump(systemData *d);

/**
 * @brief genereting delcaration for vars submerge in while/s
 * @param *d system data
 * @param decor decorator 
 */
void genWhileDecFLUSH(systemData *d,unsigned long int decor);

/**
 * @brief genereting delcaration for global vars
 * @param *d system data
 */
void genGlobalDecFLUSH(systemData *d);

/**
 * @brief genereting calculation of jumping epresion
 * @param expT type which will be compered
 */
void genJumpExpresion(tokenType expT);

/**
 * @brief genereting header of else statement
 * @param decor decorator 
 */
void genElseHeader(unsigned long int decor);

/**
 * @brief genereting footer of else statement
 * @param decor decorator 
 */
void genElseFoter(unsigned long int decor);

/**
 * @brief genereting sting constant in ifj21code format
 * @param decor decorator 
 */
void genStringConstant(char * string);

/**
 * @brief genereting escape sequence in ifj21code format
 * @param *string string from which it will be generated  
 * @param *i starting pozition of esc. seq. in string 
 */
void genEscapeSec(char * string,int *i);

/**
 * @brief genereting write "function"
 */
void genWrite();

/**
 * @brief genereting predefineted functions
 */
void buildInFuction();