
#include "parser.h"

Parser::Parser(std::string file_name)
{

    _reader = Json::CharReaderBuilder().newCharReader();
    if (_reader == nullptr)
    {
        throw;
    }

    this->_file_name = file_name;
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

    return false;
}

bool Parser::parse_thermometers(Json::Value &root, std::vector<Thermometer> &thermometers)
{
    for (int i = 0; root[i]; i++)
    {
        thermometers.push_back(Thermometer(root[i]["topic"].asString(),
                                           root[i]["name"].asString(), 
                                           root[i]["location"].asString(), 
                                           root[i]["min_temp"].asFloat(), 
                                           root[i]["max_temp"].asFloat(), 
                                           root[i]["min_step"].asFloat(), 
                                           root[i]["max_step"].asFloat(),
                                           root[i]["temp"].asFloat(),
                                           root[i]["period"].asInt()));
    }

    return false;
}
