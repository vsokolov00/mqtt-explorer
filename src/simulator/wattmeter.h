
//================================================================================================
// File:        wattmeter.cpp
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Implementation of constructors, destructors and functions of the Wattmeter class.
//================================================================================================

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"

/**
 * @class Represents a wattmeter device, which has a minimum and maximum values, minimum and maximum step per period,
 *        a current value with a unit.
 **/
class Wattmeter : PublishingDevice
{
    private:
        int _min_val;
        int _max_val;
        int _min_step;
        int _max_step;
        int _value;
        std::string _unit;

    public:
        Wattmeter(std::string topic, std::string name, int period, int min_val, 
                  int max_val, int min_step, int max_step, int value, std::string unit);

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
