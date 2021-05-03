
//================================================================================================
// File:        camera.h
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Declaration of a class representing a Hygrometer device.
//================================================================================================

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"

/**
 * @class Represents a hygrometer device, which has minimum and maximum humidity change and a starting humidity.
 **/
class Hygrometer : PublishingDevice
{
    private:
        float _min_step;
        float _max_step;
        float _humidity;
    
    public:
        Hygrometer(std::string topic, std::string name, int period, float min_step, float max_step, float humidity);
        
        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
