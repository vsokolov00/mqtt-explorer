
#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class Relay : public RecievingDevice
{
    private:
        int _state = -1;
        std::vector<std::string> _states;
    
    public:
        Relay(std::string topic, std::string name, int period, std::string id, std::string recv_topic);

        void add_state(std::string state);
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};