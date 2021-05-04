
/**
 * @file        log.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a Log class.
 **/

#pragma once

#include <iostream>

/**
 * @brief This class is used for logging messages to STDOUT, logs to STDERR if verbose is true and warning and errors
 *        to STDERR.
 **/
class Log
{
    public:
        static bool verbose;    ///< when true @see log messages are printed, otherwise not.

        /**
         * @brief Prints a message to STDOUT.
         * @param message the printed message.
         **/
        static void message(const std::string &message);

        /**
         * @brief Prints a log message to STDERR.
         * @param message the printed message.
         **/
        static void log(const std::string &message);

        /**
         * @brief Prints a warning message to STDERR.
         * @param message the printed message.
         **/
        static void warning(const std::string &message);

        /**
         * @brief Prints an error message to STDERR.
         * @param message the printed message.
         **/
        static void error(const std::string &message);

        /**
         * @brief Prints a help message to STDOUT.
         * @param cerr if true prints to STDERR, otherwise to STDOUT
         **/
        static void help_message(bool cerr);
};
