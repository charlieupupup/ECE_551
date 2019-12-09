#include <unistd.h>
#include <limits.h>

#include <string>
#include <vector>
#include <iostream>

#include "changedir.hpp"


void changedir(std::vector<std::string> input)
{

    if (input.size() == 2)
    {
        int cd = chdir(input[1].c_str());

        if (cd == -1)
        {
            perror("fail to change directory");
        }
    }

}