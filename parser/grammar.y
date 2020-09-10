%{
    //Prologue

    #include <stdio.h>

    #include <parameterListParserApi.h>


    extern int yylex();
    void yyerror (char const *s);

    extern inputParameterList list;
%}

//Declarations 

%define api.value.type {char *}

%token SHORT_OPT
%token LONG_OPT_START
%token PARAMETER_TOKEN
%token CHAR
%token WHITESPACECHAR
%token EQUAL
%token DOUBLE_QUOTATION
%token TEST

%start parameterList

%%
    //Rules

    parameterList : 
        parameter |
        parameterList whiteSpacing parameter;
        

    parameter : 
        SHORT_OPT           
        {
            handleShortOption(&list, $1);
            free($1);
        }                                                       | 

        longOpt             
        {
            handleLongOption(&list, $1);
            free($1);
        }                                                       | 

        longOptWithArg                                          |

        arg                 
        {
            handleArgument(&list, $1);
            free($1);
        }                                                       | 

        %empty                                                  ;


    longOpt : LONG_OPT_START PARAMETER_TOKEN 
    {
        $$ = $2;
    };


    longOptWithArg : 
        LONG_OPT_START PARAMETER_TOKEN EQUAL arg 
        {
            handleLongOptionWithArg(&list, $2, $4); 
            free($2); 
            free($4);
        };


    arg : 
        DOUBLE_QUOTATION string DOUBLE_QUOTATION  | 
        PARAMETER_TOKEN {$$ = $1;};


    string : 
        string PARAMETER_TOKEN  | 
        string CHAR             |  
        string whiteSpacing     | 
        %empty;


    whiteSpacing : 
        WHITESPACECHAR              | 
        whiteSpacing WHITESPACECHAR ;

%%

    //Epilogue



void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}
