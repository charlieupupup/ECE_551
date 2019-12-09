#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>

#include "parse_normal.hpp"

std::vector<std::string> parse_normal(std::string input, std::map<std::string, std::string> var)
{
    std::vector<std::string> parse_result;
    std::string temp;
    bool quote = true;

    for (unsigned long i = 0; i < input.length(); i++)
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

            if (i == input.length())
            {
                temp += input[i];
                continue;
            }
        }

        if (input[i] == '"')
        {

            quote = !quote;
            continue;
        }
        if (input[i] == '<' && quote == true)
        {
            if (i == input.length() - 1)
            {
                std::cout << "error: syntax error near ending '<'" << std::endl;
                parse_result.clear();
                return parse_result;
            }
            if (i > 0 && input[i - 1] != ' ')
            {
                std::cout << "error: syntax error near '<'" << std::endl;
                parse_result.clear();
                return parse_result;
            }
            if (i > 0 && input[i - 1] == ' ')
            {
                parse_result.push_back("REDI_IN");
                i++;
                for (unsigned long j = i; j < input.length(); ++j)
                {
                    if (input[j] != ' ')
                    {
                        temp += input[j];
                        i = j;
                    }
                    if (input[j] == ' ' && temp.empty())
                    {
                        i = j;
                        continue;
                    }
                    if (input[j] == ' ' && !temp.empty())
                    {
                        i = j + 1;
                        break;
                    }
                }
                if (temp.empty())
                {
                    std::cout << "error: syntax error near '<'" << std::endl;
                    parse_result.clear();
                    return parse_result;
                }
                parse_result.push_back(temp);
                temp.clear();
            }
            if (i == input.length() - 1)
            {
                break;
            }
        }

        if (input[i] == '>' && quote == true)
        {
            if (i == input.length() - 1)
            {
                std::cout << "error: syntax error near ending '>'" << std::endl;
                parse_result.clear();
                return parse_result;
            }
            if (i > 0 && input[i - 1] != ' ')
            {
                std::cout << "error: syntax error near '>'" << std::endl;
                parse_result.clear();
                return parse_result;
            }
            if (i > 0 && input[i - 1] == ' ')
            {
                parse_result.push_back("REDI_OUT");
                i++;
                for (unsigned long j = i; j < input.length(); ++j)
                {
                    if (input[j] != ' ')
                    {
                        temp += input[j];
                        i = j;
                    }
                    if (input[j] == ' ' && temp.empty())
                    {
                        i = j;
                        continue;
                    }
                    if (input[j] == ' ' && !temp.empty())
                    {
                        i = j + 1;
                        break;
                    }
                }
                if (temp.empty())
                {
                    std::cout << "error: syntax error near '>'" << std::endl;
                    parse_result.clear();
                    return parse_result;
                }
                parse_result.push_back(temp);
                temp.clear();
                if (i == input.length() - 1)
                {
                    break;
                }
            }
        }

        if (input[i] == '2' && quote == true && i != input.length() - 1)
        {
            if (input[i + 1] == '>' && i + 1 == input.length() - 1)
            {
                std::cout << "error: syntax error near '2>'" << std::endl;
                parse_result.clear();
                break;
            }

            if (input[i + 1] == '>' && i + 1 != input.length() - 1)
            {
                if (i > 0 && input[i - 1] != ' ')
                {
                    std::cout << "error: syntax error near '2>'" << std::endl;
                    parse_result.clear();
                    break;
                }

                if (i > 0 && input[i - 1] == ' ')
                {
                    parse_result.push_back("REDI_ERR");
                    i += 2;
                    for (unsigned long j = i; j < input.length(); ++j)
                    {
                        if (input[j] != ' ')
                        {
                            temp += input[j];
                            i = j;
                        }
                        if (input[j] == ' ' && temp.empty())
                        {
                            i = j;
                            continue;
                        }
                        if (input[j] == ' ' && !temp.empty())
                        {
                            i = j + 1;
                            break;
                        }
                    }
                }
                if (temp.empty())
                {
                    std::cout << "error: syntax error near '2>'" << std::endl;
                    parse_result.clear();
                    break;
                }
                parse_result.push_back(temp);
                temp.clear();
                if (i == input.length() - 1)
                {
                    break;
                }
            }
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

    if (!temp.empty())
    {
        parse_result.push_back(temp);
    }

    if (!quote)
    {
        std::cout << "unclosed quotation mark! " << std::endl;
        parse_result.clear();
    }

    return parse_result;
}
