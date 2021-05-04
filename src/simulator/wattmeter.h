
/**
 * @file        wattmeter.cpp
 * Case:        VUT, FIT, ICP, project                              <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz            <br>
 * Date:        summer semester 2021                                <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0            <br>
 * @brief       Implementation of constructors, destructors and functions of the Wattmeter class.
 **/

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"

/**
 * @brief Represents a wattmeter device, which has a minimum and maximum values, minimum and maximum step per period,
 *        a current value with a unit.
 **/
class Wattmeter : PublishingDevice
{
    private:
        int _min_val;           ///< minimum value of a wattmeter device
        int _max_val;           ///< maximum value of a wattmeter device
        int _min_step;          ///< minimul value change per one period
        int _max_step;          ///< maximum value change per one period
        int _value;             ///< current value of a wattmeter device
        std::string _unit;      ///< unit of measurement of a wattmeter device

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
