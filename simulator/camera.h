
#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iterator>

#include "base_device.h"
#include "mqtt/client.h"

class Camera : PublishingDevice
{
    private:
        int _max_period;
        std::vector<std::string> _images;
    
    public:
        Camera(std::string topic, std::string name, int min_period, int max_period);

        void add_image(std::string image);
        void run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future);
};
