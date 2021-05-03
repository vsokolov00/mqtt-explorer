
//================================================================================================
// File:        devices.h
// Case:        VUT, FIT, ICP, project
// Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
// Date:        summer semester 2021
// Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
// Description: Declaration of a structure encapsulating all devices.
//================================================================================================

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

/**
 * @struct Holds all devices, that can be simulated by the simulator.
 **/
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
