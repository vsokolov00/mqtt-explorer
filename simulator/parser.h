
#pragma once

#include "json/json-forwards.h"
#include "json/json.h"
#include "devices.h"
#include "mqtt/async_client.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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
        void parse_cameras(Json::Value &root, std::vector<Camera> &cameras);
        void parse_relays(Json::Value &root, std::vector<Relay> &relays);
        void parse_valves(Json::Value &root, std::vector<Valve> &valves);
        void parse_thermostats(Json::Value &root, std::vector<Thermostat> &thermostats);
        void parse_locks(Json::Value &root, std::vector<Lock> &locks);

    public:
        Parser();
        Parser(const Parser&) = delete;
        ~Parser();

        bool parse_file(std::string file_name, Devices &devices);
};
