
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

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};
