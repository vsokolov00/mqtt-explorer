#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"
#include "mqtt/client.h"

class MoveSensor : PublishingDevice
{
    private:
        int _max_period;
        int _horizontal_FOV = 0;
        int _vertical_FOV = 0;

    public:
        MoveSensor(std::string topic, std::string name, int min_period, int max_period, 
                    int horizontal_FOV, int vertical_FOV);

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
