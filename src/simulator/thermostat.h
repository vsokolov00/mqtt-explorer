
/**
 * @file        thermostat.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a class representing a Thermostat device.
 **/

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"

/**
 * @brief Represents a thermostat device, which has minimum period as the period from the base class, a maximum period,
 *        a set point which can be changeg via recieved message, the maximum temprature change in one period and,
 *        the stating and current temperature with a specific unit and a direction of a temperature change.
 **/
class Thermostat : public RecievingAndPublishingDevice
{
    private:
        int _max_period;            ///< maximum period of a thermostat device
        float _set_point;           ///< current position of the setpoint
        float _temp_change;         ///< maximal temperature change per period
        float _temp;                ///< current temperature
        const std::string _unit;    ///< unit of measurement of a thermostat device
        bool _direction;            ///< direction of a temperature change

    public:
        Thermostat(std::string topic, std::string name, std::string id, std::string recv_topic, int min_period, int max_period,
                   float set_point, float temp_change, float temp, std::string unit);
        Thermostat(const Thermostat &thermostat) = default;

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);

        /**
         * @brief Overrides the basic behaviour of message arrived function to represent a thermostat. The function
         *        reacts to a change of the setpoint, which can result in the direction of the temperature.
         * @param See the derived classes.
         **/
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};
