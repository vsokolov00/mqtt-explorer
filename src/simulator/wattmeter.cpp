
/**
 * @file        wattmeter.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a class representing a Wattmeter device.
 **/

#include "wattmeter.h"

Wattmeter::Wattmeter(std::string topic, std::string name, int period, int min_val, 
                  int max_val, int min_step, int max_step, int value, std::string unit)
          :PublishingDevice(topic, name, period), _min_val(min_val), _max_val(max_val), _min_step(min_step),
           _max_step(max_step), _value(value), _unit(unit) {}

void Wattmeter::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(_topic, _name);
    message->set_qos(1);

    auto step_generator = std::bind(std::uniform_int_distribution<int>(_min_step, _max_step), std::default_random_engine(time(nullptr)));
    step_generator();
    auto up_down_generator = std::bind(std::uniform_int_distribution<int>(0, 1), std::default_random_engine(time(nullptr)));
    up_down_generator();

    float step;
    bool up_down;
    std::string message_str;

    future.wait_for(std::chrono::seconds(_period));
    while (run)
    {
        step = step_generator();
        up_down = up_down_generator();

        if (up_down)
        {
            _value = _value + step > _max_val ? _max_val : _value + step;
        }
        else
        {
            _value = _value - step < _min_val ? _min_val : _value - step;
        }

        message_str = std::to_string(_value) + " " + _unit;
        message->set_payload(message_str.c_str(), message_str.size());
        
        mutex.lock();
            client.publish(message);
        mutex.unlock();

        Log::log(_name + ": electric power = " + std::to_string(_value) + " " + _unit);
        future.wait_for(std::chrono::seconds(_period));
    }
}
