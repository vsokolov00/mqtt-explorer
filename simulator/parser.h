
#pragma once

#include "json/json-forwards.h"
#include "json/json.h"
#include "devices.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Parser
{
    private:
        Json::CharReader *reader;
        std::string file_name;

        bool read_file_content(std::string &content);
        bool parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers);

    public:
        Parser(std::string file_name);
        ~Parser();

        bool parse_file(Devices &devices);
};
