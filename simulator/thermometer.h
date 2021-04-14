#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "main.h"
#include "mqtt/client.h"

class Thermometer
{
    public:
        std::string topic;
        std::string name;
        std::string location;
        float min_temp;
        float max_temp;
        float min_step;
        float max_step;
        float temp;
        int period;
    
    Thermometer(std::string topic, std::string name, std::string location, float min_temp, float max_temp, float min_step, 
                float max_step, float temp, int period);

    void run_thermometer(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};

class ThermometerRunner
{
    private:
        bool _run = false;
        std::vector<Thermometer>& _thermometers;

        mqtt::client _client;
        std::mutex _mutex;
        std::vector<std::thread> _threads;
        std::vector<std::promise<void>> _promises;

    public:
        bool not_runable = false;

        ThermometerRunner(std::vector<Thermometer> &thermometers, const std::string &server_address);

        void run_thermometers();
        void stop_thermometers();
};
