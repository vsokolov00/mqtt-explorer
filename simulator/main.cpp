
#include "json/json-forwards.h"
#include "json/json.h"
#include "devices.h"
#include "parser.h"
#include "thermometer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool run = true;

int main()
{
    Devices devices;
    Parser parser("file.json");

    parser.parse_file(devices);

    std::vector<std::thread> threads;
    threads.reserve(devices.thermometers.size());

    for (int i = 0; i < devices.thermometers.size(); i++)
    {
        threads.push_back(std::thread(&Thermometer::run_thermometer, devices.thermometers[i]));
    }

    std::cin.get();

    run = false;
    std::cout << "Please wait, terminating..." << std::endl;

    for (auto &thread: threads)
    {
        thread.join();
    }

    std::cout << "Bye" << std::endl;
    return 0;
}