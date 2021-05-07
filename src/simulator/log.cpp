
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
    stream << "run as: ./simulator [options ...]" << std::endl;
    stream << "Options:" << std::endl;
    stream << "   --help or -h:             Display this help/usage message to STDOUT." << std::endl;
    stream << "   --file or -f <file name>: JSON file from which application configuration is loaded, default file is 'config.json'." << std::endl;
    stream << "   --server or -s:           MQTT server address, default address is 'tcp://localhost:1883'." << std::endl;
    stream << "   --verbose or -v:          Display log messages." << std::endl;
    stream << "   --apart or -a:            If specified before all other options below, devices will be excluded from the running list, rather then included." << std::endl;
    stream << "   --cameras or -c:          Include or exclude cameras." << std::endl;
    stream << "   --hygrometers or -g:      Include or exclude hygrometers." << std::endl;
    stream << "   --lights or -l:           Include or exclude lights." << std::endl;
    stream << "   --locks or -k:            Include or exclude locks." << std::endl;
    stream << "   --move or -m:             Include or exclude move sensors." << std::endl;
    stream << "   --relays or -r:           Include or exclude relays." << std::endl;
    stream << "   --thermometers or -t:     Include or exclude thermometers." << std::endl;
    stream << "   --thermostats or -e:      Include or exclude thermostats." << std::endl;
    stream << "   --valves or -u:           Include or exclude valves." << std::endl;
    stream << "   --wattmeters or -w:       Include or exclude wattmeters." << std::endl;
}
