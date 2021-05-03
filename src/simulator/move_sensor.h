
//================================================================================================
// File:        move_sensor.h
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Declaration of a class representing a MoveSensor device.
//================================================================================================

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>

#include "base_device.h"

/**
 * @class Represents a move sensor device, which has period used as minumal period from the based class and maximum period of
 *        change which is published. A move sensor can also have a field of view where the movement is detected.
 **/
class MoveSensor : PublishingDevice
{
    private:
        int _max_period;
        int _horizontal_FOV = 0;
        int _vertical_FOV = 0;

    public:
        MoveSensor(std::string topic, std::string name, int min_period, int max_period, 
                    int horizontal_FOV, int vertical_FOV);

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
