
#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

#include "base_device.h"
#include "mqtt/client.h"
#include "log.h"

class Relay : public RecievingDevice
{
    private:
        std::string _state = "";
        std::vector<std::string> _states;
    
    public:
        Relay(std::string topic, std::string name, std::string id, std::string recv_topic);
        Relay(const Relay &relay) = default;

        void add_state(std::string state);
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};