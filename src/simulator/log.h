
//================================================================================================
// File:        log.h
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Declaration of a Log class.
//================================================================================================

#pragma once

#include <iostream>

/**
 * @class This class is used for logging messages to STDOUT, logs to STDERR if verbose is true and warning and errors
 *        to STDERR.
 **/
class Log
{
    public:
        static bool verbose;

        static void message(const std::string &message);
        static void log(const std::string &message);
        static void warning(const std::string &message);
        static void error(const std::string &message);
        static void help_message(bool cerr);
};
