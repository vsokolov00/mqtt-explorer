
/**
 * @file        log.cpp
 * Case:        VUT, FIT, ICP, project                              <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz            <br>
 * Date:        summer semester 2021                                <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0            <br>
 * @brief       Implementation of static functions of the Log class
 **/

#include "log.h"

bool Log::verbose = false;

void Log::log(const std::string &message)
{
    if (Log::verbose)
    {   
        std::cerr << "LOG: " << message << std::endl;
    }
}

void Log::warning(const std::string &message)
{
    std::cerr << "WARNING: " << message << std::endl;
}

void Log::error(const std::string &message)
{
    std::cerr << "ERROR: " << message << std::endl;
}

void Log::message(const std::string &message)
{
    std::cout << message << std::endl;
}

void Log::help_message(bool cerr)
{
    std::ostream &stream = cerr ? std::cerr : std::cout;
    stream << "TODO" << std::endl;
}
