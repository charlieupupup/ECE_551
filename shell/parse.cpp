#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

#include "parse.hpp"
#include "parse_normal.hpp"
#include "parse_set.hpp"
#include "changedir.hpp"
#include "expand.hpp"

std::vector<std::string> parse(std::string input, std::map<std::string, std::string> &var)
{
    std::vector<std::string> parse_result;
    parse_result = parse_normal(input, var);
    if (parse_result[0].compare("set") == 0)
    {
        parse_result = parse_set(input);
        parse_result = expand(parse_result, var);
        if (!parse_result.empty())
        {

            var[parse_result[1]] = parse_result[2];
        }

        parse_result.clear();
    }
    if (parse_result[0].compare("export") == 0)
    {
        if (parse_result.size() == 1)
        {
            std::cout << "too few arg " << std::endl;
            parse_result.clear();
        }

        if (parse_result.size() > 2)
        {
            std::cout << "too much arg " << std::endl;
            parse_result.clear();
        }

        if (parse_result.size() == 2)
        {
            if (var.find(parse_result[1]) != var.end())
            {
                setenv(parse_result[1].c_str(), var[parse_result[1]].c_str(), 1);

                parse_result.clear();
            }

            if (var.find(parse_result[1]) == var.end())
            {
                std::cout << "error: no such key" << std::endl;
                parse_result.clear();
            }
        }
        parse_result.clear();
    }
    if (parse_result[0].compare("rev") == 0)
    {
        if (parse_result.size() == 1)
        {
            std::cout << "error : too less argument" << std::endl;
            parse_result.clear();
        }

        if (parse_result.size() > 2)
        {
            std::cout << "error : only accept 1 var each time" << std::endl;
            parse_result.clear();
        }
        if (var.find(parse_result[1]) != var.end())
        {
            std::string &s = var[parse_result[1]];
            std::reverse(s.begin(), s.end());
            parse_result.clear();
        }

        if (var.find(parse_result[1]) == var.end())
        {
            std::cout << "error: no such key" << std::endl;
        }

        parse_result.clear();
    }
    if (parse_result[0].compare("cd") == 0)
    {
        changedir(parse_result);
        parse_result.clear();
    }
    return parse_result;
}
