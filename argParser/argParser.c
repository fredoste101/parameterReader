
#include <stdlib.h>
#include <string.h>

static int getAllArgumentTotalStrLen(int argc, char* argv[]);
static char* getAllArgString(int argc, char* argv[]);

int argParser(int argc, char* argv[])
{
    
    char* argString = getAllArgString(argc, argv);

    yy_scan_buffer(argString, strlen(argString));


    yyparse();


    free(argString);
}


static char* getAllArgString(int argc, char* argv[])
{

    int totalArgStrLen = getAllArgumentTotalStrLen(argc, argv);

    char* argString = (char*)malloc( sizeof(char) * totalArgStrLen );

    memset(argString, '\0', (sizeof(char) * totalArgStrLen));


    copyArgToSingleStr(argc, argv, argString);

    return argString;

}


static int getAllArgumentTotalStrLen(int argc, char* argv[])
{
    int i = 0;
    int totalLength = 0;

    for(i; i < argc; i++)
    {
        totalLength += strlen(argv[i]);
    }

    totalLength++; //To accomodate '\0'
    return totalLength;
}


static int copyArgToSingleStr(int argc, char* argv[], char* dest)
{
    int i = 0;
    
    for(i; i < argc; i++)
    {
        memcpy(dest, argv[i], sizeof(char) * strlen(argv[i]));
    }
}