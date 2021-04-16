
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include "mqtt/client.h"
#include "hygrometer.h"
#include "thermometer.h"
#include "devices.h"
#include "reciever.h"

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

        void connect_clients(mqtt::connect_options connect_options);
        void disconnect_clients();
        void run_devices();
        void stop_devices();
};

class Runner
{
    private:
        DeviceRunner<Thermometer, void(Thermometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _thermometer_runner;
        DeviceRunner<Hygrometer, void(Hygrometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _hygrometer_runner;
        DeviceRunner<Wattmeter, void(Wattmeter::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _wattmeter_runner;
        DeviceRunner<MoveSensor, void(MoveSensor::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _move_sensor_runner;
        DeviceRunner<Light, void(Light::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _light_runner;

        Reciever _reciever;

    public:
        Runner(Devices &devices, const std::string server_address);

        bool start();
        void stop();
};
