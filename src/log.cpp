
#include "log.h"

bool Log::verbose = true;

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
