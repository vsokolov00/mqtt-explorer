
/**
 * @file        base_device.h                                 
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of classes representing types of devices, which are used as base
 *              classes of specific devices.
 **/

#pragma once

#include <thread>
#include <string>

#include "log.h"
#include "../client/client.h"
#include "../client/listener.h"


/**
 * @brief Represents a basic device with name and its topic.
 **/ 
class Device
{
    protected:
        std::string _topic;     ///< publishing topic of a device
        std::string _name;      ///< name of a device

    public:
        Device(std::string topic, std::string name);
        Device(const Device&) = default;
};

/**
 * @brief Represents a publishing device with name and period of publihing to topic from the base class.
 **/
class PublishingDevice : public Device
{
    protected:
        int _period;       ///< period or minimum period, depends on the derived class interpretation

    public:
        PublishingDevice(std::string topic, std::string name, int period);
        PublishingDevice(const PublishingDevice&) = default;
};

/**
 * @brief Represents a recieving device with topic from the bass class used as an answering topic and recv_topic used as topic
 *        where the device listen for commands. The device is identified by its id.
 **/
class RecievingDevice : public Device
{
    protected:
        std::mutex *_mutex = nullptr;   ///< mutex used for synchronization when sending messages via @see Client

    public:
        std::string id;                 ///< id of a device
        std::string recv_topic;         ///< recieving topic of a device

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
 * @brief Represents a recieving and also publishing device, to the base class adds a period of publishing
 **/
class RecievingAndPublishingDevice : public RecievingDevice
{
    protected:
        int _period;       ///< period or minimum period, depends on the derived class interpretation

    public:
        RecievingAndPublishingDevice(std::string topic, std::string name, int period, std::string id, std::string recv_topic);
        RecievingAndPublishingDevice(const RecievingAndPublishingDevice &device);
};
