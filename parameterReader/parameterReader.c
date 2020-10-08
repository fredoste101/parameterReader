
#include <stdlib.h>
#include <string.h>
#include <parser.h>
#include <lexer.h>
#include <parameterList.h>

#include "parameterReader.h"

static int getAllArgumentTotalStrLen(int argc, char* argv[]);
static char* concatArgsToSingleString(int argc, char* argv[]);
static int copyArgToSingleString(int argc, char* argv[], char* dest);

int parameterReader(int argc, char* argv[], inputParameterList* listP)
{
    
    char* argString = concatArgsToSingleString(argc, argv);

    //Set this string to be read by the lexer/scanner (yylex) whilst parsing (yyparse)
    yy_scan_buffer(argString, strlen(argString));

    yyparse(listP);

    free(argString);
}


static char* concatArgsToSingleString(int argc, char* argv[])
{

    int totalArgStrLen = getAllArgumentTotalStrLen(argc, argv);

    char* argString = (char*)malloc( sizeof(char) * totalArgStrLen );

    memset(argString, '\0', (sizeof(char) * totalArgStrLen));


    copyArgToSingleString(argc, argv, argString);

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


static int copyArgToSingleString(int argc, char* argv[], char* dest)
{
    int i = 0;
    
    for(i; i < argc; i++)
    {
        memcpy(dest, argv[i], sizeof(char) * strlen(argv[i]));
    }
}