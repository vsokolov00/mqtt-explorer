
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
 * @class Represent a lock device, which is only recieving and has states, which are changed by the recieved message.
 **/
class Lock : public RecievingDevice
{
    private:
        std::string _state = "";
        std::vector<std::string> _states;
    
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