%{
    #include <parser.h>
%}


%%

-[a-zA-Z]+                      {
                                    yylval = malloc(sizeof(strlen(yytext)));
                                    memcpy(yylval, yytext, strlen(yytext));
                                    yylval[strlen(yytext)] = '\0';
                                    return SHORT_OPT;
                                };

--                              return LONG_OPT_START;

[a-zA-Z0-9][a-zA-Z0-9\_\-\.]*  {
                                    yylval = malloc(sizeof(strlen(yytext)));
                                    memcpy(yylval, yytext, strlen(yytext));
                                    yylval[strlen(yytext)] = '\0';
                                    return PARAMETER_TOKEN;
                                };

                                

[ \t\n\r]+                      {
                                    yylval = malloc(sizeof(strlen(yytext)));
                                    memcpy(yylval, yytext, strlen(yytext));
                                    yylval[strlen(yytext)] = '\0';
                                    return WHITESPACECHARS;
                                };

=                               return EQUAL;


\\[a-zA-Z\"]                    {
                                    yylval = malloc(sizeof(strlen(yytext)));
                                    memcpy(yylval, yytext, strlen(yytext));
                                    yylval[strlen(yytext)] = '\0';
                                    return ESCAPE_SEQ; 
                                };

\"                              return DOUBLE_QUOTATION;
.                               return -1;

%%

int yywrap(void)
{
    return 1;
}