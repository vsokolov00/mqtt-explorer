#pragma once

#include <string>
#include <thread>
#include <iostream>
#include <chrono>

extern bool run;

class Thermometer
{
    public:
        std::string name;
        std::string location;
        int max;
        int min;
        float average;
        float deviation;
        int period;
    
    Thermometer(std::string name, std::string location, int max, int min, float average, float deviation, int period);

    void run_thermometer();
};
