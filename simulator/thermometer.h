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

class Thermometer : PublishingDevice
{
    private:
        float _min_temp;
        float _max_temp;
        float _min_step;
        float _max_step;
        float _temp;
        const std::string _unit;
    
    public:
        Thermometer(std::string topic, std::string name, int period, float min_temp, float max_temp, 
                    float min_step, float max_step, float temp, std::string unit);

        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};

