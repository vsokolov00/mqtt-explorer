
#include "base_device.h"

Device::Device(std::string topic, std::string name, std::string location, int period)
        : topic(topic), name(name), location(location), period(period) {}
        