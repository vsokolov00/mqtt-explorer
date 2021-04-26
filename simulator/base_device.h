
#pragma once

#include <thread>
#include <string>

#include "mqtt/client.h"
#include "client.h"
#include "log.h"


/**
 * @class Represents a basic device with name and its topic.
 **/ 
class Device
{
    protected:
        std::string _topic;
        std::string _name;

    public:
        Device(std::string topic, std::string name);
        Device(const Device&) = default;
};

/**
 * @class Represents a publishing device with name and period of publihing to topic from the base class.
 **/
class PublishingDevice : public Device
{
    protected:
        int _period;

    public:
        PublishingDevice(std::string topic, std::string name, int period);
        PublishingDevice(const PublishingDevice&) = default;
};

/**
 * @class Represents a recieving device with topic from the bass class used as an answering topic and recv_topic used as topic
 *        where the device listen for commands. The device is identified by its id.
 **/
class RecievingDevice : public Device
{
    protected:
        std::mutex *_mutex = nullptr;

    public:
        std::string id;
        std::string recv_topic;

        RecievingDevice(std::string topic, std::string name, std::string id, std::string recv_topic);
        RecievingDevice(const RecievingDevice& device);
        ~RecievingDevice();

        /**
         * @brief Specificfied by derived class, handles the arrival of mqtt message, the device, to which the message 
         *        is delivered, is identified by the arrival topic and id.
         * @param sate the recieved message, the state to which the device should switch and send a respons on the change.
         * @param client a client used to send the response message.
         * @param mutex a mutex used for sinchroniztion of operations on the client between different devices that recieve 
         *              message.
         **/        
        virtual void on_message_arrived(std::string state, Client &client, std::mutex &mutex);
};

/**
 * @class Represents a recieving and also publishing device, to the base class adds a period of publishing
 **/
class RecievingAndPublishingDevice : public RecievingDevice
{
    protected:
        int _period;

    public:
        RecievingAndPublishingDevice(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        RecievingAndPublishingDevice(const RecievingAndPublishingDevice &device);
};
