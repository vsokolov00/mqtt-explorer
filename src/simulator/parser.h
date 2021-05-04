
/**
 * @file        parser.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a Parser class.
 **/

#pragma once

#include "../json/json/json.h"
#include "../json/json/json-forwards.h"
#include "devices.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/**
 * @brief Parses a configuration file.
 **/
class Parser
{
    private:
        Json::CharReader *_reader;      ///< used for parsing JSON files.

        /**
         * @brief Opens a file and reads its conentent.
         * @param filename the path to a file to be read.
         * @param content [out] the read content of the specified file.
         **/
        bool read_file_content(std::string file_name, std::string &content);

        /**
         * @brief Retrieves all thermometer devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved thermometers.
         **/
        void parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers);

        /**
         * @brief Retrieves all hygrometer devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved hygrometers.
         **/
        void parse_hygrometers(Json::Value &root, std::vector<Hygrometer> &hygrometers);

        /**
         * @brief Retrieves all wattmeter devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved wattmeters.
         **/
        void parse_wattmeters(Json::Value &root, std::vector<Wattmeter> &wattmeters);

        /**
         * @brief Retrieves all move sensor devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved move sensors.
         **/
        void parse_move_sensors(Json::Value &root, std::vector<MoveSensor> &move_sensors);

        /**
         * @brief Retrieves all light devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved lights.
         **/
        void parse_lights(Json::Value &root, std::vector<Light> &lights);

        /**
         * @brief Retrieves all camera devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved cameras.
         **/
        void parse_cameras(Json::Value &root, std::vector<Camera> &cameras);

        /**
         * @brief Retrieves all relay devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved relays.
         **/
        void parse_relays(Json::Value &root, std::vector<Relay> &relays);

        /**
         * @brief Retrieves all valve devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved valves.
         **/
        void parse_valves(Json::Value &root, std::vector<Valve> &valves);

        /**
         * @brief Retrieves all thermostat devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved thermostats.
         **/
        void parse_thermostats(Json::Value &root, std::vector<Thermostat> &thermostats);

        /**
         * @brief Retrieves all lock devices from a give JSON value;
         * @param root the given JSON value.
         * @param thermometers [out] the retrieved locks.
         **/
        void parse_locks(Json::Value &root, std::vector<Lock> &locks);

    public:
        Parser();
        Parser(const Parser&) = delete;
        ~Parser();

        /**
         * @brief Parses a file with path given by a file name.
         * @param filename the file name (the path and name).
         * @param devices [out] the parsed devices.
         **/
        bool parse_file(std::string file_name, Devices &devices);
};
