
#pragma once

#include "hygrometer.h"
#include "thermometer.h"
#include "wattmeter.h"
#include "move_sensor.h"
#include "light.h"

#include <vector>

struct Devices
{
    public:
        std::vector<Thermometer> thermometers;
        std::vector<Hygrometer> hygrometers;
        std::vector<Wattmeter> wattmeters;
        std::vector<MoveSensor> move_sensors;
        std::vector<Light> lights;
};