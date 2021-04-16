
#include "base_device.h"

Device::Device(std::string topic, std::string name, int period)
        : _topic(topic), _name(name), _period(period) {}

RecievingDevice::RecievingDevice(std::string topic, std::string name, int period, std::string id, std::string recv_topic)
                : Device(topic, name, period), id(id), recv_topic(recv_topic) {}
        
void RecievingDevice::on_message_arrived(std::string state, Client &client, std::mutex &mutex)
{
    (void)client;
    (void)mutex;
    std::cerr << "Message arrived to virtual function, state: " << state << std::endl;
}
        