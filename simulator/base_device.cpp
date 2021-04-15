
#include "base_device.h"

Device::Device(std::string topic, std::string name, int period)
        : topic(topic), name(name), period(period) {}
        