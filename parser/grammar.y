%{
    //Prologue

    #include <stdio.h>

    #include <parameterListParserApi.h>


    extern int yylex();
    void yyerror (inputParameterList *listP, char const *s);


    static char* concatStrings(char* str1, char* str2);
%}

//Declarations 

%code requires {#include <parameterListParserApi.h>}
%parse-param {inputParameterList *listP}

%define api.value.type {char *}

%token SHORT_OPT
%token LONG_OPT_START
%token PARAMETER_TOKEN
%token WHITESPACECHARS
%token EQUAL
%token DOUBLE_QUOTATION
%token TEST
%token ESCAPE_SEQ

%start parameterList

%%
    //Rules

    parameterList : 
        parameter |
        parameterList WHITESPACECHARS parameter {free($2);};
        

    parameter : 
        SHORT_OPT           
        {
            handleShortOption(listP, $1);
            free($1);
        }                                                       | 

        longOpt                                                 |

        arg                                                     
        {
            handleArgument(listP, $1);
            free($1);  
        }                                                       | 

        %empty                                                  ;


    longOpt : 
        LONG_OPT_START PARAMETER_TOKEN 
        {
            handleLongOption(listP, $2);
            free($2);
        }                                                         | 
    
        LONG_OPT_START PARAMETER_TOKEN EQUAL arg 
        {
            handleLongOptionWithArg(listP, $2, $4); 
            free($2); 
            free($4);
        };
        


    arg : 
        DOUBLE_QUOTATION string DOUBLE_QUOTATION  
        {
            $$ = $2;
        }                                                           |

        PARAMETER_TOKEN 
        {
            $$ = $1;
        };


    string : 
        string PARAMETER_TOKEN  
        {
            if($1 == NULL)
            {
                $$ = $2;
            }
            else
            {
                $$ = concatStrings($1, $2);
                free($1);
                free($2);
            }
        };                                      |

        string WHITESPACECHARS   
        {
            if($1 == NULL)
            {
                $$ = $2;
            }
            else
            {
                $$ = concatStrings($1, $2);
                free($1);
                free($2);
            }
        };                                      |

        string ESCAPE_SEQ       
        {
            if($1 == NULL)
            {
                $$ = $2;
            }
            else
            {
                $$ = concatStrings($1, $2);
                free($1);
                free($2);
            }
        };                                      | 

        %empty {$$ = NULL;};


%%

    //Epilogue



void yyerror (inputParameterList *listP, char const *s)
{
    fprintf (stderr, "%s\n", s);
}


static char* concatStrings(char* str1, char* str2)
{
    size_t stringSize   = sizeof(char) * (strlen(str1) + strlen(str2) + 1);
    char* resultStr     = (char*)malloc(stringSize);
    
    memset(resultStr, '\0', stringSize);
    
    memcpy(resultStr, str1, strlen(str1));

    memcpy(&resultStr[strlen(str1)], str2, strlen(str2));

    return resultStr;
}
