
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
    char* argString = concatArgsToSingleString(argc-1, &argv[1]);

    //Set this string to be read by the lexer/scanner (yylex) whilst parsing (yyparse)
    //yy_scan_buffer(argString, strlen(argString) + 1);
    paramReader__scan_string(argString);

    int parseOk = paramReader_parse(listP);

    free(argString);

    return parseOk;
}


static char* concatArgsToSingleString(int argc, char* argv[])
{

    int totalArgStrLen = getAllArgumentTotalStrLen(argc, argv);

    char* argString = (char*)malloc( sizeof(char) * totalArgStrLen + 1 + (sizeof(char) * argc));

    memset(argString, '\0', (sizeof(char) * totalArgStrLen + 1));


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
    unsigned int length = 0;

    for(i; i < argc; i++)
    {
        memcpy(&dest[length], argv[i], sizeof(char) * strlen(argv[i]));
        
        length += strlen(argv[i]) + 1;
        dest[length - 1] = ' ';
    }

    dest[length - 1] = '\0';
}