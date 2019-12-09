#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include "parse_set.hpp"

std::vector<std::string> parse_set(std::string input)
{
    std::vector<std::string> parse_result;
    std::string temp;
    bool quote = true;
    
    for (unsigned long i = 0; i < input.length(); i++)
    {
        if (parse_result.size() == 2)
        {
            quote = true;
            if (input[i] == '\\')
            {

                if (i != input.length() - 1)
                {
                    if (input[i + 1] == '\\' || input[i + 1] == '"')
                    {
                        i++;
                        temp += input[i];
                        continue;
                    }

                    else
                    {
                        temp += input[i];
                        continue;
                    }
                }

                if (i == input.length() - 1)
                {
                    temp += input[i];
                    continue;
                }
            }

            if (input[i] == ' ')
            {
                if (temp.empty())
                {
                    continue;
                }
                if (!temp.empty())
                {
                    temp += input[i];
                    continue;
                }
            }

            temp += input[i];
        }

        if (parse_result.size() < 2)
        {
            if (input[i] == '\\')
            {

                if (i != input.length() - 1)
                {
                    if (input[i + 1] == '\\' || input[i + 1] == '"')
                    {
                        i++;
                        temp += input[i];
                        continue;
                    }

                    else
                    {
                        temp += input[i];
                        continue;
                    }
                }

                if (i == input.length() - 1)
                {
                    temp += input[i];
                    continue;
                }
            }

            if (input[i] == '"')
            {
                std::cout << i << " " << input[i] << std::endl;
                quote = !quote;
                continue;
            }

            if (input[i] == ' ' && quote == false)
            {
                temp += input[i];
                continue;
            }

            if (input[i] == ' ' && quote == true)
            {
                if (temp.empty())
                {
                    continue;
                }
                if (!temp.empty())
                {
                    parse_result.push_back(temp);
                    temp.clear();
                    continue;
                }
            }

            temp += input[i];
        }
    }

    if (!temp.empty())
    {
        parse_result.push_back(temp);
    }

    for (std::string::iterator it = parse_result[1].begin(); it != parse_result[1].end(); it++)
    {
        if (isalnum(*it) || *it == '_')
        {

            continue;
        }

        else
        {
            std::cout << "ilegal variable" << std::endl;
            parse_result.clear();
        }
    }

    return parse_result;
}
