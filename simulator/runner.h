
#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include "thermometer.h"
#include "devices.h"
#include "mqtt/client.h"

class Runner
{
    private:
        ThermometerRunner _thermometer_runner;


    public:
        bool not_runable = false;

        Runner();
        Runner(Devices &devices, const std::string server_address);

        void run_threads();
        void stop_threads();
};
