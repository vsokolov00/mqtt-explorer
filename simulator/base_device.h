
#pragma once

#include <thread>
#include <string>

#include "mqtt/client.h"

class Device
{
    public:
        std::string topic;
        std::string name;
        int period;

        Device(std::string topic, std::string name, int period);

        void virtual run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future) = 0;
};
