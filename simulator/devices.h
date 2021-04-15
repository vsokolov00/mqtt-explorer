
#pragma once

#include "hygrometer.h"
#include "thermometer.h"
#include "wattmeter.h"
#include "move_sensor.h"
#include <vector>

class Devices
{
    public:
        std::vector<Thermometer> thermometers;
        std::vector<Hygrometer> hygrometers;
        std::vector<Wattmeter> wattmeters;
        std::vector<MoveSensor> move_sensors;
};