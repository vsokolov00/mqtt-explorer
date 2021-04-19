
#pragma once

#include "hygrometer.h"
#include "thermometer.h"
#include "wattmeter.h"
#include "move_sensor.h"
#include "light.h"
#include "camera.h"
#include "relay.h"
#include "valve.h"
#include "thermostat.h"
#include "lock.h"

#include <vector>

struct Devices
{
    public:
        std::vector<Thermometer> thermometers;
        std::vector<Hygrometer> hygrometers;
        std::vector<Wattmeter> wattmeters;
        std::vector<MoveSensor> move_sensors;
        std::vector<Light> lights;
        std::vector<Camera> cameras;
        std::vector<Relay> relays;
        std::vector<Valve> valves;
        std::vector<Thermostat> thermostats;
        std::vector<Lock> locks;
};