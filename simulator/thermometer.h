#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "json/json-forwards.h"
#include "json/json.h"
#include "base_device.h"
#include "mqtt/client.h"

class Thermometer : Device
{
    public:
        float min_temp;
        float max_temp;
        float min_step;
        float max_step;
        float temp;
        std::string unit;
    
    Thermometer(std::string topic, std::string name, std::string location, int period, float min_temp, float max_temp, 
                float min_step, float max_step, float temp, std::string unit);

    void run_thermometer(mqtt::client &client, const bool &run, std::mutex &mutex, 
                         std::future<void> future);
};

