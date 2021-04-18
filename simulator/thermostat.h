
#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class Thermostat : public RecievingAndPublishingDevice
{
    private:
        int _max_period;
        float _set_point;
        float _temp_change;
        float _temp;
        const std::string _unit;
        bool _direction;

    public:
        Thermostat(std::string topic, std::string name, std::string id, std::string recv_topic, int min_period, int max_period,
                   float set_point, float temp_change, float temp, std::string unit);
        Thermostat(const Thermostat &thermostat) = default;

        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};
