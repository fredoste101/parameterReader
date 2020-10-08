#include <stdio.h>
#include <parameterList.h>
#include <parameterReader.h>


int main(int argc, char* argv[])
{
    printf("\nTesting....\n");

    inputParameterList list;

    memset(&list, 0, sizeof(list));

    list.list = NULL;
    printf("\nSTARTING PARSE\n");

    parameterReader(argc, argv, &list);

    printf("\nnumOfElements=%d\n", list.numOfElements);

    inputParameter p;
    getInputParameterAtIndex(&list, 0, &p);


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