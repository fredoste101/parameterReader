%{
    #include <parser.h>
    #include <parameterList.h>
%}

%option prefix="paramReader_"

%%

-[a-zA-Z]+                      {
                                    paramReader_lval = malloc(sizeof(strlen(paramReader_text)) + 1);
                                    memcpy(paramReader_lval, paramReader_text, strlen(paramReader_text));
                                    paramReader_lval[strlen(paramReader_text)] = '\0';
                                    return SHORT_OPT;
                                };

--                              return LONG_OPT_START;

[a-zA-Z0-9][a-zA-Z0-9\_\-\.]*  {
                                    paramReader_lval = malloc(sizeof(strlen(paramReader_text)) + 1);
                                    memcpy(paramReader_lval, paramReader_text, strlen(paramReader_text));
                                    paramReader_lval[strlen(paramReader_text)] = '\0';
                                    return PARAMETER_TOKEN;
                                };

                                

[ \t\n\r]+                      {
                                    paramReader_lval = malloc(sizeof(strlen(paramReader_text)) + 1);
                                    memcpy(paramReader_lval, paramReader_text, strlen(paramReader_text));
                                    paramReader_lval[strlen(paramReader_text)] = '\0';
                                    return WHITESPACECHARS;
                                };

=                               return EQUAL;


\\[a-zA-Z\"]                    {
                                    paramReader_lval = malloc(sizeof(strlen(paramReader_text)) + 1);
                                    memcpy(paramReader_lval, paramReader_text, strlen(paramReader_text));
                                    paramReader_lval[strlen(paramReader_text)] = '\0';
                                    return ESCAPE_SEQ; 
                                };

\"                              return DOUBLE_QUOTATION;
.                               {return -1;};

%%

int paramReader_wrap(void)
{
    return 1;
}