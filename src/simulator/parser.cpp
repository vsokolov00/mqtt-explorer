
/**
 * @file        parser.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and functions of the Parser class
 *              used for parsing a device configuration file.
 **/

#include "parser.h"

Parser::Parser()
{
    _reader = Json::CharReaderBuilder().newCharReader();
}

Parser::~Parser()
{
    delete _reader;
}

bool Parser::read_file_content(std::string file_name, std::string &content)
{
    std::ifstream file(file_name, std::ifstream::in);
    if (file.fail())
    {
        Log::error("Opening configuration file '" + file_name + "' failed.");
        return true;
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    content = stream.str();

    file.close();
    return false;
}

bool Parser::parse_file(std::string file_name, Devices &devices)
{
    if (_reader == nullptr)
    {
        return true;
    }

    std::string content;

    if (read_file_content(file_name, content))
    {
        return true;
    }

    std::string errs;
    Json::Value root;

    if (!_reader->parse(content.c_str(), content.c_str() + content.size(), &root, &errs))
    {
        Log::error("JSON configuration file parsing failed with:\n" + errs);
        return true;
    }

    try
    {
        parse_thermometers(root["thermometers"], devices.thermometers);
        parse_hygrometers(root["hygrometers"], devices.hygrometers);
        parse_wattmeters(root["wattmeters"], devices.wattmeters);
        parse_move_sensors(root["move sensors"], devices.move_sensors);
        parse_lights(root["lights"], devices.lights);
        parse_cameras(root["cameras"], devices.cameras);
        parse_relays(root["relays"], devices.relays);
        parse_valves(root["valves"], devices.valves);
        parse_thermostats(root["thermostats"], devices.thermostats);
        parse_locks(root["locks"], devices.locks);
    }
    catch (const std::bad_alloc &e)
    {
        std::stringstream message;
        message << "Memory allocation of devices failed with '" << e.what() << "', some may strill run.";
        Log::warning(message.str());
    }
    catch (const Json::Exception &e)
    {
        std::stringstream message;
        message << "Parsing of devices faild with '" << e.what() << "' , some may strill run.";
        Log::warning(message.str());
    }

    return false;
}

void Parser::parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers)
{
    thermometers.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        thermometers.push_back(Thermometer(root[i]["topic"].asString(),
                                           root[i]["name"].asString(), 
                                           root[i]["period"].asInt(),
                                           root[i]["min_temp"].asFloat(), 
                                           root[i]["max_temp"].asFloat(), 
                                           root[i]["min_step"].asFloat(), 
                                           root[i]["max_step"].asFloat(),
                                           root[i]["temp"].asFloat(),
                                           root[i]["unit"].asString()
                                           ));
    }
}

void Parser::parse_hygrometers(Json::Value &root, std::vector<Hygrometer> &hygrometers)
{
    hygrometers.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        hygrometers.push_back(Hygrometer(root[i]["topic"].asString(),
                                         root[i]["name"].asString(), 
                                         root[i]["period"].asInt(),
                                         root[i]["min_step"].asFloat(), 
                                         root[i]["max_step"].asFloat(),
                                         root[i]["humidity"].asFloat()
                                         ));
    }
}


void Parser::parse_wattmeters(Json::Value &root, std::vector<Wattmeter> &wattmeters)
{
    wattmeters.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        wattmeters.push_back(Wattmeter(root[i]["topic"].asString(),
                                         root[i]["name"].asString(), 
                                         root[i]["period"].asInt(),
                                         root[i]["min_val"].asInt(),
                                         root[i]["max_val"].asInt(),
                                         root[i]["min_step"].asInt(),
                                         root[i]["max_step"].asInt(),
                                         root[i]["value"].asInt(),
                                         root[i]["unit"].asString()
                                         ));
    }
}

void Parser::parse_move_sensors(Json::Value &root, std::vector<MoveSensor> &move_sensors)
{
    move_sensors.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        move_sensors.push_back(MoveSensor(root[i]["topic"].asString(),
                                          root[i]["name"].asString(), 
                                          root[i]["min_period"].asInt(),
                                          root[i]["max_period"].asInt(),
                                          root[i]["horizontal_FOV"].asInt(),
                                          root[i]["vertical_FOV"].asInt()
                                         ));
    }
}

