
/**
 * @file        main.h
 * Case:        VUT, FIT, ICP, project                                      <br>
 * Author:      Vladislav Sokolovskii, xsokol15@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                                        <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0                    <br>
 * @brief       Command line argumetnts parsing function declaration.
 **/

#pragma once
#include "main_view.h"
#include "program.h"

#include <QApplication>

/**
 * @brief Parses the command line arguments.
 * @param argc number of arguments.
 * @param argv the arguments.
 **/
void parse_command_line_arguments(int argc, char **argv);
