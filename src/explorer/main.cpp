
/**
 * @file        main.cpp
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Starting point of the eplorer application, the main function.
 **/

#include "main_view.h"

#include "program.h"

#include <QApplication>

int main(int argc, char *argv[])
{
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
