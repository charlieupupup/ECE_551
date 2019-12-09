#include <limits.h>
#include <unistd.h>

#include <iostream>

#include "prompt.hpp"

void prompt(int status)
{
    char buffer[PATH_MAX];
    char *path = getcwd(buffer, sizeof(buffer));

    if (status == 0)
    {
        if (path)
        {
            std::cout << "ffosh:" << buffer << " $";
        }

        else
        {
            perror("error printing working directory");
        }
    }
}
