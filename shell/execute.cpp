#include "execute.hpp"
#include "redirect.hpp"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include <string>
#include <cstring>
#include <vector>
int execute(std::vector<std::string> input)
{

    if (input.empty())
    {
        return EXIT_SUCCESS;
    }

    pid_t pid_child, wait;
    int status;

    pid_child = fork();
    if (pid_child == -1)
    {
        perror("uncessful fork");
        std::exit(EXIT_FAILURE);
    }
   

    //code executed by process child

    if (pid_child == 0)
    {
        //redirection

        int std_in = 0;
        int std_out = 1;
        int std_err = 2;

        redirect(input, std_in, std_out, std_err);

        dup2(std_in, 0);
        dup2(std_out, 1);
        dup2(std_err, 2);

        // allocate memory and set environment variable
        char **argv_new = new char *[input.size() + 1];
        for (size_t i = 0; i < input.size(); ++i)
        {
            argv_new[i] = const_cast<char *>(input[i].c_str());
        }
        argv_new[input.size()] = NULL;

        if (input[0].find('/') != std::string::npos)
        {

            execve(argv_new[0], argv_new, environ);
            close(std_in);
            close(std_out);
            close(std_err);

            // de-allocate

            input.clear();
            delete[] argv_new;
            perror("execute error");
            std::exit(EXIT_FAILURE);
        }

        if (input[0].find('/') == std::string::npos)
        {

            char *path = getenv("PATH");
            char *p_deli = strtok(path, ":");

            std::string cmd;

            while (p_deli)
            {
                cmd.assign(p_deli);

                if (cmd.back() != '/')
                {
                    cmd.push_back('/');
                }

                cmd.append(input[0]);

                argv_new[0] = const_cast<char *>(cmd.c_str());

                execve(argv_new[0], argv_new, environ);

                p_deli = strtok(NULL, ":");
            }

            delete[] argv_new;

            std::cout << "Command " << input[0] << " not found" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    //code executed by process parent
    if (pid_child > 0)
    {

        wait = waitpid(pid_child, &status, WUNTRACED | WCONTINUED);

        if (wait == -1)
        {
            perror("Waitpid mistake\n");
            return EXIT_FAILURE;
        }

        if (WIFEXITED(status))
        {

            if (WEXITSTATUS(status) == 0)
            {
                std::cout << "Program was successful" << std::endl;
            }
            else
            {
                std::cout << "Program failed with code " << WEXITSTATUS(status) << std::endl;
            }
        }

        if (WIFSIGNALED(status))
        {
            std::cout << "Terminated by signal " << WTERMSIG(status) << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
