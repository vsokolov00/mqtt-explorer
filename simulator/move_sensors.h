#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class MoveSensors : Device
{
    public:
        int max_period;
        int vertical_FOV = 0;
        int horizontal_FOV = 0;

        MoveSensors(std::string topic, std::string name, int min_period, int max_period, int horizontal_FOV, int vertical_FOV);

        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future) override;
};
