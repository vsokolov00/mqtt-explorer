
/**
 * @file        options.h
 * Case:        VUT, FIT, ICP, project                              <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz            <br>
 * Date:        summer semester 2021                                <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0            <br>
 * @brief       Declaration of command line option flags, option structure with and a command 
 *              line arguments parsing function.
 **/

#pragma once

#include <iostream>
#include "getopt.h"
#include "log.h"

/// flags specifying each specific device type
const unsigned THERMOMETERS_FLAG{0b1};
const unsigned HYGROMETERS_FLAG{0b10};
const unsigned WATTMETERS_FLAG{0b100};
const unsigned MOVE_FLAG{0b1000};
const unsigned LIGHTS_FLAG{0b10000};
const unsigned CAMERAS_FLAG{0b100000};
const unsigned RELAYS_FLAG{0b1000000};
const unsigned VALVES_FLAG{0b10000000};
const unsigned THERMOSTAT_FLAG{0b10000000};
const unsigned LOCKS_FLAG{0b100000000};

/**
 * @brief Used for parsing the command line arguments with default values for configuraton file and server address,
 *        the device flags are constructed by the @see parse_arguments function, defaultly all devices are set to run.
 **/
struct Options
{
    unsigned device_flags = 0xFFFFFFFF;                          ///< determines which devices are run, all by default
    std::string filename = "config.json";                        ///< the file name of a devices configuration file
    std::string server_addres = "tcp://localhost:1883";          ///< the address of a mqtt broker
};

/**
 * @brief Parses the command line arguments.
 * @param argc number of argunets including the name of the program.
 * @param options [out] the parsed options retrieved by parsing the command line arguments.
 */
void parse_arguments(int argc, char **argv, Options &options);
