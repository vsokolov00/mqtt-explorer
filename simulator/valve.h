
#pragma once 

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

#include "base_device.h"
#include "mqtt/client.h"

class Valve : public RecievingAndPublishingDevice
{
    private:
        int _state = -1;
        std::vector<std::string> _states;
    
    public:
        Valve(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        Valve(const Valve &valve) = default;

        void add_state(std::string state);
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};
