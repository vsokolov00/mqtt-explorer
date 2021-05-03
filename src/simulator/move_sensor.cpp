
//================================================================================================
// File:        move_sensor.cpp
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Implementation of constructors, destructors and functions of the MoveSensor class.
//================================================================================================

#include "move_sensor.h"

MoveSensor::MoveSensor(std::string topic, std::string name, int min_period, int max_period, 
                         int horizontal_FOV, int vertical_FOV)
            : PublishingDevice(topic, name, min_period), _max_period(max_period), _horizontal_FOV(horizontal_FOV), 
              _vertical_FOV(vertical_FOV) {}

void MoveSensor::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(_topic, _name);
    message->set_qos(1);
    
    auto period_generator = std::bind(std::uniform_int_distribution<int>(_period, _max_period), std::default_random_engine(time(nullptr)));
    period_generator();
    auto horizontal_generator = std::bind(std::uniform_int_distribution<int>(0, _horizontal_FOV), std::default_random_engine(time(nullptr)));
    horizontal_generator();
    auto vertical_generator = std::bind(std::uniform_int_distribution<int>(0, _vertical_FOV), std::default_random_engine(time(nullptr)));
    vertical_generator();

    std::string message_str;

    future.wait_for(std::chrono::seconds(period_generator()));
    while (run)
    {
        message_str = _name;
        if (_horizontal_FOV | _vertical_FOV)
        {
            message_str += ": move detected at x = " + std::to_string(horizontal_generator()) 
                        + ", y = " + std::to_string(vertical_generator());
        }
        else
        {
            message_str += ": move detected";
        }

        message->set_payload(message_str.c_str(), message_str.size());
        
        mutex.lock();
            client.publish(message);
        mutex.unlock();

        Log::log(message_str);     
        future.wait_for(std::chrono::seconds(period_generator()));
    }
}
