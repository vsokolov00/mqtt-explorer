
#include "parser.h"

Parser::Parser(std::string file_name) : _file_name(file_name)
{
    _reader = Json::CharReaderBuilder().newCharReader();
}

Parser::~Parser()
{
    delete _reader;
}

bool Parser::read_file_content(std::string &content)
{
    std::ifstream file(_file_name, std::ifstream::in);
    if (file.fail())
    {
        std::cerr << "Opening configuration file failed." << std::endl;
        return true;
    }

    std::ostringstream stream;
    stream << file.rdbuf();
    content = stream.str();

    file.close();
    return false;
}

bool Parser::parse_file(Devices &devices)
{
    if (_reader == nullptr)
    {
        return true;
    }

    std::string content;

    if (read_file_content(content))
    {
        return true;
    }

    std::string errs;
    Json::Value root;

    if (!_reader->parse(content.c_str(), content.c_str() + content.size(), &root, &errs))
    {
        std::cerr << errs << std::endl;
        return true;
    }

    parse_thermometers(root["thermometers"], devices.thermometers);
    parse_hygrometers(root["hygrometers"], devices.hygrometers);
    parse_wattmeters(root["wattmeters"], devices.wattmeters);
    parse_move_sensors(root["move sensors"], devices.move_sensors);

    return false;
}

void Parser::parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers)
{
    for (int i = 0; root[i]; i++)
    {
        thermometers.push_back(Thermometer(root[i]["topic"].asString(),
                                           root[i]["name"].asString(), 
                                           root[i]["period"].asInt(),
                                           root[i]["min_temp"].asFloat(), 
                                           root[i]["max_temp"].asFloat(), 
                                           root[i]["min_step"].asFloat(), 
                                           root[i]["max_step"].asFloat(),
                                           root[i]["temp"].asFloat(),
                                           root[i]["unit"].asString()));
    }
}

void Parser::parse_hygrometers(Json::Value &root, std::vector<Hygrometer> &hygrometers)
{
    for (int i = 0; root[i]; i++)
    {
        hygrometers.push_back(Hygrometer(root[i]["topic"].asString(),
                                         root[i]["name"].asString(), 
                                         root[i]["period"].asInt(),
                                         root[i]["min_step"].asFloat(), 
                                         root[i]["max_step"].asFloat(),
                                         root[i]["humidity"].asFloat()));
    }
}


void Parser::parse_wattmeters(Json::Value &root, std::vector<Wattmeter> &wattmeters)
{
    for (int i = 0; root[i]; i++)
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
    for (int i = 0; root[i]; i++)
    {
        move_sensors.push_back(MoveSensor(root[i]["topic"].asString(),
                                          root[i]["name"].asString(), 
                                          root[i]["min_period"].asInt(),
                                          root[i]["max_period"].asInt(),
                                          root[i]["horizontal_FOV"].asInt(),
                                          root[i]["vertical_FOV"].asInt(),
                                          root[i]["type"].asString()
                                         ));
    }
}

