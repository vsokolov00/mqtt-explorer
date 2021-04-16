
#pragma once

#include <thread>
#include <string>

#include "mqtt/client.h"
#include "client.h"


class Device
{
    protected:
        std::string _topic;
        std::string _name;
        int _period;

    public:
        Device() = default;
        Device(std::string topic, std::string name, int period);
        Device(const Device&) = default;
};

class RecievingDevice : public Device
{
    public:
        std::string id;
        std::string recv_topic;

        RecievingDevice() = default;
        RecievingDevice(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        RecievingDevice(const RecievingDevice&) = default;
        
        virtual void on_message_arrived(std::string state, Client &client, std::mutex &mutex);
};
