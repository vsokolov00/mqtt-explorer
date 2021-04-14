
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include "hygrometer.h"
#include "thermometer.h"
#include "devices.h"
#include "mqtt/client.h"

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
        bool not_runable = false;

        DeviceRunner(std::vector<T> &devices, U function, const std::string &server_address, const std::string &id);

        void run_devices();
        void stop_devices();
};

class Runner
{
    private:
        DeviceRunner<Thermometer, void(Thermometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _thermometer_runner;
        DeviceRunner<Hygrometer, void(Hygrometer::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _hygrometer_runner;
        DeviceRunner<Wattmeter, void(Wattmeter::*)(mqtt::client&, const bool&, std::mutex&, std::future<void>)> _wattmeter_runner;
        
    public:
        bool not_runable = false;

        Runner();
        Runner(Devices &devices, const std::string server_address);

        void run_threads();
        void stop_threads();
};
