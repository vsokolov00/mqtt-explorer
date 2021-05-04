
/**
 * @file        runner.h
 * Case:        VUT, FIT, ICP, project                          <br>
 * Author:      David Mihola, xmihol00@stud.fit.vutbr.cz        <br>
 * Date:        summer semester 2021                            <br>
 * Compiled:    g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0        <br>
 * @brief       Declaration of a Runner class, which runs simultaneously all registered devices.
 **/

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include "hygrometer.h"
#include "thermometer.h"
#include "devices.h"
#include "reciever.h"
#include "options.h"

/**
 * @brief Template class with T as a device type and U as a run function of that device
 **/
template<class T, class U> class DeviceRunner
{
    private:
        bool _run = false;                  ///< true when devices are running, otherwise false
        std::vector<T>& _devices;           ///< vector of devices of specified type
        U _function;                        ///< run function of a device
    
        mqtt::client _client;                       ///< client used for publishing
        std::mutex _mutex;                          ///< mutex used for synchronization of operations on the @see _client
        std::vector<std::thread> _threads;          ///< running threads with size equals to the number of devices
        std::vector<std::promise<void>> _promises;  ///< vector of promises used to terminate threads when needed

    public:
        DeviceRunner(std::vector<T> &devices, U function, const std::string &server_address, const std::string &id);

        /**
         * @brief Connects client of a T type of devices.
         * @param connect_options the options of connection.
         **/
        void connect_client(mqtt::connect_options connect_options);

        /**
         * @brief Disconnect client of a T type of device.
         **/
        void disconnect_client();

        /**
         * @brief Runs all devices of type T with run function U.
         **/
        void run_devices();

        /**
         * @brief Stops all devices of type T.
         **/
        void stop_devices();
};

/**
 * @brief Runs publishing and recieving devices, the devices that are run are determined by the flags created by
 *        the command line arguments.
 **/
class Runner
{
    private:
        DeviceRunner<Thermometer, void(Thermometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _thermometer_runner;  ///< runs the Thermometer devices
        DeviceRunner<Hygrometer, void(Hygrometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _hygrometer_runner;     ///< runs the Hygrometer devices
        DeviceRunner<Wattmeter, void(Wattmeter::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _wattmeter_runner;        ///< runs the Wattmeter devices
        DeviceRunner<MoveSensor, void(MoveSensor::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _move_sensor_runner;    ///< runs the MoveSensor devices
        DeviceRunner<Light, void(Light::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _light_runner;                    ///< runs the Light devices
        DeviceRunner<Camera, void(Camera::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _camera_runner;                 ///< runs the Camera devices
        DeviceRunner<Valve, void(Valve::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _valve_runner;                    ///< runs the Valve devices
        DeviceRunner<Thermostat, void(Thermostat::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _thermostat_runner;     ///< runs the Thermostat devices

        Reciever _reciever;        ///< reciever used for recieving messages of all registered recieving devices
        unsigned _flags;           ///< flags determining which devices are started

    public:
        Runner(Devices &devices, const std::string server_address, unsigned flags);

        /**
         * @brief Runs all registered devices.
         **/
        bool start();

        /**
         * @brief Stops all running devices.
         **/
        void stop();
};
