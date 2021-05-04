
/**
 * @file        options.cpp
 * Case:        VUT, FIT, ICP, project                              <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz            <br>
 * Date:        summer semester 2021                                <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0            <br>
 * @brief       Implementation of function used for parsing command line arguments.
 **/

#include "options.h"

void parse_arguments(int argc, char **argv, Options &options)
{
    static struct option long_options[] =
    {
        {"help",         0, nullptr, 'h'},
        {"file",         0, nullptr, 'f'},
        {"server",       0, nullptr, 's'},
        {"verbose",      0, nullptr, 'v'},
        {"apart",        0, nullptr, 'a'},
        {"cameras",      0, nullptr, 'c'},
        {"hygrometers",  0, nullptr, 'g'},
        {"lights",       0, nullptr, 'l'},
        {"locks",        0, nullptr, 'k'},
        {"move",         0, nullptr, 'm'},
        {"relays",       0, nullptr, 'r'},
        {"thermometers", 0, nullptr, 't'},
        {"thermostats",  0, nullptr, 'e'},
        {"valves",       0, nullptr, 'u'},
        {"wattmeters",   0, nullptr, 'w'},
        {nullptr,        0, nullptr,  0 }

    };

    int c{-1};
    bool appart{false};
    bool not_appart{true};
    options.device_flags = 0xFFFFFFFF;
    unsigned flag{0};
    opterr = 0;

    while ((c = getopt_long(argc, argv, "hf:s:vacglkmrteuw", long_options, nullptr)) != -1)
    {
        switch (c)
        {
            case 'a':
                if (not_appart)
                {
                    appart = true;
                    not_appart = false;
                }
                else
                {
                    Log::warning("Option '-a' or '--apart' connot be used in this context.");
                }
                continue;
            
            case 'h':
                Log::help_message(false);
                exit(0);
            
            case 't':
                flag = THERMOMETERS_FLAG;
                break;

            case 'g':
                flag = HYGROMETERS_FLAG;
                break;
                
            case 'w':
                flag = WATTMETERS_FLAG;
                break;
                
            case 'm':
                flag = MOVE_FLAG;
                break;
                
            case 'l':
                flag = LOCKS_FLAG;
                break;
                
            case 'c':
                flag = CAMERAS_FLAG;
                break;
                
            case 'r':
                flag = RELAYS_FLAG;
                break;
                
            case 'u':
                flag = VALVES_FLAG;
                break;
                
            case 'e':
                flag = THERMOMETERS_FLAG;
                break;

            case 'k':
                flag = LOCKS_FLAG;
                break;

            case 'v':
                Log::verbose = true;
                continue;

            case 'f':
                options.filename.assign(optarg);
                continue;
            
            case 's':
                options.server_addres.assign(optarg);
                continue;

            default:
                Log::warning("unknow option '" + std::to_string(static_cast<char>(optopt)) + "'.");
                continue;
        }

        if (not_appart)
        {
            options.device_flags = 0;
            not_appart = false;
        }

        if (appart)
        {
            options.device_flags &= ~flag;
        }
        else
        {
            options.device_flags |= flag;
        }
    }    
}
