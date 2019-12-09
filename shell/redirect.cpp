#include <iostream>
#include <string>
#include <vector>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "redirect.hpp"

void redirect(std::vector<std::string> &input, int &std_in, int &std_out, int &std_err)
{
    std::string s_in;
    std::string s_out;
    std::string s_err;

    for (unsigned long i = 0; i < input.size(); ++i)
    {
        if (input[i].compare("REDI_IN") == 0)
        {
            s_in = input[i + 1];
            input.erase(input.begin() + i);
            input.erase(input.begin() + i);
            continue;
        }
        if (input[i].compare("REDI_OUT") == 0)
        {
            s_out = input[i + 1];
            input.erase(input.begin() + i);
            input.erase(input.begin() + i);
            continue;
        }
        if (input[i].compare("REDI_ERR") == 0)
        {
            s_err = input[i + 1];
            input.erase(input.begin() + i);
            input.erase(input.begin() + i);
            continue;
        }
    }

    if (!s_in.empty())
    {
        int std_in_tmp = open(s_in.c_str(), O_RDONLY);
        if (std_in_tmp == -1)
        {
            std::cout << "error: unable to open file " << s_in << std::endl;
        }
        else
        {
            std_in = std_in_tmp;
        }
    }

    if (!s_out.empty())
    {
        int std_out_tmp = open(s_out.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        if (std_out_tmp == -1)
        {
            std::cout << "error: unable to open file" << s_out << std::endl;
        }
        else
        {
            std_out = std_out_tmp;
        }
    }

    if (!s_err.empty())
    {
        int std_err_tmp = open(s_err.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        if (std_err_tmp == -1)
        {
            std::cout << "error: unable to open file" << s_err << std::endl;
        }
        else
        {
            std_err = std_err_tmp;
        }
    }
}
