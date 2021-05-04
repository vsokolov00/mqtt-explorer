
/**
 * @file        thermostat.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and functions of the Thermostat class.
 **/

#include "thermostat.h"

Thermostat::Thermostat(std::string topic, std::string name, std::string id, std::string recv_topic, int min_period, 
                       int max_period, float set_point, float temp_change, float temp, std::string unit)
           : RecievingAndPublishingDevice(topic, name, min_period, id, recv_topic), _max_period(max_period),
             _set_point(set_point), _temp_change(temp_change), _temp(temp), _unit(unit) 
{
    _direction = _set_point > _temp;
}

void Thermostat::run(mqtt::client &client, const bool &run, std::mutex &mutex, std::future<void> future)
{
    mqtt::message_ptr message = mqtt::make_message(_topic, _name);
    message->set_qos(1);

    auto period_generator = std::bind(std::uniform_int_distribution<int>(_period, _max_period), 
                                      std::default_random_engine(time(nullptr)));
    period_generator();
    auto step_generator = std::bind(std::uniform_int_distribution<int>(0, static_cast<int>(_temp_change * 1000)), 
                                    std::default_random_engine(time(nullptr)));
    step_generator();

    float temp_chage{0};
    std::string temp_str;
    std::string message_str;

    future.wait_for(std::chrono::seconds(period_generator()));
    while (run)
    {
        message_str = _name;
        temp_chage = step_generator() / 1000.0f;

        _mutex->lock();
            
            _direction ? _temp += temp_chage : _temp -= temp_chage; 
            temp_str = std::to_string(_temp);
            temp_str = temp_str.erase(temp_str.size() - 3);

            if (_direction && _set_point > _temp)
            {
                message_str += ": temperature raised to: " + temp_str + " " + _unit + ", heating remains turned on";
            }
            else if (!_direction && _set_point < _temp)
            {
                message_str += ": temperature droped to: " + temp_str + " " + _unit + ", heating remains turned off";
            }
            else if (_direction && _set_point < _temp)
            {
                message_str += ": temperature raised to: " + temp_str + " " + _unit + ", turning heating off";
            }
            else
            {
                message_str += ": temperature droped to: " + temp_str + " " + _unit + ", turning heating on";
            }
            _direction = _set_point > _temp;

            message->set_payload(message_str.c_str(), message_str.size());

            mutex.lock();
                client.publish(message);
            mutex.unlock();

            Log::log(message_str);
        _mutex->unlock();

        future.wait_for(std::chrono::seconds(period_generator()));
    }
}

void Thermostat::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
{
    std::string message_str = _name;
    
    float set_point;
    try
    {
        set_point = std::stof(state);
    }
    catch (const std::invalid_argument& e1)
    {
        message_str += ": recieved value could not be parsed";
        Log::log(message_str);
        mutex.lock();
            client.publish(_topic, message_str);
        mutex.unlock();
    }
    catch (const std::out_of_range& e2)
    {
        message_str += ": recieved value could not be parsed";
        Log::log(message_str);
        mutex.lock();
            client.publish(_topic, message_str);
        mutex.unlock();
    } 

    std::string set_point_str = std::to_string(set_point);
    set_point_str = set_point_str.erase(set_point_str.size() - 3);
    std::string temp_str = std::to_string(_temp);
    temp_str = temp_str.erase(temp_str.size() - 3);

    _mutex->lock();
        if (_direction && set_point > _temp && set_point > _set_point)
        {
            message_str += ": set point raised to " + set_point_str + " " + _unit + ", heating remains turned on, current temperature is " +
                           temp_str + " " + _unit;
        }
        else if (_direction && set_point > _temp && set_point < _set_point)
        {
            message_str += ": set point lowerd to " + set_point_str + " " + _unit + ", heating remains turned on, current temperature is " +
                           temp_str + " " + _unit;
        }
        else if (_direction && set_point < _temp && set_point > _set_point)
        {
            message_str += ": set point raised to " + set_point_str + " " + _unit + ", turning heating off, current temperature is " +
                           temp_str + " " + _unit;
        }
        else if (_direction && set_point < _temp && set_point < _set_point)
        {
            message_str += ": set point lowerd to " + set_point_str + " " + _unit + ", turning heating off, current temperature is " +
                           temp_str + " " + _unit;
        }
        else if (!_direction && set_point < _temp && set_point < _set_point)
        {
            message_str += ": set point lowerd to " + set_point_str + " " + _unit + ", heating remains turned off, current temperature is " +
                           temp_str + " " + _unit;
        }
        else if (!_direction && set_point < _temp && set_point > _set_point)
        {
            message_str += ": set point raised to " + set_point_str + " " + _unit + ", heating remains turned off, current temperature is " +
                           temp_str + " " + _unit;
        }
                else if (!_direction && set_point > _temp && set_point < _set_point)
        {
            message_str += ": set point lowerd to " + set_point_str + " " + _unit + ", turning heating on, current temperature is " +
                           temp_str + " " + _unit + _unit;
        }
        else if (!_direction && set_point > _temp && set_point > _set_point)
        {
            message_str += ": set point raised to " + set_point_str + " " + _unit + ", turning heating on, current temperature is " +
                           temp_str + " " + _unit;
        }
        _set_point = set_point;
        _direction = _set_point > _temp;
        
        mutex.lock();
            client.publish(_topic, message_str);
        mutex.unlock();
        Log::log(message_str);
    _mutex->unlock();
}
