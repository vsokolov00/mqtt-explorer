
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
        Json::CharReader *_reader;
        std::string _file_name;

        bool read_file_content(std::string &content);
        void parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers);
        void parse_hygrometers(Json::Value &root, std::vector<Hygrometer> &hygrometers);
        void parse_wattmeters(Json::Value &root, std::vector<Wattmeter> &wattmeters);
        void parse_move_sensors(Json::Value &root, std::vector<MoveSensor> &move_sensors);

    public:
        Parser(std::string file_name);
        ~Parser();

        bool parse_file(Devices &devices);
};
