
/**
 * @file        hygrometer.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and functions of the Hygrometer class.
 **/

#include "hygrometer.h"

Hygrometer::Hygrometer(std::string topic, std::string name, int period, float min_step, float max_step, float humidity)
            : PublishingDevice(topic, name, period), _min_step(min_step), _max_step(max_step) 
{
    _humidity = humidity >= 0.0f && humidity <= 100.f ? humidity : 50.0f;
}


void Hygrometer::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(_topic, _name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(_min_step * 1000, _max_step * 1000), 
                                    std::default_random_engine(time(nullptr)));
    step_generator();
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine(time(nullptr)));
    up_down_generator();

    float step;
    bool up_down;
    std::string message_str;

    future.wait_for(std::chrono::seconds(_period));
    while (run)
    {
        step = step_generator() / 1000.0f;
        up_down = up_down_generator();

        if (up_down)
        {
            _humidity = _humidity + step > 100.f ? 100.0f : _humidity + step;
        }
        else
        {
            _humidity = _humidity - step < 0.0f ? 0.0f : _humidity - step;
        }

        message_str = std::to_string(_humidity);
        message_str = message_str.erase(message_str.size() - 3);
        message_str += "%";
        message->set_payload(message_str.c_str(), message_str.size());
        
        mutex.lock();
            client.publish(message);
        mutex.unlock();
        
        Log::log(_name + ": humidity = " + std::to_string(_humidity) + "%");
        future.wait_for(std::chrono::seconds(_period));
    }
}
