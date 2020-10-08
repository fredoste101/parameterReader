#include "parameterList.h"

#define INPUT_PARAMETER_LIST_INCREMENT_SIZE 10


static void increaseSizeOfList(inputParameterList* list);


int indexOfInputParameter(inputParameterList* list, char* param)
{
    unsigned int i;
    for(i = 0; i < list->numOfElements; i++)
    {
        if(strcmp(param, list->list[i].value) == 0)
        {
            return i;
        }
    }

    return -1;
}


void getInputParameterAtIndex(inputParameterList* list, const unsigned int index, inputParameter* p)
{
    if(index >= list->numOfElements)
    {
        p = NULL;
        return;
    }

    memcpy(p, &list->list[index], sizeof(inputParameter));
}


void removeInputParameter(inputParameterList* list, unsigned int index)
{

    //Remove allocated value
    if(list->list[index].value != NULL)
    {
        free(list->list[index].value);
    }

    //Remove allocated arg
    if(list->list[index].arg != NULL)
    {
        free(list->list[index].arg);
    }

    for(index; index < (list->numOfElements - 1); index++)
    {
        memcpy(&list->list[index], &list->list[index+1], sizeof(inputParameter));
    }

    list->numOfElements--;
}


static void enqueueInputParameter(inputParameterList* list, inputParameter* param)
{
    if(list->numOfElements == list->maxNumOfElements)
    {
        increaseSizeOfList(list);
    }

    memcpy(&list->list[list->numOfElements], param, sizeof(*param));
    list->numOfElements++;
}


static void increaseSizeOfList(inputParameterList* list)
{
    unsigned int newSize = sizeof(inputParameter) * (list->maxNumOfElements + INPUT_PARAMETER_LIST_INCREMENT_SIZE);
    
    void* tempList = malloc(newSize);


    if(!tempList)
    {
        perror("Malloc failed!");
        exit(1);
    }

    memcpy(tempList, list->list, (list->maxNumOfElements * sizeof(inputParameter)));

    free(list->list);

    list->maxNumOfElements += INPUT_PARAMETER_LIST_INCREMENT_SIZE;
    list->list              = (inputParameter*) tempList;
}


void handleShortOption(inputParameterList* list, char* value)
{
    unsigned int numOfArgs = strlen(value) - 1;
    unsigned int i;

    inputParameter input;
    memset(&input, 0, sizeof(input));
    
    input.type = PARAM_TYPE_SHORT_OPT;

    for(i = 0; i < numOfArgs; i++)
    {
        input.value     = (char*)malloc(sizeof(char)*2);
        memset(input.value, '\0', 2);
        *(input.value)  = value[i+1];

        enqueueInputParameter(list, &input);
    }
}


void handleLongOption(inputParameterList* list, char* opt)
{
    inputParameter input;
    memset(&input, 0, sizeof(input));
    
    input.type = PARAM_TYPE_LONG_OPT;

    input.value = (char*)malloc(sizeof(char) * strlen(opt) + 1);
    strcpy(input.value, opt);

    enqueueInputParameter(list, &input);
}


void handleLongOptionWithArg(inputParameterList* list, char* opt, char* arg)
{
    inputParameter input;
    memset(&input, 0, sizeof(input));
    
    input.type = PARAM_TYPE_LONG_OPT_WITH_ARG;

    input.value = (char*)malloc(sizeof(char) * strlen(opt) + 1);
    strcpy(input.value, opt);

    input.arg = (char*)malloc(sizeof(char) * strlen(arg) + 1);
    strcpy(input.arg, arg);



    enqueueInputParameter(list, &input);
}


void handleArgument(inputParameterList* list, char* arg)
{
    inputParameter input;
    memset(&input, 0, sizeof(input));
    
    input.type = PARAM_TYPE_ARG;

    input.value = (char*)malloc(sizeof(char) * strlen(arg) + 1);
    strcpy(input.value, arg);

    enqueueInputParameter(list, &input);
}