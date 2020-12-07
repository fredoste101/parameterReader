#ifndef PARAMETER_LIST_H
#define PARAMETER_LIST_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>



enum ParameterType
{  
    PARAM_TYPE_SHORT_OPT = 1,      //Ex -o -a -g
    PARAM_TYPE_LONG_OPT,           //Ex --input --file
    PARAM_TYPE_EMPTY_SHORT_OPT,    //Ex -
    PARAM_TYPE_EMPTY_LONG_OPT,     //Ex --
    PARAM_TYPE_LONG_OPT_WITH_ARG,  //Ex --file=input.txt
    PARAM_TYPE_ARG,                //Ex input.txt
};


typedef struct inputParameter
{
    enum ParameterType  type;
    char*               value;
    char*               arg;      //For ex: --input=file, then file will be placed here
} inputParameter;


typedef struct inputParameterList
{
    unsigned int    numOfElements;
    unsigned int    maxNumOfElements;
    inputParameter* list;
} inputParameterList;


int indexOfInputParameter(inputParameterList* list, char* param);

void getInputParameterAtIndex(inputParameterList* list, 
                              const unsigned int index, 
                              inputParameter* p);

/**
 * @brief Frees all allocated memory related to the parameter at given index
 * 
 * @param[in/out] list 
 * @param[in] index 
 */
void removeInputParameter(inputParameterList* list, unsigned int index);

#endif