
/**
 * @file        lock.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a class representing a Lock device.
 **/

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

#include "base_device.h"
#include "log.h"

/**
 * @brief Represent a lock device, which is only recieving messages and has states, which can be changed 
 *        by the recieved message, if the recieved messaged is understood (i.e. represents a state added 
 *        with @see add_state).
 **/
class Lock : public RecievingDevice
{
    private:
        std::string _state = "";            ///< current state of a lock device
        std::vector<std::string> _states;   ///< all known states of a lock device
    
    public:
        Lock(std::string topic, std::string name, std::string id, std::string recv_topic);
        Lock(const Lock &lock) = default;

        /**
         * @brief Adds a new state to the lock.
         * @param state the added state.
         **/
        void add_state(std::string state);

        /**
         * @brief Overrides the basic behaviour of message arrived function to represent a lock. The function
         *        uses the defined states of the lock. The arrived message can be accepted, if it represent 
         *        some of the lock states and the state of the lock is changed or stays the same based of 
         *        the current state.
         * @param See the derived classes.
         **/
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};