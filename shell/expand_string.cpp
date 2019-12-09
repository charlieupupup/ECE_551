#include <map>
#include <string>
#include <cctype>
#include <iostream>

#include "expand_string.hpp"

std::string expand_string(std::string input, std::map<std::string, std::string> var)
{
    std::string result;
    std::string key_tmp;
    std::string val_tmp;
    for (unsigned long it = 0; it < input.length(); ++it)
    {
        if (input[it] == '$')
        {
            
            
            if (it == input.length() - 1)
            {
                std::cout << "error : $ cannot end command line" << std::endl;
            }
            it++;
            while (it < input.length() && (isalnum(input[it]) || input[it] == '_'))
            {

                key_tmp += input[it];
                it++;
            }
            
            if (input[it] == '$' && it == input.length() - 1)
            {
                std::cout << "error : $ cannot end command line" << std::endl;
                result.clear();
                return result;
            }

            if (var.find(key_tmp) != var.end())
            {
                val_tmp = var[key_tmp];
            }

            if (val_tmp.empty())
            {
                std::cout << "error: no variable key set as " << key_tmp << std::endl;
                result.clear();
                return result;
            }
        }

        if (val_tmp.empty())
        {
            result += input[it];
        }
        if (!val_tmp.empty())
        {
            result += val_tmp;
            result += input[it];
            key_tmp.clear();
            val_tmp.clear();
        }
    }
    return result;
}