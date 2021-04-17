#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class MoveSensor : PublishingDevice
{
    private:
        int _max_period;
        int _horizontal_FOV = 0;
        int _vertical_FOV = 0;
        std::string _type;

    public:
        MoveSensor(std::string topic, std::string name, int min_period, int max_period, 
                    int horizontal_FOV, int vertical_FOV, std::string type);

        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
