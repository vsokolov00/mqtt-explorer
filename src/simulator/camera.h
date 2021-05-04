
/**
 * @file        camera.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a class representing a camera device.
 **/

#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iterator>

#include "base_device.h"

/**
 * @brief Represents a camera publishing device, which used period from the base class as minimum period and defines
 *        max period and list of published images.
 **/
class Camera : PublishingDevice
{
    private:
        int _max_period;                    ///< maximum period
        std::vector<std::string> _images;   ///< images, which are published by a camera
    
    public:
        Camera(std::string topic, std::string name, int min_period, int max_period);

        /**
         * @brief Adds an image to the list of published images.
         * @param image a path to a file containing the image.
         **/
        void add_image(std::string image);

        /**
         * @brief Runs the device.
         * @param client the client, which the device uses to publish.
         * @param run the device runs until the variable is true. Can be changed by another thread.
         * @param mutex a mutex used for sinchronization of operation on the client, which is shared between mutiple devices.
         * @param future a future on which the device passively waits, but can be woken up by another thread.
         **/
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
