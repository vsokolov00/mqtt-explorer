
/**
 * @file        light.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a class representing a Light device.
 **/

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

#include "base_device.h"

/**
 * @brief Represents a ligh device, which has defined states by the configuration file. The states are switched 
 *        localy (i.e. by the simulator) or by a recieved message.
 **/
class Light : public RecievingAndPublishingDevice
{
    private:
        int _state = -1;                    ///< index of a current state pointing to @see _states
        std::vector<std::string> _states;   ///< known states of a light device
    
    public:
        Light(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        Light(const Light &light) = default;

        /**
         * @brief Adds a new state to the ligh.
         * @param state the added state.
         **/
        void add_state(std::string state);

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);

        /**
         * @brief Overrides the basic behaviour of message arrived function to represent a light. The function
         *        uses the defined states of the light. The arrived message can be accepted, if it represent 
         *        some of the light states and the state of the light is changed or stays the same base on 
         *        the current state.
         * @param See the derived classes.
         **/
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};
