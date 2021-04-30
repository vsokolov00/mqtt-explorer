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

/**
 * @class Represents a thermometer device, which have minimum and maximum temperature with minimum and maximum
 *        change in one period, starting temperature and a unit of a the temperature.
 **/
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

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};

