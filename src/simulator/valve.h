
/**
 * @file        valve.h
 * Case:        VUT, FIT, ICP, project                              <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz            <br>
 * Date:        summer semester 2021                                <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0            <br>
 * @brief       Declaration of a class representing a Valve device.
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
 * @brief Represents a valve device, which has defined states by the configuration file. The states can be changed
 *        either localy or by recieving a message. 
 **/
class Valve : public RecievingAndPublishingDevice
{
    private:
        int _state = -1;                    ///< index of a current state pointing to @see _states
        std::vector<std::string> _states;   ///< known states by a valve device
    
    public:
        Valve(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        Valve(const Valve &valve) = default;

        /**
         * @brief Adds a new state to a valve device.
         * @param state The newly added state.
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
         * @brief Overrides the basic behaviour of message arrived function to represent a valve. The function
         *        uses the defined states of the valve. The arrived message can be accepted, if it represent 
         *        some of the valve states and the state of the valve is changed or stays the same base on 
         *        the current state.
         * @param See the derived classes.
         **/
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};
