
/**
 * @file        lock.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and functions of the Lock class.
 **/

#include "lock.h"

Lock::Lock(std::string topic, std::string name, std::string id, std::string recv_topic)
      : RecievingDevice(topic, name, id, recv_topic) { }

void Lock::add_state(std::string state)
{
    _states.push_back(state);
}

void Lock::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
{
    auto iterator = std::find(_states.begin(), _states.end(), state);
    
    Json::Value root;
    Json::StreamWriter *writer = Json::StreamWriterBuilder().newStreamWriter();
    if (writer == nullptr)
    {
        Log::error("unable to allocate resources to answer a message on device: " + _name + ".");
    }
    std::ostringstream stream;
    std::string message_str;

    root["name"] = _name;
    root["id"] = id;

    if (iterator == _states.end())
    {
        mutex.lock();
            root["change"] = "unsuccessful";
            root["unknow state"] = state;
            writer->write(root, &stream);
            message_str = stream.str();

            Log::log(_name + ": change of state unsuccessful, unknown state: " + state);
            client.publish(_topic, message_str);
        mutex.unlock();

        delete writer;
        return;
    }

    _mutex->lock();
        if (state != _state)
        {
            root["change"] = "successful";
            root["state"] = state;
            writer->write(root, &stream);
            message_str = stream.str();

            Log::log(_name + ": changing state to: " + state);
        }
        else
        {
            root["change"] = "unchanged";
            root["state"] = state;
            writer->write(root, &stream);
            message_str = stream.str();

            Log::log(_name + ": state remains unchanged: " + state);
        }
        _state = state;
        
        mutex.lock();
            client.publish(_topic, message_str);
        mutex.unlock();
    _mutex->unlock();

    delete writer;
}
