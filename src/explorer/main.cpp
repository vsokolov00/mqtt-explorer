
/**
 * @file        main.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Starting point of the eplorer application, the main function.
 **/

#include "main.h"

int main(int argc, char *argv[])
{
    parse_command_line_arguments(argc, argv);

    QApplication application(argc, argv);

    Program program;
    try
    {
        program.init();
    }
    catch (std::bad_alloc &e)
    {
        (void)e;
        Log::error("Memory allocation failed.");
        program.~Program();
        exit(99);
    }
    program.start();

    int return_value = application.exec();

    program.quit();

    return return_value;
}

void parse_command_line_arguments(int argc, char **argv)
{
    std::string argument;
    bool file{false};

    if (argc == 2)
    {
        argument = std::string(argv[1]);
        if (argument == "-v" || argument == "--verbose")
        {
            Log::verbose = true;
        }
        else
        {
            Program::CONFIG_FILE = argument;
        }
    }
    else if (argc > 2)
    {
        argument = std::string(argv[1]);
        if (argument == "-v" || argument == "--verbose")
        {
            Log::verbose = true;
        }
        else
        {
            file = true;
            Program::CONFIG_FILE = argument;
        }

        argument = std::string(argv[2]);
        if (argument == "-v" || argument == "--verbose")
        {
            Log::verbose = true;
        }
        else if (!file)
        {
            Program::CONFIG_FILE = argument;
        }
    }
}
