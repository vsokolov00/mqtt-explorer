
#include "relay.h"

Relay::Relay(std::string topic, std::string name, std::string id, std::string recv_topic)
      : RecievingDevice(topic, name, id, recv_topic) { }

//Relay::Relay(const Relay &relay)
//      : RecievingDevice(relay), _state(relay._state), _states(relay._states) { }

void Relay::add_state(std::string state)
{
    _states.push_back(state);
}

void Relay::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
{
    std::string message_str = "name: " + _name;
    auto iterator = std::find(_states.begin(), _states.end(), state);

    if (iterator == _states.end())
    {
        mutex.lock();
            message_str += ", change unsuccessful, unknow state: " + state;
            std::cerr << message_str << std::endl;
            client.publish(_topic, message_str);
        mutex.unlock();
        return;
    }

    _mutex->lock();
        if (state != _state)
        {
            message_str += ", changing state to: " + state;
        }
        else
        {
            message_str += ", state remains unchanged: " + state;
        }
        _state = state;
        
        mutex.lock();
            client.publish(_topic, message_str);
        mutex.unlock();
        std::cerr << message_str << std::endl;
    _mutex->unlock();
}
