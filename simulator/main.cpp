
#include "json/json-forwards.h"
#include "json/json.h"
#include "devices.h"
#include "parser.h"
#include "thermometer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    Devices devices;
    Parser parser("file.json");

    mqtt::client client("tcp://localhost:1883", "id_1985472");
    mqtt::connect_options connection_opts;
    connection_opts.set_keep_alive_interval(60);
    connection_opts.set_clean_session(true);

    try
    {
         client.connect(connection_opts);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error: " << exc.what() << std::endl;
        return 1;
    }

    parser.parse_file(devices);

    thred_control_t control;
    control.condition = true;

    std::vector<std::thread> threads;
    threads.reserve(devices.thermometers.size());
    std::vector<std::promise<void>> promises;
    promises.reserve(devices.thermometers.size());

    for (unsigned i = 0; i < devices.thermometers.size(); i++)
    {
        promises.push_back(std::promise<void>());
        threads.push_back(std::thread(&Thermometer::run_thermometer, devices.thermometers[i], 
                                      std::ref(client), std::ref(control), promises[i].get_future()));
    }

    std::cin.get();

    control.condition = false;
    std::cout << "Please wait, terminating..." << std::endl;

    for (auto &promise: promises)
    {
        promise.set_value();
    }

    for (auto &thread: threads)
    {
        thread.join();
    }

    std::cout << "Bye" << std::endl;
    return 0;
}