void Parser::parse_lights(Json::Value &root, std::vector<Light> &lights)
{
    lights.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        lights.push_back(Light(root[i]["topic"].asString(),
                               root[i]["name"].asString(), 
                               root[i]["period"].asInt(),
                               root[i]["id"].asString(),
                               root[i]["recieving topic"].asString()
                               ));
        
        if (!root[i]["states"] || !root[i]["states"].isArray())
        {
            Log::warning("States of a device '" + root[i]["name"].asString() + ", could not be parsed.");
            continue;
        }

        for (unsigned j = 0; root[i]["states"][j]; j++)
        {
            lights[i].add_state(root[i]["states"][j].asString());
        }
    }
}

void Parser::parse_cameras(Json::Value &root, std::vector<Camera> &cameras)
{
    cameras.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        cameras.push_back(Camera(root[i]["topic"].asString(),
                                 root[i]["name"].asString(), 
                                 root[i]["min_period"].asInt(),
                                 root[i]["max_period"].asInt()
                                 ));
        
        if (!root[i]["images"] || !root[i]["images"].isArray())
        {
            Log::warning("Imgaes of a camera '" + root[i]["name"].asString() + ", could not be parsed.");
            continue;
        }

        for (unsigned j = 0; root[i]["images"][j]; j++)
        {
            cameras[i].add_image(root[i]["images"][j].asString());
        }
    }
}

void Parser::parse_relays(Json::Value &root, std::vector<Relay> &relays)
{
    relays.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        relays.push_back(Relay(root[i]["answering topic"].asString(),
                               root[i]["name"].asString(), 
                               root[i]["id"].asString(),
                               root[i]["recieving topic"].asString()
                               ));
        
        if (!root[i]["states"] || !root[i]["states"].isArray())
        {
            Log::warning("States of a device '" + root[i]["name"].asString() + ", could not be parsed.");
            continue;
        }

        for (unsigned j = 0; root[i]["states"][j]; j++)
        {
            relays[i].add_state(root[i]["states"][j].asString());
        }
    }
}

void Parser::parse_valves(Json::Value &root, std::vector<Valve> &valves)
{
    valves.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        valves.push_back(Valve(root[i]["topic"].asString(),
                               root[i]["name"].asString(), 
                               root[i]["period"].asInt(), 
                               root[i]["id"].asString(),
                               root[i]["recieving topic"].asString()
                               ));
        
        if (!root[i]["states"] || !root[i]["states"].isArray())
        {
            Log::warning("States of a device '" + root[i]["name"].asString() + ", could not be parsed.");
            continue;
        }

        for (unsigned j = 0; root[i]["states"][j]; j++)
        {
            valves[i].add_state(root[i]["states"][j].asString());
        }
    }
}

void Parser::parse_thermostats(Json::Value &root, std::vector<Thermostat> &thermostats)
{
    thermostats.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        thermostats.push_back(Thermostat(root[i]["topic"].asString(),
                                         root[i]["name"].asString(), 
                                         root[i]["id"].asString(),
                                         root[i]["recieving topic"].asString(),
                                         root[i]["min_period"].asInt(),
                                         root[i]["max_period"].asInt(),
                                         root[i]["set_point"].asFloat(),
                                         root[i]["max_temp_change"].asFloat(),
                                         root[i]["starting_temp"].asFloat(),
                                         root[i]["unit"].asString()
                                         ));
    }
}

void Parser::parse_locks(Json::Value &root, std::vector<Lock> &locks)
{
    locks.reserve(root.size());
    for (unsigned i = 0; root[i]; i++)
    {
        locks.push_back(Lock(root[i]["answering topic"].asString(),
                             root[i]["name"].asString(), 
                             root[i]["id"].asString(),
                             root[i]["recieving topic"].asString()
                             ));
        
        if (!root[i]["states"] || !root[i]["states"].isArray())
        {
            Log::warning("States of a device '" + root[i]["name"].asString() + ", could not be parsed.");
            continue;
        }

        for (unsigned j = 0; root[i]["states"][j]; j++)
        {
            locks[i].add_state(root[i]["states"][j].asString());
        }
    }
}
