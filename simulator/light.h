
#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class Light : Device
{
    private:
        float _min_step;
        float _max_step;
        float _humidity;
    
    public:
        Light(std::string topic, std::string name, int period, float min_step, float max_step, float humidity);

        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future) override;
};
