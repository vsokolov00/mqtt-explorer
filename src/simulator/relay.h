
//================================================================================================
// File:        relay.h
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Declaration of a class representing a Relay device.
//================================================================================================

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
 * @class Represents a relay device, which has defined states by the configuration file. It changes its state
 *        only by recieving a message with known state (i.e. added with @see add_state).
 **/
class Relay : public RecievingDevice
{
    private:
        std::string _state = "";
        std::vector<std::string> _states;
    
    public:
        Relay(std::string topic, std::string name, std::string id, std::string recv_topic);
        Relay(const Relay &relay) = default;

        /**
         * @brief Adds a new state to the relay.
         * @param state the added state.
         **/
        void add_state(std::string state);

        /**
         * @brief Overrides the basic behaviour of message arrived function to represent a relay. The function
         *        uses the defined states of the relay. The arrived message can be accepted, if it represent 
         *        some of the relay states and the state of the relay is changed or stays the same base on 
         *        the current state.
         * @param See the derived classes.
         **/
        void on_message_arrived(std::string state, Client &client, std::mutex &mutex) override;
};