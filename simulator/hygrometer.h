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

class Hygrometer : Device
{
    public:
        float min_step;
        float max_step;
        float humidity;
    
    Hygrometer(std::string topic, std::string name, std::string location, int period, float min_step, 
                float max_step, float humidity);

    void run_hygrometer(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);

    static void test(int a);
};

void func(int a);
