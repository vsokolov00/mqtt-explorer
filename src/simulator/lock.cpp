
//================================================================================================
// File:        lock.cpp
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Implementation of constructors, destructors and functions of the Lock class.
//================================================================================================

#include "lock.h"

Lock::Lock(std::string topic, std::string name, std::string id, std::string recv_topic)
      : RecievingDevice(topic, name, id, recv_topic) { }

void Lock::add_state(std::string state)
{
    _states.push_back(state);
}

void Lock::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
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
