
/**
 * @file        thermometer.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a class representing a Thermometer device.
 **/

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "../json/json/json.h"
#include "../json/json/json-forwards.h"
#include "base_device.h"

/**
 * @brief Represents a thermometer device, which have minimum and maximum temperature with minimum and maximum
 *        change in one period, starting temperature and a unit of a the temperature.
 **/
class Thermometer : PublishingDevice
{
    private:
        float _min_temp;            ///< minimal temperature of a thermometer device
        float _max_temp;            ///< maximal temperature of a thermometer device
        float _min_step;            ///< minimal temperature change per one period
        float _max_step;            ///< maximal temperature change per one period
        float _temp;                ///< current temperature of a thermometer device
        const std::string _unit;    ///< unit of measurement of a thermometer device
    
    public:
        Thermometer(std::string topic, std::string name, int period, float min_temp, float max_temp, 
                    float min_step, float max_step, float temp, std::string unit);

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};

