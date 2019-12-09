#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "prompt.hpp"
#include "parse.hpp"
#include "expand.hpp"
#include "execute.hpp"

int main(void)
{
    //store variable
    std::map<std::string, std::string> var; 
    //store input string
    std::string input;
    //store input parse 
    std::vector<std::string> input_parse;
    //store execute result
    int execute_result;
    while (true)
    {
        //output: prompt
        prompt(0);

        //input: command line
        if (!std::getline(std::cin, input) || input.compare("exit") == 0)
        {
            break;
        }

        //parse: input
        input_parse = parse(input, var);

        //expand: input
        input_parse = expand(input_parse, var);

        //execute
        execute_result = execute(input_parse);
        if(execute_result == 0)
        {
            continue;
        }
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}
