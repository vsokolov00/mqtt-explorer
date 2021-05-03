
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
 * @class Template class with T as a device type and U as a run function of that device
 **/
template<class T, class U> class DeviceRunner
{
    private:
        bool _run = false;
        std::vector<T>& _devices;
        U _function;

        mqtt::client _client;
        std::mutex _mutex;
        std::vector<std::thread> _threads;
        std::vector<std::promise<void>> _promises;

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
 * @class Runs publishing and recieving devices, the devices that are run are determined by the flags created by
 *        the command line arguments.
 **/
class Runner
{
    private:
        DeviceRunner<Thermometer, void(Thermometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _thermometer_runner;
        DeviceRunner<Hygrometer, void(Hygrometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _hygrometer_runner;
        DeviceRunner<Wattmeter, void(Wattmeter::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _wattmeter_runner;
        DeviceRunner<MoveSensor, void(MoveSensor::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _move_sensor_runner;
        DeviceRunner<Light, void(Light::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _light_runner;
        DeviceRunner<Camera, void(Camera::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _camera_runner;
        DeviceRunner<Valve, void(Valve::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _valve_runner;
        DeviceRunner<Thermostat, void(Thermostat::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _thermostat_runner;

        Reciever _reciever;
        unsigned _flags;

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
