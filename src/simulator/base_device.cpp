
/**
 * @file        base_device.cpp
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Implementation of constructors, destructors and virtual functions of base classes
 *              used by other classes, which represent specific devices.
 **/

#include "base_device.h"

Device::Device(std::string topic, std::string name)
       : _topic(topic), _name(name) {}

PublishingDevice::PublishingDevice(std::string topic, std::string name, int period)
        : Device(topic, name), _period(period) {}

RecievingDevice::RecievingDevice(std::string topic, std::string name, std::string id, std::string recv_topic)
                : Device(topic, name), id(id), recv_topic(recv_topic) 
{
    _mutex = new std::mutex();
}

RecievingDevice::RecievingDevice(const RecievingDevice& device) 
                : Device(device), id(device.id), recv_topic(device.recv_topic)
{
    _mutex = new std::mutex();
}

RecievingDevice::~RecievingDevice()
{
    delete _mutex;
}
        
void RecievingDevice::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
{
    (void)client;
    (void)mutex;
    Log::warning("Message arrived to virtual function, state: " + state);
}
        
RecievingAndPublishingDevice::RecievingAndPublishingDevice(std::string topic, std::string name, int period, std::string id, 
                                                           std::string recv_topic)
                             : RecievingDevice(topic, name, id, recv_topic), _period(period) {}

RecievingAndPublishingDevice::RecievingAndPublishingDevice(const RecievingAndPublishingDevice &device) 
                             : RecievingDevice(device), _period(device._period) { }

