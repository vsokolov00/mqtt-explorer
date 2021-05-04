
/**
 * @file        relay.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and functions of the Relay class.
 **/

#include "relay.h"

Relay::Relay(std::string topic, std::string name, std::string id, std::string recv_topic)
      : RecievingDevice(topic, name, id, recv_topic) { }

void Relay::add_state(std::string state)
{
    _states.push_back(state);
}

void Relay::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
{
    std::string message_str = _name;
    auto iterator = std::find(_states.begin(), _states.end(), state);

    if (iterator == _states.end())
    {
        mutex.lock();
            message_str += ": change unsuccessful, unknow state: " + state;
            Log::log(message_str);
            client.publish(_topic, message_str);
        mutex.unlock();
        return;
    }

    _mutex->lock();
        if (state != _state)
        {
            message_str += ": changing state to: " + state;
        }
        else
        {
            message_str += ": state remains unchanged: " + state;
        }
        _state = state;
        
        mutex.lock();
            client.publish(_topic, message_str);
        mutex.unlock();
        Log::log(message_str);
    _mutex->unlock();
}
