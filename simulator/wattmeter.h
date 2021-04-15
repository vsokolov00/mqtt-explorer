#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class Wattmeter : Device
{
    public:
        int min_val;
        int max_val;
        int min_step;
        int max_step;
        int value;
        std::string unit;

        Wattmeter(std::string topic, std::string name, int period, int min_val, 
                  int max_val, int min_step, int max_step, int value, std::string unit);

        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future) override;
};
