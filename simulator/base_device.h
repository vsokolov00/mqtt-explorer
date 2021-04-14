
#pragma once

#include <string>

class Device
{
    public:
        std::string topic;
        std::string name;
        std::string location;
        int period;

        Device(std::string topic, std::string name, std::string location, int period);
};
