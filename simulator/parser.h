
#pragma once

#include "json/json-forwards.h"
#include "json/json.h"
#include "devices.h"
#include "mqtt/async_client.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Message
{
    public:
        std::string topic;
        std::string id;
        std::string state;
};

class Parser
{
    private:
        Json::CharReader *_reader;

        bool read_file_content(std::string file_name, std::string &content);
        void parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers);
        void parse_hygrometers(Json::Value &root, std::vector<Hygrometer> &hygrometers);
        void parse_wattmeters(Json::Value &root, std::vector<Wattmeter> &wattmeters);
        void parse_move_sensors(Json::Value &root, std::vector<MoveSensor> &move_sensors);
        void parse_lights(Json::Value &root, std::vector<Light> &lights);

    public:
        Parser();
        ~Parser();

        bool parse_file(std::string file_name, Devices &devices);
        bool parse_message(mqtt::const_message_ptr recieved_message, Message &parsed_message);
};
