
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

    public:
        Device() = default;
        Device(std::string topic, std::string name);
        Device(const Device&) = default;
};

class PublishingDevice : public Device
{
    protected:
        int _period;

    public:
        PublishingDevice() = default;
        PublishingDevice(std::string topic, std::string name, int period);
        PublishingDevice(const PublishingDevice&) = default;
};

class RecievingDevice : public Device
{
    protected:
        std::mutex *_mutex = nullptr;

    public:
        std::string id;
        std::string recv_topic;

        RecievingDevice() = default;
        RecievingDevice(std::string topic, std::string name, std::string id, std::string recv_topic);
        RecievingDevice(const RecievingDevice& device);
        ~RecievingDevice();
        
        virtual void on_message_arrived(std::string state, Client &client, std::mutex &mutex);
};

class RecievingAndPublishingDevice : public RecievingDevice
{
    protected:
        int _period;

    public:
        RecievingAndPublishingDevice() = default;
        RecievingAndPublishingDevice(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        RecievingAndPublishingDevice(const RecievingAndPublishingDevice &device);
};
