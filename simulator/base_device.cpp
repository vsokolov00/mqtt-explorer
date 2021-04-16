
#include "base_device.h"

Device::Device(std::string topic, std::string name, int period)
        : _topic(topic), _name(name), _period(period) {}
        