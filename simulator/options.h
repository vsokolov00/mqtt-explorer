
#pragma once

#include <iostream>
#include "getopt.h"
#include "log.h"

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
 * @struct Used for parsing the command line arguments with default values for configuraton file and server address,
 *         the device flags are constructed by the @see parse_arguments function
 **/
struct Options
{
    unsigned device_flags;
    std::string filename = "config.json";
    std::string server_addres = "tcp://localhost:1883";
};

/**
 * @brief Parses the command line arguments.
 * @param argc number of argunets including the name of the program.
 * @param options [out] the parsed options retrieved by parsing the command line arguments.
 */
void parse_arguments(int argc, char **argv, Options &options);
