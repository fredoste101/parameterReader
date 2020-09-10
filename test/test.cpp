#include <iostream>

#include "../parameterReader.h"


int main()
{
    std::string test1 = "-a --test --input=file -bcd";

    std::vector<inputParameter> result;

    result = argReader(test1);

    for(unsigned int i = 0; i < result.size(); i++)
    {
        std::cout << "TYPE:" << result[i].parameterType << std::endl 
                  << "Parameter:" << result[i].parameter << std::endl 
                  << "OptionArgument:" << result[i].optionArgument << std::endl << std::endl;
    }

    return 0;
}