#include <stdio.h>
#include <parameterList.h>
#include <parser.h>

inputParameterList list;

int main()
{
    printf("\nTesting....\n");

    memset(&list, 0, sizeof(list));

    list.list = NULL;
    printf("\nSTARTING PARSE\n");
    yyparse();

    printf("\nnumOfElements=%d\n", list.numOfElements);

    inputParameter p;
    getInputParameterAtIndex(&list, 0, &p);


/*
    printf("\nType: %d %c\n", p.type, *p.value);

    int i = indexOfInputParameter(&list, "input");

    printf("\n index: %d \n", i);


    getInputParameterAtIndex(&list, i, &p);
    printf("\nArg: %s\n", p.value);
*/


    unsigned int i = 0;
    for(i = 0; i < list.numOfElements; i++)
    {
        getInputParameterAtIndex(&list, i, &p);

        switch(p.type)
        {
            case PARAM_TYPE_SHORT_OPT:
                printf("\nSHORT OPT: %s\n", p.value);
            break;
            case PARAM_TYPE_LONG_OPT:
                printf("\nLONG OPT: %s\n", p.value);
            break;
            case PARAM_TYPE_LONG_OPT_WITH_ARG:
                printf("\nLONG OPT WITH ARG: %s = %s\n", p.value, p.arg);
            break;
            case PARAM_TYPE_ARG:
                printf("\nARGUMENT: %s\n", p.value);
            break;
            default:
                printf("\nNot handled type: %d\n", p.type);
            break;
        }
    }
}