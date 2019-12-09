#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "expand_string.hpp"

std::vector<std::string> expand(std::vector<std::string> input, std::map<std::string, std::string> var)
{
    std::vector<std::string> result;
    std::string tmp;
    for(unsigned i = 0; i < input.size(); ++i)
    {
        tmp = expand_string(input[i], var);
        if(tmp.empty())
        {
            result.clear();
            return result;
        }
        

        result.push_back(tmp);
        tmp.clear();
    }
    return result;
}