
#pragma once

#include "hygrometer.h"
#include "thermometer.h"
#include "wattmeter.h"
#include <vector>

class Devices
{
    public:
        std::vector<Thermometer> thermometers;
        std::vector<Hygrometer> hygrometers;
        std::vector<Wattmeter> wattmeters;
};