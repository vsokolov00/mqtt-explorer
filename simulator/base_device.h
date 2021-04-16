
#pragma once

#include <thread>
#include <string>

#include "mqtt/client.h"

class Device
{
    protected:
        std::string _topic;
        std::string _name;
        int _period;

    public:
        Device(std::string topic, std::string name, int period);

        void virtual run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future) = 0;
};
