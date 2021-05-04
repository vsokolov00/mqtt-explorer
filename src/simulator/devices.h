
/**
 * @file        devices.h
 * Case:        VUT, FIT, ICP, project                             <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz           <br>
 * Date:        summer semester 2021                               <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0           <br>
 * @brief       Declaration of a structure encapsulating all devices.
 **/

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
 * @brief Holds all devices, that can be simulated by the simulator.
 **/
struct Devices
{
    public:
        std::vector<Thermometer> thermometers;      ///< Thermometer dvices
        std::vector<Hygrometer> hygrometers;        ///< Hygrometer dvices
        std::vector<Wattmeter> wattmeters;          ///< Wattmeter devices
        std::vector<MoveSensor> move_sensors;       ///< MoveSensor devices
        std::vector<Light> lights;                  ///< Light devices
        std::vector<Camera> cameras;                ///< Camera devices
        std::vector<Relay> relays;                  ///< Relay devices
        std::vector<Valve> valves;                  ///< Valve devices
        std::vector<Thermostat> thermostats;        ///< Thermostat devices
        std::vector<Lock> locks;                    ///< Lock devices
};
