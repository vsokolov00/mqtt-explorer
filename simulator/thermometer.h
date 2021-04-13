#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>

#include "main.h"
#include "mqtt/client.h"

class Thermometer
{
    public:
        std::string topic;
        std::string name;
        std::string location;
        int max;
        int min;
        float average;
        float deviation;
        int period;
    
    Thermometer(std::string topic, std::string name, std::string location, int max, int min, float average, float deviation, int period);

    void run_thermometer(mqtt::client &client, thred_control_t &control, std::future<void> future);
};
