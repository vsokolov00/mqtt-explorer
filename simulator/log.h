
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
