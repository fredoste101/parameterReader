#include <parameterList.h>

void handleShortOption(inputParameterList* list, char* value);

void handleLongOption(inputParameterList* list, char* opt);

void handleLongOptionWithArg(inputParameterList* list, char* opt, char* arg);

void handleArgument(inputParameterList* list, char* arg);